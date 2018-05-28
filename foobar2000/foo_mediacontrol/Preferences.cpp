#include "stdafx.h"

#include "preferences.h"

const GUID preferences::guid_show_image = { 0x7d8a2294, 0x36d0, 0x4ee9,{ 0xaa, 0x71, 0x36, 0x70, 0x5f, 0x0f, 0x43, 0x70 } };
const GUID preferences::guid_show_stop = { 0x7d8a2294, 0x36d0, 0x4ee9,{ 0xaa, 0x71, 0x36, 0x70, 0x5f, 0x0f, 0x43, 0x69 } };
const GUID preferences::guid_show_songstop = { 0x7d8a2294, 0x36d0, 0x4ee9,{ 0xaa, 0x71, 0x36, 0x70, 0x5f, 0x0f, 0x43, 0x68 } };
const GUID preferences::guid_show_album = { 0x7d8a2294, 0x36d0, 0x4ee9,{ 0xaa, 0x71, 0x36, 0x70, 0x69, 0x0f, 0x43, 0x53 } };

const GUID preferences::guid_advconfig_branch = { 0x1260bbfa, 0x0806, 0x434e,{ 0x91, 0x7c, 0xc8, 0x91, 0x89, 0xd3, 0x9c, 0x88 } };

cfg_bool preferences::show_image(guid_show_image, true);
cfg_bool preferences::show_stop(guid_show_stop, true);
cfg_bool preferences::show_songstop(guid_show_songstop, false);
cfg_bool preferences::show_album(guid_show_album, false);
advconfig_branch_factory preferences::g_advconfig_branch(PREFERENCES_SECTION_NAME, guid_advconfig_branch, advconfig_branch::guid_branch_tools, 0);

BOOL preferences::on_init(CWindow, LPARAM) {
	uButton_SetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH, show_image);
	uButton_SetCheck(this->m_hWnd, IDC_SHOWSTOP, show_stop);
	uButton_SetCheck(this->m_hWnd, IDC_SHOWSONGSTOP, show_songstop);
	uButton_SetCheck(this->m_hWnd, IDC_SHOWALBUM, show_album);

	return FALSE;
}

void preferences::on_edit(UINT, int, CWindow) {
	on_changed();
}

void preferences::on_changed() {
	m_callback->on_state_changed();
}

t_uint32 preferences::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (uButton_GetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH) != show_image) {
		state |= preferences_state::changed;
	}
	if (uButton_GetCheck(this->m_hWnd, IDC_SHOWSTOP) != show_stop) {
		state |= preferences_state::changed;
	}
	if (uButton_GetCheck(this->m_hWnd, IDC_SHOWSONGSTOP) != show_songstop) {
		state |= preferences_state::changed;
	}
	if (uButton_GetCheck(this->m_hWnd, IDC_SHOWALBUM) != show_album) {
		state |= preferences_state::changed;
	}

	return state;
}

void preferences::apply() {
	show_image = uButton_GetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH);
	show_stop = uButton_GetCheck(this->m_hWnd, IDC_SHOWSTOP);
	show_songstop = uButton_GetCheck(this->m_hWnd, IDC_SHOWSONGSTOP);
	show_album = uButton_GetCheck(this->m_hWnd, IDC_SHOWALBUM);

	on_changed();
}

void preferences::reset() {
	show_image = true;
	show_stop = true;
	show_songstop = false;
	show_album = false;

	on_changed();
}

static preferences_page_factory_t<preferences_page_custom_impl> g_preferences_page_factory;