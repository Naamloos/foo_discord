#pragma once

#include "resource.h"

#define PREFERENCES_SECTION_NAME "Discord Rich Presences"

class preferences : public CDialogImpl<preferences>, public preferences_page_instance {
public:
	preferences(preferences_page_callback::ptr callback) : m_callback(callback) {}

	enum { IDD = IDD_PREFERENCES };

	BEGIN_MSG_MAP(CPreferences)
		MSG_WM_INITDIALOG(on_init)
		COMMAND_HANDLER_EX(IDC_PREFERENCES_PASSTHROUGH, BN_CLICKED, on_edit)
		COMMAND_HANDLER_EX(IDC_SHOWSTOP, BN_CLICKED, on_edit)
		COMMAND_HANDLER_EX(IDC_SHOWSONGSTOP, BN_CLICKED, on_edit)
		COMMAND_HANDLER_EX(IDC_SHOWALBUM, BN_CLICKED, on_edit)
		COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)
		COMMAND_HANDLER(IDC_BUTTON2, BN_CLICKED, OnBnClickedButton2)
		COMMAND_HANDLER(IDC_BUTTON3, BN_CLICKED, OnBnClickedButton3)
	END_MSG_MAP()

	t_uint32 get_state();
	void apply();
	void reset();

	inline static bool get_show_image() { return show_image; }
	inline static bool get_show_stop() { return show_stop; }
	inline static bool get_show_songstop() { return show_songstop; }
	inline static bool get_show_album() { return show_album; }

private:
	BOOL on_init(CWindow, LPARAM);
	void on_edit(UINT, int, CWindow);
	void on_changed();

	preferences_page_callback::ptr m_callback;

	static const GUID guid_show_image;
	static const GUID guid_show_stop;
	static const GUID guid_show_songstop;
	static const GUID guid_show_album;
	static const GUID guid_advconfig_branch;

	static cfg_bool show_image;
	static cfg_bool show_stop;
	static cfg_bool show_songstop;
	static cfg_bool show_album;

	static advconfig_branch_factory g_advconfig_branch;
public:
	LRESULT OnNMClickSyslink1(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButton2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButton3(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};

class preferences_page_custom_impl : public preferences_page_impl<preferences> {
public:
	const char * get_name() { return PREFERENCES_SECTION_NAME; }
	GUID get_guid() {
		static const GUID guid = { 0x779304fc, 0x27da, 0x4bad,{ 0xaf, 0x72, 0x8c, 0x4b, 0xeb, 0x2c, 0xd4, 0x69 } };
		return guid;
	}
	GUID get_parent_guid() { return guid_tools; }

};