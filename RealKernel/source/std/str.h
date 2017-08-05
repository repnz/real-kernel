#pragma once
#include <std/inta.h>

namespace std {
	namespace str_tools {
		word length(const char* str);

		bool equals_length(const char* left, const char* right, word bothLen);

		bool equals_length(const char* left, const char* right, word leftLen, word rightLen);

		bool equals_until(const char* left, const char* right, char c);

		inline bool equals(const char* left, const char* right) {
			return equals_until(left, right, 0);
		}

        void copy(const char* src, char* dst);
	};

}

