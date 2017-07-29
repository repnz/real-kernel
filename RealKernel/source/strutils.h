#pragma once
#include "int.h"

namespace string{
	word length(const char* str) {
		word len = 0;

		while (*(str++) != '\0') {
			++len;
		}

		return len;
	}
};
