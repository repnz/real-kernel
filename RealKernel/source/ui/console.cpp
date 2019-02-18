#include <ui/console.h>
#include <bios/video.h>
#include <bios/keyboard.h>

using namespace bios;

namespace ui {
	namespace console {

		void clear() {
            /*
			__asm {
				pusha
				mov ax, 0x0700 //; function 07, AL = 0 means scroll whole window
				mov bh, 0x07 //; character attribute = white on black
				mov cx, 0x0000 //; row = 0, col = 0
				mov dx, 0x184f //; row = 24 (0x18), col = 79 (0x4f)
				int 0x10 //; call BIOS video interrupt
				popa
			}

			video::set_cursor_position(0, video::cell(0, 0));

            */
		}

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

		word read_line(char* buffer, word len) {

			video::cursor_info inf;
			video::get_cursor_info(0, &inf);
			video::cell pos = inf.location;

			len--;
			word i = 0;
			word bufferLastIndex = 0;

			while (true) {				
				keyboard::press_info press = keyboard::read_press();

				switch (press.scanCode) {
				case keyboard::scan_codes::Enter:
					buffer[i] = 0;
					return i;
				case keyboard::scan_codes::BackSpace:
					if (i > 0) {
						pos.column--;
						video::set_cursor_position(0, pos);
						print_char(' ');
						video::set_cursor_position(0, pos);
						buffer[i] = 0;
						--i;
					}

					break;
				case keyboard::scan_codes::LeftArrow:
					if (i > 0) {
						pos.column--;
						video::set_cursor_position(0, pos);
					}
					
					break;

				case keyboard::scan_codes::RightArrow:
					if (i < bufferLastIndex) {
						pos.column++;
						video::set_cursor_position(0, pos);
					}

				break;

				default:
					if (i < len && press.asciiChar != 0) {
						print_char(press.asciiChar);
						buffer[i] = press.asciiChar;
						++i;
					}

					pos.column++;
					bufferLastIndex++;
				}
			}
		}
	}
}