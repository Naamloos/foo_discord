#include "stdafx.h"

#include "message_listener.h"
#include "preferences.h"

// required to disable media key duplication when the media controls are enabled
bool message_listener::pretranslate_message(MSG* p_msg) {
	if (!preferences::get_setting_passthrough()) {
		if (p_msg->wParam == HSHELL_APPCOMMAND) {
			switch (HIWORD(p_msg->lParam)) {
			case APPCOMMAND_MEDIA_PLAY:
			case APPCOMMAND_MEDIA_PAUSE:
			case APPCOMMAND_MEDIA_PLAY_PAUSE:
			case APPCOMMAND_MEDIA_STOP:
			case APPCOMMAND_MEDIA_PREVIOUSTRACK:
			case APPCOMMAND_MEDIA_NEXTTRACK:
				return true;

			}
		}
	}
	
	return false;
} 
