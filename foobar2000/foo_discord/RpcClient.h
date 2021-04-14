#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <ctime>

#include "util.h"
#include "preferences.h"
#include "discord/discord.h"

#define BASE_APPID 379748462377566219

class RpcClient
{
public:
	RpcClient();
	void Initialize();
	void UpdatePresence();
	void SetSongName(wchar_t* songname);
	void SetArtistName(wchar_t* artistname, wchar_t* albumname);
	void SetTimer(double length, bool storelen);
	void ResumeTimer();
	void SeekTimer(double time);
	void KillTimer();
	void SetPlay();
	void SetPause();
	void SetStop();
	void Disconnect();
	bool IsInitialized();
	~RpcClient();
	static RpcClient rpc;

private:
	const char* getArtType();
	bool hasTimer = false;
	bool initialized = false;
	double songlength = 0;
	double pausetime = 0;
	double starttime = 0;
	double foostarttime = 0;

	char _smallimagekey[128] = "";
	char* smallimagekey = &*_smallimagekey;

	char _largeimagekey[128] = "";
	char* largeimagekey = &*_largeimagekey;

	char _smallimagetext[128] = "";
	char* smallimagetext = &*_smallimagetext;

	char _largeimagetext[128] = "";
	char* largeimagetext = &*_largeimagetext;

	char _state[128] = "";
	char* state = &*_state;

	char _details[128] = "";
	char* details = &*_details;


	double start;
	double end;

	char _albumcopy[128] = "";
	char* albumcopy = &*_albumcopy;
};