#include "stdafx.h"

#include "track_data.h"
#include "util.h"

wchar_t* const track_data::empty = L"";
wchar_t* const track_data::genre_separator = L" / ";

track_data::track_data(metadb_handle_ptr metadb_data) {
	abort_callback_dummy abort;
	metadb_info_container::ptr container = metadb_data->get_info_ref();

	// get file name without extension as title fallback
	m_name = util::utf8_to_wide(pfc::io::path::getFileNameWithoutExtension(metadb_data->get_path()).c_str());

	if (container != nullptr) {
		const file_info& info = container->info();

		// populate basic info map
		for (track_data_map::iterator it = m_data.begin(); it != m_data.end(); ++it) {
			if (info.meta_exists(it->first)) {
				it->second = util::utf8_to_wide(info.meta_get(it->first, 0));
			}
		}

		tracklength = info.get_length();
	}
	else {
		throw pfc::exception("Could not fetch track metadata.");
	}
}

track_data::~track_data() {
	for (track_data_map::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		if (it->second != empty) {
			delete[] it->second;
		}
	}

	delete[] m_name;
}
