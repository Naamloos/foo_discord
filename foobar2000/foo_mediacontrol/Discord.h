#include <iostream>
#include <sstream>
#include "stdafx.h"
#include "util.h"
#include "preferences.h"
#define _CRT_SECURE_NO_WARNING

const char* APPLICATION_ID = "379748462377566219";

void handleDiscordReady() {}

void handleDiscordDisconnected(int errcode, const char* message) {}

void handleDiscordError(int errcode, const char* message) {}

void discordInit()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.disconnected = handleDiscordDisconnected;
	handlers.errored = handleDiscordError;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

#include <ctime>;

static char *savedsongname;
static char *savedartist;
static char *savedalbum;
static double start_epoch;
static double pause_epoch;
static double savedlength;

void UpdatePresence(wchar_t *songname, wchar_t *artist, double tracklength, wchar_t *filename, wchar_t *album)
{
	savedsongname = util::wide_to_utf8(songname);
	savedartist = util::wide_to_utf8(artist);
	savedalbum = util::wide_to_utf8(album);

	if (strlen(savedsongname) < 1) {
		savedsongname = util::wide_to_utf8(filename);
	}
	if (strlen(savedartist) < 1) {
		savedartist = "";
	}
	savedlength = tracklength;
	std::time_t result = std::time(nullptr);
	start_epoch = result;

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = savedsongname;
	if (preferences::get_show_image()) {
		discordPresence.largeImageKey = "foobar";
	}
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	if (preferences::get_show_album() && strlen(savedalbum) > 0) {
		std::stringstream ss;
		ss << savedartist << " [" << savedalbum << "]";
		discordPresence.state = ss.str().c_str();
	}
	else {
		discordPresence.state = savedartist;
	}
	discordPresence.instance = 1;
	discordPresence.startTimestamp = result;
	discordPresence.endTimestamp = result + tracklength;
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresenceSeeked(double seek) {
	std::time_t result = std::time(nullptr);

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = savedsongname;
	if (preferences::get_show_image()) {
		discordPresence.largeImageKey = "foobar";
	}
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	if (preferences::get_show_album() && strlen(savedalbum) > 0) {
		std::stringstream ss;
		ss << savedartist << " [" << savedalbum << "]";
		discordPresence.state = ss.str().c_str();
	}
	else {
		discordPresence.state = savedartist;
	}
	discordPresence.instance = 1;
	discordPresence.startTimestamp = result;
	discordPresence.endTimestamp = result + (savedlength - seek);
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresenceResumed() {
	std::time_t result = std::time(nullptr);
	double played = pause_epoch - start_epoch;

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = savedsongname;
	if (preferences::get_show_image()) {
		discordPresence.largeImageKey = "foobar";
	}
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	if (preferences::get_show_album() && strlen(savedalbum) > 0) {
		std::stringstream ss;
		ss << savedartist << " [" << savedalbum << "]";
		discordPresence.state = ss.str().c_str();
	}
	else {
		discordPresence.state = savedartist;
	}
	discordPresence.instance = 1;
	discordPresence.startTimestamp = result;
	discordPresence.endTimestamp = result + (savedlength - played);
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresencePaused()
{
	pause_epoch = std::time(nullptr);
	char buffer[256];
	sprintf_s(buffer, 256, "%s (Paused)", savedsongname);
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = buffer;
	if (preferences::get_show_image()) {
		discordPresence.largeImageKey = "foobar";
	}
	discordPresence.smallImageKey = "pause";
	discordPresence.smallImageText = "Paused";
	discordPresence.largeImageText = "Foobar2000";
	if (preferences::get_show_album() && strlen(savedalbum) > 0) {
		std::stringstream ss;
		ss << savedartist << " [" << savedalbum << "]";
		discordPresence.state = ss.str().c_str();
	}
	else {
		discordPresence.state = savedartist;
	}
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresenceStopped()
{
	if (preferences::get_show_stop()) {
		if (preferences::get_show_songstop() == false) {
			char buffer[256];
			DiscordRichPresence discordPresence;
			memset(&discordPresence, 0, sizeof(discordPresence));
			if (preferences::get_show_image()) {
				discordPresence.largeImageKey = "foobar";
			}
			discordPresence.smallImageKey = "stop";
			discordPresence.smallImageText = "Stopped";
			discordPresence.largeImageText = "Foobar2000";
			discordPresence.details = "Stopped";
			discordPresence.instance = 1;
			Discord_UpdatePresence(&discordPresence);
		}
		else {
			char buffer[256];
			sprintf_s(buffer, 256, "%s (Stopped)", savedsongname);
			DiscordRichPresence discordPresence;
			memset(&discordPresence, 0, sizeof(discordPresence));
			discordPresence.details = buffer;
			if (preferences::get_show_image()) {
				discordPresence.largeImageKey = "foobar";
			}
			discordPresence.smallImageKey = "stop";
			discordPresence.smallImageText = "Stopped";
			discordPresence.largeImageText = "Foobar2000";
			if (preferences::get_show_album() && strlen(savedalbum) > 0) {
				std::stringstream ss;
				ss << savedartist << " [" << savedalbum << "]";
				discordPresence.state = ss.str().c_str();
			}
			else {
				discordPresence.state = savedartist;
			}
			discordPresence.instance = 1;
			Discord_UpdatePresence(&discordPresence);
		}
	}
	else {
		Discord_ClearPresence();
	}
}