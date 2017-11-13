#include "stdafx.h"

#include "playback_listener.h"
#include "media_controls.h"
#include "track_data.h"
#include <time.h>
#include "Discord.h"

bool init = false;

void playback_listener::on_playback_new_track(metadb_handle_ptr p_track) {
	try {
		// create new track data from metadb handle
		track_data data(p_track);

		// update the media controls
		media_controls::get()
			.begin_update()
			.set_title(data.get_title() != track_data::empty ? data.get_title() : data.get_file_name())
			.set_artist(data.get_artist())
			.set_genres(data.get_genres())
			.set_album(data.get_album())
			.set_album_artist(data.get_album_artist())
			.set_track_number(data.get_track_number())
			.set_thumbnail(data.get_album_art())
			.end_update();

		if (init == false) {
			discordInit();
			init = true;
		}
		
		UpdatePresence(data.get_title(), data.get_artist());
	}
	catch (pfc::exception e) {
		popup_message::g_show("Caught exception", "Error");
	}
}

void playback_listener::on_playback_starting(play_control::t_track_command p_command, bool p_paused) {
	media_controls::get().play();
}

void playback_listener::on_playback_stop(play_control::t_stop_reason p_reason) {
	if (p_reason != play_control::t_stop_reason::stop_reason_starting_another) {
		media_controls::get().stop();
	}
}

void playback_listener::on_playback_pause(bool p_state) {
	if (p_state) {
		media_controls::get().pause();
	}
	else {
		media_controls::get().play();
	}
}