#include <io/disk.h>
#include <io/disk_cache.h>
#include <bios/disk.h>
#include <ui/console.h>

namespace io {

    namespace disk {
        byte* read(word sector, word sectorsToRead) {
            return nullptr;
        }

        byte* read(word sector) {
            ui::console::print_string("fetching sector 0x");
            ui::console::print_hex(sector, 2);
            ui::console::print_line();

            byte* sector_ptr = disk_cache::get_cached_value(sector);

            ui::console::print_string("cached ptr=");
            ui::console::print_hex((word)sector_ptr, 2);
            ui::console::print_line();

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