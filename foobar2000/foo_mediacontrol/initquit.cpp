#include "stdafx.h"

#include "playback_listener.h"

#include "Preferences.h"

class myinitquit : public initquit {
public:
	void on_init() {
		// create a playback listener
		m_playback_listener = new playback_listener();
	}
	void on_quit() {
		// free memory of playback listener
		delete m_playback_listener;
	}

private:
	playback_listener* m_playback_listener;

};

static initquit_factory_t<myinitquit> g_initquit_factory;
