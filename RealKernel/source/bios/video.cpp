#include <bios/video.h>

namespace bios {
	namespace video {
		void set_video_mode(video_mode mode) {
            asm(
                "mov ah, 0x0;"
                "mov al, mode;"
                "int 0x10;"
                );
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

            asm(
                "mov ah, 0xf;"
                "int 0x10;"
                "mov m, al;"
                "mov n1, ah;"
                "mov n2, bh;"
            );

			if (numberOfColumns != nullptr) {
				*numberOfColumns = n1;
			}

			if (activePage != nullptr) {
				*activePage = n2;
			}

            return m;
		}

		void set_cursor_size(byte width, byte height) {
            asm(
                "mov ah, 1;"
                "mov ch, width;"
                "mov cl, height;"
                "int 0x10;"
                );
		}

		void set_cursor_position(byte pageNumber, cell cell) {
            asm(
                "mov ah, 0x2;"
                "mov bh, pageNumber;"
                "mov dh, byte ptr [cell];" // row
                "mov dl, byte ptr [cell + 1];" // column
                "int 0x10;"
            );
		}

		cell get_cursor_location() {
			byte row, column;

            asm(
                "mov ah, 0x3;"
                "mov bh, 0;"
                "int 0x10;"
                "mov row, dh;"
                "mov column, dl;"
                );

			return cell(row, column);
		}

		void get_cursor_info(byte pageNumber, cursor_info* info) {
            asm(
                "push bx;"
                "mov ah, 0x3;"
                "mov bh, pageNumber;"
                "int 0x10;"
                "mov bx, info;"
                "mov byte ptr[bx], ch;" // start_scan_line
                "mov byte ptr[bx + 1], cl;" // end_scan_line
                "mov byte ptr[bx + 2], dh;" // row
                "mov byte ptr[bx + 3], dl;" // column
                "pop bx;"
                );
		}

		void set_active_page(byte pageNumber) {
            asm(
                "mov ah, 0x5;"
                "mov al, pageNumber;"
                "int 0x10;"
                );
		}

		void scroll_up_window(const window& wnd, byte lines, bios_color color) {
			
			byte color_byte = color.color_byte();
            asm(
                "push bx;"
                "mov bx, wnd;"
                "mov ch, byte ptr [bx];"   // upper row number
                "mov cl, byte ptr [bx+1];" // left column number
                "mov dh, byte ptr [bx+2];" // lower row number
                "mov dl, byte ptr [bx+3];" // right column number
                "mov bh, color_byte;"
                "mov al, lines;"
                "mov ah, 0x6;"
                "int 0x10;"
                "pop bx;"
            );
		}

		void scroll_down_window(const window& wnd, byte lines, bios_color color) {

			byte color_byte = color.color_byte();
            asm(
                "push bx;"
                "mov bx, wnd;"
                "mov ch, byte ptr[bx];" // upper row number
                "mov cl, byte ptr[bx + 1];" // left column number
                "mov dh, byte ptr[bx + 2];" // lower row number
                "mov dl, byte ptr[bx + 3];" // right column number
                "mov bh, color_byte;"
                "mov al, lines;"
                "mov ah, 0x7;"
                "int 0x10;"
                "pop bx;"
                );
		}

		cell_info read_cursor_position_attributes(byte pageNumber) {
			cell_info inf;
			byte bios_color;

            asm(
                "mov ah, 0x8;"
                "int 0x10;"
                "mov byte ptr [inf], al;"
                "mov bios_color, cl;"
                );

			inf.backgroundColor = get_background(bios_color);
			inf.foregroundColor = get_foreground(bios_color);

			return inf;
		}

		void write_character(char character, const bios_color inf, byte pageNumber, word timesToPrint) {
			byte color = inf.color_byte();

            asm(
                "mov ah, 0x9;"
                "mov al, character;"
                "mov bl, color;"
                "mov bh, pageNumber;"
                "mov cx, timesToPrint;"
                "int 0x10;"
            );

		}

		void write_character(char character, byte pageNumber, word timesToPrint) {
            asm(
                "mov ah, 0xA;"
                "mov al, character;"
                "mov bh, pageNumber;"
                "mov cx, timesToPrint;"
                "int 0x10;"
            );
		}

		void set_background_and_border(text_color background, text_color border) {
			byte param = byte_from_halfs((byte)background, (byte)border);

            asm(
                "mov ah, 0xB;"
                "mov bh, 0;"
                "mov bl, param;"
                "int 0x10;"
                );
		}

		void write_pixel(text_color pixel, word x, word y, byte pageNumber) {
			byte pixelByte = (byte)pixel;

            asm(
                "mov al, pixelByte;"
                "mov bh, pageNumber;"
                "mov cx, x;"
                "mov dx, y;"
                "mov ah, 0xC;"
                "int 0x10;"
                );
		}

		text_color read_pixel(word x, word y, byte pageNumber) {
            asm(
                "mov bh, pageNumber;"
                "mov cx, x;"
                "mov dx, y;"
                "mov ah, 0xD;"
                "int 0x10;"
                );
		}

		void teletype_write(char character, byte pageNumber) {
            asm(
                "mov al, character;"
                "mov bh, pageNumber;"
                "mov ah, 0xE;"
                "int 0x10;"
                );
		}

		void teletype_write_graphics(char character, bios_color color, byte pageNumber) {
			byte color_byte = color.color_byte();

            asm(
                "mov al, character;"
                "mov bh, pageNumber;"
                "mov bl, color_byte;"
                "mov ah, 0xE;"
                "int 0x10;"
                );
		}

		void write_string(const char* str, cell location, write_mode mode, byte pageNumber, bios_color color, word len) {
			byte color_byte = color.color_byte();

            asm(
                "mov ah, 0x08;"
                "int 0x10;"
                "mov bl, color_byte;"
                "mov al, mode;"
                "mov bh, pageNumber;"
                "mov cx, len;"
                "mov dh, byte ptr [location];"
                "mov dl, byte ptr [location + 1];"
                "mov bp, str;"
                "mov ah, 0x13;"
                "int 0x10;"
                );
		}
	}
}