#include "stdafx.h"
#include "RpcClient.h"
#include <sstream>
using namespace std;
#define _CRT_SECURE_NO_WARNING

RpcClient RpcClient::rpc;

RpcClient::RpcClient()
{
}

// Here we initialize our RPC Client.
void RpcClient::Initialize()
{
	try{
		// Initializing Discord's RPC api..
		Discord_Initialize(BASE_APPID, NULL, 1, NULL);

		// We're not doing anything yet, so we're idling.
		details = "Idle";
		state = NULL;
		foostarttime = time(nullptr); // time(nullptr) returns the current time, apparently.

		// Updating the presence, thus sending it to the client.
		UpdatePresence();

		// After all this, we're setting the initialized value to true. If this failed, all methods should not do anything.
		this->initialized = true;
	}
	catch (std::exception e) {
		// failed to initialize RPC, telling the user to either restart or ignore us.
		popup_message::g_show("Failed to initialize Discord RPC.\nTry restarting foobar2000 to try again, or proceed to your music.\nIf this issue persists, contact Naamloos.", "Whoopsie Daisy!");
	}
}

// This method updates the current presence.
void RpcClient::UpdatePresence() {
	// Check whether the user wants to show images. If so, set image to current option.
	if (preferences::get_show_image()) {
		largeimagekey = getArtType();
	}
	else {
		largeimagekey = NULL;
	}

	// Check whether the user wants to show elapsed time. If so, set it.
	if (preferences::get_elapsed()) {
		KillTimer();
		start = foostarttime;
	}

	// Create a new DiscordRichPresence instance.
	DiscordRichPresence drp;
	memset(&drp, 0, sizeof(drp));

	// Set all fields of the presence to their respective values.
	drp.details = details;
	drp.state = state;
	if (hasTimer) {
		drp.endTimestamp = end;
		drp.startTimestamp = start;
	}
	drp.largeImageKey = largeimagekey;
	drp.largeImageText = largeimagetext;
	drp.smallImageKey = smallimagekey;
	drp.smallImageText = smallimagetext;

	// Update values.
	Discord_UpdatePresence(&drp);
}

// Sets a new song name.
void RpcClient::SetSongName(wchar_t* songname) {
	details = util::wide_to_utf8(songname);
}

// Sets the artist name and the album name.
void RpcClient::SetArtistName(wchar_t* artistname, wchar_t* albumname) {
	if (preferences::get_show_album() && wcslen(albumname)) {
		int bufferlen = wcslen(artistname) + wcslen(albumname) + 3;
		wchar_t* buffer = new wchar_t[bufferlen];
		wcscpy(buffer, artistname);
		wcscat(buffer, util::utf8_to_wide(" ["));
		wcscat(buffer, albumname);
		wcscat(buffer, util::utf8_to_wide("]"));
		state = util::wide_to_utf8(buffer);
	}
	else {
		state = util::wide_to_utf8(artistname);
	}
}


// Sets the timer.
void RpcClient::SetTimer(double length, bool storelen) {
	time_t current = time(nullptr);
	
	start = current;
	end = current + length;
	if (storelen) {
		songlength = length;
	}
	starttime = current;
	hasTimer = true;
}

// Resumes the timer.
void RpcClient::ResumeTimer() {
	time_t current = time(nullptr);

	start = current;
	end = current + (songlength - (pausetime - starttime));
	hasTimer = true;
}

// Seeks on the timer.
void RpcClient::SeekTimer(double time) {
	RpcClient::SetTimer(songlength - time, false);
}

// Kills the timer.
void RpcClient::KillTimer() {
	hasTimer = false;
}

// Sets current status to playing.
void RpcClient::SetPlay() {
	smallimagekey = "play";
	smallimagetext = "Playing";
	hasTimer = true;
}

// Sets current status to paused.
void RpcClient::SetPause() {
	smallimagekey = "pause";
	smallimagetext = "Paused";
	pausetime = time(nullptr);
	hasTimer = false;
}

// Sets current status to stopped.
void RpcClient::SetStop() {
	smallimagekey = "stop";
	smallimagetext = "Stopped";

	if (!preferences::get_show_songstop()) {
		details = "Idle";
		state = " ";
	}
	hasTimer = false;
}

// Disconnects Discord RPC
void RpcClient::Disconnect() 
{
	Discord_Shutdown();
}

// Indicated whether this RpcClient was initialized.
bool RpcClient::IsInitialized()
{
	return initialized;
}

// Gets the current art type.
const char* RpcClient::getArtType() {
	int arttype = preferences::get_art_type();

	if (arttype == 1) {
		return "foobar";
	}
	else if (arttype == 2) {
		return "note";
	}
	else if (arttype == 3) {
		return "saiko";
	}
	else if (arttype == 4) {
		return "kirb";
	}
	else if (arttype == 5) {
		return "think";
	}
	else if (arttype == 6) {
		return "anime";
	}

	return "foobar";
}

RpcClient::~RpcClient()
{
	Discord_Shutdown();
}
