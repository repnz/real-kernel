#include "bios/video.h"
#include "strutils.h"

namespace bios {
	namespace video {
		void set_video_mode(video_mode mode) {
			__asm {
					mov ah, 00h
					mov al, mode
					int 10h
			}
		}
		
		void get_window_size(video_mode mode, byte* rows, byte* columns) {
			switch (mode) {
			case video_modes::text_small_columns:
				*rows = 40;
				*columns = 25;
				break;
			case video_modes::text_medium_columns:
				*rows = 80;
				*columns = 25;
				break;
			case video_modes::text_big_columns:
				*rows = 132;
				*columns = 25;
				break;
			}
		}

		video_mode get_video_mode(byte* numberOfColumns, byte* activePage) {
			byte n1, n2;
			video_mode m;

			__asm {
				mov ah, 0xf
				int 10h	
				mov m, al
				mov n1, ah
				mov n2, bh
			}

			if (numberOfColumns != nullptr) {
				*numberOfColumns = n1;
			}

			if (activePage != nullptr) {
				*activePage = n2;
			}
		}

		void set_cursor_size(byte width, byte height) {
			__asm {
					mov ah, 01h
					mov ch, width
					mov cl, height
					int 10h
			}
		}

		void set_cursor_position(byte pageNumber, byte row, byte column) {
			__asm {
					mov ah, 02h
					mov bh, pageNumber,
					mov dh, row
					mov dl, column
					int 10h
			}
		}

		void get_cursor_info(byte pageNumber, cursor_info* info) {

			__asm {
					mov ah, 03h
					mov bh, pageNumber
					int 10h
					mov byte ptr[info], ch
					mov byte ptr[info + 1], cl
					mov byte ptr[info + 2], dh
					mov byte ptr[info + 3], dl
			}
		}

		void set_active_page(byte pageNumber) {
			__asm {
					mov ah, 05h
					mov al, pageNumber
					int 10h
			}
		}

		void scroll_up_window(const window& wnd, byte lines, bios_color color) {
			
			byte color_byte = color.color_byte();
			__asm {
				
				push bx
				mov bx, wnd
				mov ch, byte ptr [bx]   // upper row number
				mov cl, byte ptr [bx+1] // left column number
				mov dh, byte ptr [bx+2] // lower row number
				mov dl, byte ptr [bx+3] // right column number
				mov bh, color_byte
				mov al, lines
				mov ah, 0x6
				int 10h
				pop bx
			}
		}

		void scroll_down_window(const window& wnd, byte lines, bios_color color) {

			byte color_byte = color.color_byte();
			__asm {

				push bx
					mov bx, wnd
					mov ch, byte ptr[bx]   // upper row number
					mov cl, byte ptr[bx + 1] // left column number
					mov dh, byte ptr[bx + 2] // lower row number
					mov dl, byte ptr[bx + 3] // right column number
					mov bh, color_byte
					mov al, lines
					mov ah, 0x7
					int 10h
					pop bx
			}
		}

		cell_info read_cursor_position_attributes(byte pageNumber) {
			cell_info inf;
			byte bios_color;

			__asm {
					mov ah, 8h
					int 10h
					mov byte ptr [inf], al
					mov bios_color, cl
			}

			inf.backgroundColor = get_background(bios_color);
			inf.foregroundColor = get_foreground(bios_color);

			return inf;
		}

		inline void write_character(char character, const bios_color inf, byte pageNumber, word timesToPrint) {
			byte color = inf.color_byte();

			__asm {
					mov ah, 09h
					mov al, character
					mov bl, color
					mov bh, pageNumber
					mov cx, timesToPrint
					int 10h
			}

		}

		void write_character(char character, byte pageNumber, word timesToPrint) {
			__asm {
					mov ah, 0Ah
					mov al, character
					mov bh, pageNumber
					mov cx, timesToPrint
					int 10h
			}
		}

		void set_background_and_border(text_color background, text_color border) {
			byte param = byte_from_halfs((byte)background, (byte)border);

			__asm {
					mov ah, 0Bh
					mov bh, 00h
					mov bl, param
					int 10h
			}
		}

		void write_pixel(text_color pixel, word x, word y, byte pageNumber) {
			byte pixelByte = (byte)pixel;

			__asm {
					mov al, pixelByte
					mov bh, pageNumber
					mov cx, x
					mov dx, y
					mov ah, 0Ch
					int 10h
			}
		}

		text_color read_pixel(word x, word y, byte pageNumber) {
			__asm {
				mov bh, pageNumber
				mov cx, x
				mov dx, y
				mov ah, 0Dh
				int 10h
			}
		}

		void teletype_write(char character, byte pageNumber) {
			__asm {
				mov al, character
				mov bh, pageNumber
				mov ah, 0Eh
				int 10h
			}
		}

		void teletype_write_graphics(char character, bios_color color, byte pageNumber) {
			byte color_byte = color.color_byte();

			__asm {
				mov al, character
				mov bh, pageNumber
				mov bl, color_byte
				mov ah, 0Eh
				int 10h
			}
		}

		void write_string(const char* str, cell location, write_mode mode, byte pageNumber, bios_color color) {
			word len = string::length(str);
			byte color_byte = color.color_byte();

			__asm {
				mov ah, 08h
				int 10h
				mov bl, color_byte
				mov al, mode
				mov bh, pageNumber
				mov cx, len
				mov dh, byte ptr [location]
				mov dl, byte ptr [location + 1]
				mov es:bp, str
				mov ah, 13h
				int 10h
			}
		}
	}
}