#include <helpers/foobar2000+atl.h>

#include "playback_listener.h"
#include "track_data.h"

void playback_listener::on_playback_new_track(metadb_handle_ptr p_track) {
	try {
		// create new track data from metadb handle
		track_data data(p_track);

		// When we're playing a new track, I want to send all this new metadata to
		// the RPC client.
		RpcClient::rpc.SetArtistName(data.get_artist(), data.get_album());
		RpcClient::rpc.SetSongName(data.get_title());
		RpcClient::rpc.SetPlay();
		RpcClient::rpc.SetTimer(data.get_track_length(), true);

		// After changing all these values, we go and update the presence.
		RpcClient::rpc.UpdatePresence();
	}
	catch (pfc::exception e) {
		popup_message::g_show("Caught exception", "Error");
	}
}

void playback_listener::on_playback_seek(double newtime) {
	// We're sending the RPC Client the new time.
	RpcClient::rpc.SeekTimer(newtime);
	// Aaaaand of course we're updating the presence.
	RpcClient::rpc.UpdatePresence();
}

void playback_listener::on_playback_stop(play_control::t_stop_reason p_reason) {
	if (p_reason != play_control::t_stop_reason::stop_reason_starting_another) {
		// We're stopping playback. Tell it to the gosh darn RPC Client.
		RpcClient::rpc.SetStop();
		// Killing the timer, stopping a song means there's no timer.
		RpcClient::rpc.KillTimer();

		// Updating the presence.
		RpcClient::rpc.UpdatePresence();
	}
}

void playback_listener::on_playback_pause(bool p_state) {
	// If p_state is true, we've paused playback.
	if (p_state) {
		// Telling the RPC Client it's paused and killing the timer.
		RpcClient::rpc.SetPause();
		RpcClient::rpc.KillTimer();
	}
	else {
		// Telling the RPC Client it has resumed playback and resuming the timer.
		RpcClient::rpc.SetPlay();
		RpcClient::rpc.ResumeTimer();
	}

	// Updating the presence.
	RpcClient::rpc.UpdatePresence();
}