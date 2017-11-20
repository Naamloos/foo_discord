#include "stdafx.h"

#include "track_data.h"
#include "util.h"

wchar_t* const track_data::empty = L"";
wchar_t* const track_data::genre_separator = L" / ";

track_data::track_data(metadb_handle_ptr metadb_data) {
	abort_callback_dummy abort;
	metadb_info_container::ptr container = metadb_data->get_async_info_ref();

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
		
		// populate genre vector
		if (info.meta_exists("genre")) {
			wchar_t* genres = util::utf8_to_wide(info.meta_get("genre", 0));

			size_t off = 0;
			size_t i = std::string::npos;

			wchar_t* context;
			wchar_t* substring = wcstok_s(genres, genre_separator, &context);

			while (substring) {
				substring = wcstok_s(nullptr, genre_separator, &context);
			}

			delete[] genres;
		}
	}
	else {
		throw pfc::exception("Could not fetch track metadata.");
	}

	// populate album art data buffer (fallback in the order front->back->disc->artist->icon)
	pfc::list_t<GUID> ids;
	ids.add_item(album_art_ids::cover_front);
	ids.add_item(album_art_ids::cover_back);
	ids.add_item(album_art_ids::disc);
	ids.add_item(album_art_ids::artist);
	ids.add_item(album_art_ids::icon);

	metadb_handle_list tracks;
	tracks.add_item(metadb_data);

	album_art_extractor_instance_v2::ptr extractor = static_api_ptr_t<album_art_manager_v2>()->open(tracks, ids, abort);

	for (byte i = 0; i < ids.get_count(); ++i) {
		if (extractor->query(ids[i], m_album_art, abort)) {
			break;
		}
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
