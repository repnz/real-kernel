#pragma once
#include <std/inta.h>
#include <bios/keyboard_codes.h>

namespace bios {
	namespace keyboard {

		struct press_info {
			scan_code scanCode;
			char asciiChar;
		};

		press_info read_press();

		char read_press_char();

		scan_code read_press_scan_code();
	}
}