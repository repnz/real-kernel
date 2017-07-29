#pragma once
#include "types.h"

namespace bios {
	namespace keyboard {

		struct press_info {
			byte scanCode;
			char asciiChar;
		};

		press_info read_press();

		char read_press_char();

		byte read_press_scan_code();
	}
}