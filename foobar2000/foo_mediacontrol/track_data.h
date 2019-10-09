#pragma once

#define QUERY_TITLE "title"
#define QUERY_ARTIST "artist"
#define QUERY_ALBUM_ARTIST "album artist"
#define QUERY_ALBUM "album"
#define QUERY_TRACK_NUMBER "track number"

#include <map>

typedef std::map<const char*, wchar_t*> track_data_map;

class track_data {
public:
	track_data(metadb_handle_ptr metadb_data);

	~track_data();

	inline track_data_map& get() {
		return m_data;
	}

	inline wchar_t* get(const char* key) {
		return m_data.find(key)->second;
	}

	inline wchar_t* get_title() {
		return get(QUERY_TITLE);
	}

	inline wchar_t* get_artist() {
		return get(QUERY_ARTIST);
	}

	inline wchar_t* get_album_artist() {
		return get(QUERY_ALBUM_ARTIST);
	}

	inline wchar_t* get_album() {
		return get(QUERY_ALBUM);
	}

	inline wchar_t* get_track_number() {
		return get(QUERY_TRACK_NUMBER);
	}

	inline wchar_t* get_file_name() {
		return m_name;
	}

	inline double get_track_length() {
		return tracklength;
	}

	static wchar_t* const empty;

private:
	track_data_map m_data = {
		{ QUERY_TITLE, empty },
		{ QUERY_ARTIST, empty },
		{ QUERY_ALBUM_ARTIST, empty },
		{ QUERY_ALBUM, empty },
		{ QUERY_TRACK_NUMBER, empty }
	};

	wchar_t* m_name;
	double tracklength;

	static wchar_t* const genre_separator;
};
