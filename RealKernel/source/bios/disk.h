#pragma once 
#include "types.h"

namespace bios {
	namespace disk {

		typedef byte operation_code;

		namespace operation_codes {
			const operation_code success = 0x00;
			const operation_code invalid_command = 0x01;
			const operation_code cannot_find_address_mark = 0x02;
			const operation_code write_protected_attempt = 0x03;
			const operation_code sector_not_found = 0x04;
			const operation_code reset_failed = 0x05;
			const operation_code disk_change_line_active = 0x06;
			const operation_code drive_activity_failed = 0x07;
			const operation_code dma_overrun = 0x08;
			const operation_code dma_over_64k = 0x09;
			const operation_code bad_sector = 0x0a;
			const operation_code bad_cylinder = 0x0b;
			const operation_code media_type_not_found = 0x0c;
			const operation_code invalid_number_of_sectors = 0x0d;
			const operation_code control_data_access_mark = 0x0e;
			const operation_code dma_out_of_range = 0x0f;
			const operation_code crc_ecc_error = 0x10;
			const operation_code controller_failure = 0x20;
			const operation_code seek_failure = 0x21;
			const operation_code drive_timed_out = 0x80;
			const operation_code drive_not_ready = 0xaa;
			const operation_code undefined_error = 0xbb;
			const operation_code write_fault = 0xcc;
			const operation_code status_error = 0xe0;
			const operation_code sense_operation_failed = 0xff;
		}

		typedef struct _floppy_table {

		} floppy_table;

		typedef struct _drive_parameters {
			byte disk_drives_count;
			byte heads_count;
			word cylinder_count;
			byte sector_count;
			byte sectors_per_track_count;
			byte drive_type;
			floppy_table* floppy;
		} drive_parameters;



		void reset_disk_drive(byte drive);

		operation_code get_last_operation_code(byte drive);

		operation_code read_sectors(byte drive, byte* buffer, byte head,
			byte sector, word cylinder, byte sectorsToRead, byte* actualReadCount = nullptr);
		
		operation_code write_sectors(byte drive, const byte* buffer,
			byte track, byte sector, byte head, byte sectorsToWrite, byte* sectorsWritten);

		operation_code verify_sectors(byte drive, byte* buffer, byte head,
			byte sector, byte track, byte sectorsCount, byte* verifiedCount);

		operation_code format_track(byte drive, byte* buffer, byte head,
			byte sector, byte track, byte sectorsToFormat);


		operation_code read_drive_parameters(byte drive, drive_parameters* parameters);


	}
}