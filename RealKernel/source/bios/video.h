#pragma once
#include "types.h"

 
namespace bios {
	namespace video {
		struct cell {
			byte row;
			byte column;

			cell() {}

			cell(byte row, byte column) { this->row = row; this->column = column; }


		};

		typedef byte text_color;

		namespace bios_colors {
			const text_color black = 0x0;
			const text_color blue = 0x1;
			const text_color green = 0x2;
			const text_color cyan = 0x3;
			const text_color red = 0x4;
			const text_color magenta = 0x5;
			const text_color brown = 0x6;
			const text_color grey = 0x7;
			const text_color dark_grey = 0x8;
			const text_color light_blue = 0x9;
			const text_color light_green = 0xa;
			const text_color light_cyan = 0xb;
			const text_color light_red = 0xc;
			const text_color light_magenta = 0xd;
			const text_color light_brown = 0xe;
			const text_color white = 0xf;
		}

		struct window {
			cell upperLeft;
			cell bottomRight;
		};

		typedef byte video_mode;

		namespace video_modes {
			const video_mode text_small_columns = 0x0;
			const video_mode text_medium_columns = 0x3;
			const video_mode text_big_columns = 0x14;
		}

		typedef byte write_mode;

		namespace write_modes {
			const write_mode write_characters = 0x1;
			const write_mode write_update_cursor = 0x1;
			const write_mode write_characters_attributes = 0x2;
			const write_mode write_update_cursor_attributes = 0x3;
		}

		struct cursor_info {
			byte start_scan_line;
			byte end_scan_line;
			cell location;
		};

		inline byte byte_from_halfs(byte a, byte b) {
			return ((a << 4) | b);
		}

		inline byte color_byte(text_color foreground, text_color background) {
			return byte_from_halfs((byte)background, (byte)foreground);
		}

		inline text_color get_background(byte b) {
			return b >> 4;
		}

		inline text_color get_foreground(byte b) {
			return b & 0xF;
		}

		struct cell_info {
			char character;
			text_color backgroundColor;
			text_color foregroundColor;
		};

		struct bios_color {
			text_color background;
			text_color foreground;

			bios_color(byte color) {
				background = color >> 4;
				foreground = color & 0xF;
			}

			bios_color(text_color background, text_color foreground) {
				background = background;
				foreground = foreground;
			}

			inline byte color_byte() const { return video::color_byte(foreground, background); }

		};

		
		void get_window_size(video_mode mode, byte* rows, byte* columns);
		
		void set_video_mode(video_mode mode);

		void set_cursor_size(byte width, byte height);

		void set_cursor_position(byte pageNumber, byte row, byte column);

		void get_cursor_info(byte pageNumber, cursor_info* info);

		void set_active_page(byte pageNumber);

		void scroll_up_window(const window& wnd, byte lines, bios_color color);

		void scroll_down_window(const window& wnd, byte lines, bios_color color);

		cell_info read_cursor_position_attributes(byte pageNumber);

		void write_character(const cell_info& inf, byte pageNumber = 0, word timesToPrint = 1);

		void write_character(char character, byte pageNumber = 0, word timesToPrint = 1);

		void set_background_and_border(text_color background, text_color border);

		void write_pixel(text_color pixel, word x, word y, byte pageNumber = 0);

		text_color read_pixel(word x, word y, byte pageNumber = 0);

		void teletype_write(char character, byte pageNumber = 0);
		
		void teletype_write_graphics(char character, text_color background, text_color foreground, byte pageNumber = 0);

		video_mode get_video_mode(byte* numberOfColumns = nullptr, byte* activePage = nullptr);

		void write_string(const char* str, cell location, write_mode mode = write_modes::write_update_cursor,
			byte pageNumber = 0, bios_color color = bios_color((byte)7));


	}

}