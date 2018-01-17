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

static char *savedsongname;
static char *savedartist;

void UpdatePresence(wchar_t *songname, wchar_t *artist)
{
	savedsongname = util::wide_to_utf8(songname);
	savedartist = util::wide_to_utf8(artist);
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = savedsongname;
	discordPresence.largeImageKey = "fb2000";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = savedartist;
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}

void UpdatePresencePaused()
{
	char buffer[256];
	sprintf_s(buffer, 256, "%s (Paused)", savedsongname);
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = buffer;
	discordPresence.largeImageKey = "fbpause";
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
	discordPresence.largeImageKey = "fbstop";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.details = "Stopped";
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}