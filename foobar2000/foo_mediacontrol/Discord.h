#include <iostream>
#include "stdafx.h"
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
	char buffer[256];
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

void UpdatePresence(wchar_t *songname, wchar_t *artist)
{
	char buffer[256];
	snprintf(buffer, 256, "%ls - %ls", artist, songname);
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.largeImageKey = "fb2000";
	discordPresence.largeImageText = "Foobar2000";
	discordPresence.state = buffer;
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}