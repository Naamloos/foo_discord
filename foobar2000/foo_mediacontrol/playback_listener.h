#pragma once

class playback_listener : private play_callback_impl_base {
private:
	void on_playback_seek(double newtime);
	void on_playback_new_track(metadb_handle_ptr p_track);
	void on_playback_stop(play_control::t_stop_reason p_reason);
	void on_playback_pause(bool p_state);
};
