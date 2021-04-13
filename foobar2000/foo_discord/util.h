#pragma once

#include "stdafx.h"

namespace util {
	inline wchar_t* utf8_to_wide(const char* src) {
		t_size in_size;
		t_size out_size;

		in_size = strlen(src);
		out_size = pfc::stringcvt::estimate_utf8_to_wide(src, in_size);
		wchar_t* genres = new wchar_t[out_size];
		pfc::stringcvt::convert_utf8_to_wide(genres, out_size, src, in_size);

		return genres;
	}

	inline char* wide_to_utf8(const wchar_t* src) {
		t_size in_size;
		t_size out_size;

		in_size = wcslen(src);
		out_size = pfc::stringcvt::estimate_wide_to_utf8(src, in_size);
		char* genres = new char[out_size];
		pfc::stringcvt::convert_wide_to_utf8(genres, out_size, src, in_size);

		return genres;
	}
}
