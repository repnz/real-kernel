#include "os\console.h"
#include "bios\video.h"
#include "bios\keyboard.h"

using namespace bios;

namespace os {
	namespace console {
		void print_char(char c) {
			video::teletype_write(c);
		}

		void print_line() {
			video::teletype_write('\r');
			video::teletype_write('\n');
		}

		void print_string(const char* str) {
			while (true) {
				char s = *str;

				if (s == 0)
					return;

				video::teletype_write(s);

				++str;
			}
		}

		void print_string(const char* str, word len) {
			for (int i = 0; i < len; i++) {
				video::teletype_write(*str);
				++str;
			}
		}

		void print_hex(word w, byte bytes) {
			bool stepover_zero = true;
			byte shift = (bytes * 8) - 4;

			for (byte i = bytes * 2; i > 0; i--, shift -= 4) {
				char c = ((w >> shift) & 0xF) + 48;

				if (c > '9') {
					c += 7;
				}

				if (c != '0' || (!stepover_zero || shift == 0)) {
					video::teletype_write(c);
					stepover_zero = false;
				}
			}
		}

		void print_mem(byte* b, word len) {
			for (word i = 0; i < len; ++i) {
				print_hex(b[i], 1);
				video::teletype_write(' ');
			}
		}
	}
}