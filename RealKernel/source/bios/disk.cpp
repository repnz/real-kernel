#include "bios/disk.h"

namespace bios {
	namespace disk {
		void reset_disk_drive(byte drive) {
			__asm {
				mov dl, drive
					mov ah, 0
					int 13h
			}
		}

		operation_code get_last_operation_code(byte drive) {
			operation_code status;

			__asm {
				mov dl, drive
					mov ah, 1
					int 13h
					mov status, ah
			}

			return status;
		}

		operation_code read_sectors(byte drive, byte* buffer, byte head,
			byte sector, word cylinder, byte sectorsToRead, byte* actualReadCount) {
			operation_code status;

			word diskPlaceByte = ((cylinder & 1023) << 6) | (sector & 63);

			__asm {
				mov ax, 0
				mov es, ax
				mov al, sectorsToRead
				mov cx, diskPlaceByte
				mov dh, head
				mov dl, drive
				mov bx, buffer
				mov ah, 2
				int 13h
				mov status, ah
				push bx
				mov bx, actualReadCount
				mov BYTE PTR[bx], al
				pop bx
			}

			return status;
		}

		operation_code write_sectors(byte drive, const byte* buffer,
			byte track, byte sector, byte head, byte sectorsToWrite, byte* sectorsWritten) {

			operation_code status;

			__asm {
				mov ah, 3
					mov al, sectorsToWrite
					mov ch, track
					mov dh, head
					mov dl, drive
					mov es : bx, buffer
					int 13h
					mov status, ah
					push bx
					mov bx, sectorsWritten
					mov byte PTR[bx], al
					pop bx
			}

			return status;
		}

		inline operation_code verify_sectors(byte drive, byte* buffer, byte head,
			byte sector, byte track, byte sectorsCount, byte* verifiedCount) {
			return 0;
		}

		inline operation_code format_track(byte drive, byte* buffer, byte head,
			byte sector, byte track, byte sectorsToFormat) {
			return 0;

		}

		operation_code read_drive_parameters(byte drive, drive_parameters* parameters) {
			operation_code status;

			__asm {
				// set es:di to 0000:0000 to work around buggy drivers
				mov ax, 0
					mov es, ax
					mov di, 0


					mov ah, 08h   // read_drive_parameters function
					mov dl, drive // drive parameter
					int 13h
					mov status, ah

					// use si as a pointer to parameters
					push si
					mov si, parameters

					xor ax, ax

					// store number of hard disk drives
					mov al, dl
					mov word ptr[si], ax

					// store number of heads

					mov al, dh
					inc al
					mov word ptr[si + 2], ax

					// extract number of sectors per track
					mov al, 31
					and al, cl
					inc al
					mov word ptr[si + 4], ax

					// extract number of cylinders
					mov dx, 0xFFC0
					and dx, cx
					shr dx, 6
					mov word ptr[si + 6], dx


					// extract drive type
					xor bh, bh
					mov word ptr[si + 8], bx

					// store pointer to floppy table
					mov word ptr[si + 10], es:di

					pop si
			}

			return status;
		}
	}

}
