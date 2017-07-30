#pragma once
#include "types.h"

namespace str_tools {
	word length(const char* str);

	bool equals_length(const char* left, const char* right, word bothLen);

	bool equals_length(const char* left, const char* right, word leftLen, word rightLen);

	bool equals_until(const char* left, const char* right, char c);

	inline bool equals(const char* left, const char* right) {
		return equals_until(left, right, 0);
	}
};
