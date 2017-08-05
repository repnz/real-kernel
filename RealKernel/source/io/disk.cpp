#include <io/disk.h>
#include <io/disk_cache.h>
#include <bios/disk.h>

namespace io {

    namespace disk {
        byte* read(word sector, word sectorsToRead) {
            return nullptr;
        }

        byte* read(word sector) {
            byte* sector_ptr = disk_cache::get_cached_value(sector);

            if (sector_ptr == nullptr) {

                sector_ptr = disk_cache::get_ptr_to_cache(
                    sector,
                    1,
                    disk_cache::operations::make_space
                    );

                if (bios::disk::read_sectors(
                    0x80,
                    sector_ptr,
                    0,
                    sector,
                    0,
                    1
                    ) != bios::disk::operation_codes::success) {
                    return nullptr;
                }

            }

            return sector_ptr;
        }

        void write(word sector, word sectorsToWrite) {

        }
    }
}