#include "stdafx.h"

#include "track_data.h"
#include "util.h"

wchar_t* const track_data::empty = const_cast<wchar_t*>(L"");
wchar_t* const track_data::genre_separator = const_cast<wchar_t*>(L" / ");

track_data::track_data(metadb_handle_ptr metadb_data) {
	abort_callback_dummy abort;
	metadb_info_container::ptr container = metadb_data->get_async_info_ref();

	// get file name without extension as title fallback
	m_name = util::utf8_to_wide(pfc::io::path::getFileNameWithoutExtension(metadb_data->get_path()).c_str());

	if (container != nullptr) {
		const file_info& info = container->info();

		if (info.meta_exists(QUERY_TITLE)) {
			title = util::utf8_to_wide(info.meta_get(QUERY_TITLE, 0));
		}

		if (info.meta_exists(QUERY_ALBUM)) {
			album = util::utf8_to_wide(info.meta_get(QUERY_ALBUM, 0));
		}

		if (info.meta_exists(QUERY_ARTIST)) {
			artist = util::utf8_to_wide(info.meta_get(QUERY_ARTIST, 0));
		}

		this->tracklen = info.get_length();
	}
	else {
		throw pfc::exception("Could not fetch track metadata.");
	}
}

track_data::~track_data() {
	delete[] m_name;
}
