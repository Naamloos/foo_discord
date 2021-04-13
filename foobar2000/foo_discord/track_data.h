#pragma once

#define QUERY_TITLE "title"
#define QUERY_ARTIST "artist"
#define QUERY_ALBUM "album"

#include <map>
#include <vector>

typedef std::map<const char*, wchar_t*> track_data_map;

class track_data {
public:
	track_data(metadb_handle_ptr metadb_data);
	~track_data();

	inline wchar_t* get_title() {
		return title;
	}

	inline wchar_t* get_artist() {
		return artist;
	}

	inline wchar_t* get_album() {
		return album;
	}
	inline double get_track_length() {
		return tracklen;
	}

	inline wchar_t* get_file_name() {
		return m_name;
	}


	inline album_art_data::ptr& get_album_art() {
		return m_album_art;
	}

	static wchar_t* const empty;

private:

	wchar_t* title;
	wchar_t* artist;
	wchar_t* album;

	album_art_data::ptr m_album_art = nullptr;
	wchar_t* m_name;

	double tracklen;

	static wchar_t* const genre_separator;
};