#include <helpers/foobar2000+atl.h>

#include "playback_listener.h"

#include "Preferences.h"
#include "RpcClient.h"

class myinitquit : public initquit {
public:
	void on_init() {
		// Create a playback listener
		m_playback_listener = new playback_listener();
		// Initialize the RPC Client
		RpcClient::rpc.Initialize();
	}
	void on_quit() {
		// Disconnect the current RPC Client.
		RpcClient::rpc.Disconnect();
		// Free memory of playback listener
		delete m_playback_listener;
	}

private:
	playback_listener* m_playback_listener;
};

static initquit_factory_t<myinitquit> g_initquit_factory;