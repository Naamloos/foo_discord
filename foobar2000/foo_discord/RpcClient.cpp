#include <helpers/foobar2000+atl.h>
#include "RpcClient.h"
#include <sstream>

RpcClient RpcClient::rpc;

discord::Core* discordCore{};

RpcClient::RpcClient()
{
}

// Here we initialize our RPC Client.
void RpcClient::Initialize()
{
	try{
		// Initializing a new Discord GameSDK Core client.
		discord::Core::Create(BASE_APPID, DiscordCreateFlags_Default, &discordCore);

		// We're not doing anything yet, so we're idling.
		strcpy(details, "Idle");
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
		strcpy(largeimagekey, getArtType());
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
	discord::Activity presence = discord::Activity();

	// Set all fields of the presence to their respective values.
	presence.SetDetails(details);
	presence.SetState(state);
	presence.SetApplicationId(BASE_APPID);

	if (hasTimer) {
		// Get timestamps and set their uh.. timestamps.
		discord::ActivityTimestamps time = presence.GetTimestamps();
		time.SetEnd(end);
		time.SetStart(start);
	}

	discord::ActivityAssets assets = presence.GetAssets();
	assets.SetLargeImage(largeimagekey);
	assets.SetLargeText(largeimagetext);
	assets.SetSmallImage(smallimagekey);
	assets.SetSmallText(smallimagetext);

	// Update values.
	discordCore->ActivityManager().UpdateActivity(presence, [](discord::Result result) {}); // don't really care about the result as of right now.
}

// Sets a new song name.
void RpcClient::SetSongName(wchar_t* songname) {
	details = util::wide_to_utf8(songname);
}

// Sets the artist name and the album name.
void RpcClient::SetArtistName(wchar_t* artistname, wchar_t* albumname) {
	if (preferences::get_show_album() && wcslen(albumname) > 0) {
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
	strcpy(smallimagekey, "play");
	strcpy(smallimagetext, "Playing");
	hasTimer = true;
}

// Sets current status to paused.
void RpcClient::SetPause() {
	strcpy(smallimagekey, "pause");
	strcpy(smallimagetext, "Paused");
	pausetime = time(nullptr);
	hasTimer = false;
}

// Sets current status to stopped.
void RpcClient::SetStop() {
	strcpy(smallimagekey, "stop");
	strcpy(smallimagetext, "Stopped");

	if (!preferences::get_show_songstop()) {
		strcpy(details, "Idle");
		strcpy(state, " ");
	}
	hasTimer = false;
}

// Disconnects Discord RPC
void RpcClient::Disconnect() 
{
	discordCore->~Core();
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
	discordCore->~Core();
}
