#include <iostream>
#include "stdafx.h"
#include "util.h"
#define _CRT_SECURE_NO_WARNING

const char* APPLICATION_ID = "379748462377566219";

void handleDiscordReady() {}

void handleDiscordDisconnected(int errcode, const char* message) {}

void handleDiscordError(int errcode, const char* message) {}

void handleDiscordJoin(const char* secret) {
	std::cout << "Somone wants to join your game" << std::endl;

}

void handleDiscordSpectate(const char* secret) {
	std::cout << "Somone wants to Spectate you" << std::endl;
}

void handleDiscordJoinRequest(const DiscordJoinRequest* request) {}

void discordInit()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.errored = handleDiscordError;
	handlers.joinGame = handleDiscordJoin;
	handlers.spectateGame = handleDiscordSpectate;
	handlers.joinRequest = handleDiscordJoinRequest;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

#include <ctime>;

static char *savedsongname;
static char *savedartist;
static double start_epoch;
static double pause_epoch;
static double savedlength;

void UpdatePresence(wchar_t *songname, wchar_t *artist, double tracklength, wchar_t *filename)
{
	savedsongname = util::wide_to_utf8(songname);
	savedartist = util::wide_to_utf8(artist);
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
	discordPresence.largeImageKey = "foobar";
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = savedartist;
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
	discordPresence.largeImageKey = "foobar";
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = savedartist;
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
	discordPresence.largeImageKey = "foobar";
	discordPresence.smallImageKey = "play";
	discordPresence.smallImageText = "Playing";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = savedartist;
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
	discordPresence.largeImageKey = "foobar";
	discordPresence.smallImageKey = "pause";
	discordPresence.smallImageText = "Paused";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = savedartist;
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresenceStopped()
{
	char buffer[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.largeImageKey = "foobar";
	discordPresence.smallImageKey = "stop";
	discordPresence.smallImageText = "Stopped";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.details = "Stopped";
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}