#pragma once
#include <iostream>
#include <sstream>
#include "stdafx.h"
#include "util.h"
#include "preferences.h"
#include <ctime>
#define BASE_APPID "379748462377566219"

class RpcClient
{
public:
	RpcClient();
	void Initialize();
	void UpdatePresence();
	void SetSongName(wchar_t * songname);
	void SetArtistName(wchar_t * artistname, wchar_t * albumname);
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

	const char* smallimagekey;
	const char* largeimagekey;
	const char* smallimagetext;
	const char* largeimagetext;
	const char* state;
	const char* details;
	double start;
	double end;

	char* albumcopy;
	DiscordRichPresence drp;
};