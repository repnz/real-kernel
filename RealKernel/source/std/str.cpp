#include <std/str.h>

namespace std {

	namespace str_tools {
		bool equals_length(const char* left, const char* right, word leftLen, word rightLen) {
			if (leftLen != rightLen) {
				return false;
			}

			return equals_length(left, right, leftLen);
		}

		bool equals_length(const char* left, const char* right, word len) {
			for (word i = 0; i < (len - 1); i++) {
				register char a = *left;
				register char b = *right;

				if (a != b || !a || !b) {
					return false;
				}

				++left;
				++right;
			}

			return true;
		}

		bool equals_until(const char* left, const char* right, char c) {

			while (true) {
				register char a = *left;
				register char b = *right;

				if (a == 0) {
					return (b == c) || (b == 0);
				} else if (a == b) {
					if (a == c) {
						return true;
					}

					++left;
					++right;
				} else {
					return false;
				}
			}
		}

		word length(const char* str) {
			register word len = 0;

			while (*(str++) != '\0') {
				++len;
			}

			return len;
		}


        void copy(const char* src, char* dst) {
            while (true) {
                register char a = *src;
                
                if (a == 0) {
                    return;
                }

                *dst = a;
                ++dst;
                ++src;
            }
        }
	}
}
