#include <io/disk_cache.h>
#include <std/arr.h>

namespace io {
    namespace disk_cache {
        const word sectors_in_cache = 10;
        const word cache_size = disk::sector_size * sectors_in_cache;
        const word free_sector = 0;
        const byte not_found = -1;

        word cache_sectors[sectors_in_cache]; // index = sector value, value = cache index
        byte cache[cache_size];
        byte used_sectors = 0;

        inline byte* cache_at(word index) {
            return  cache + (index * cache_size);
        }
        
        void defragment() {

            word old_cache_sectors[sectors_in_cache];
            
            std::arr::copy<word>(cache_sectors, old_cache_sectors, sectors_in_cache);
            std::arr::bubble_sort(cache_sectors, sectors_in_cache);
            
            // a temp buffer to use for swaps
            byte tmpBuffer[disk::sector_size];

            for (word i = 0; i < sectors_in_cache; ++i) {
                
                // the new sector block at cache index i

                word new_sector = cache_sectors[i];

                // if the cache sector needs to be free
                if (new_sector == disk_cache::free_sector) {
                    continue;
                }
                
                // get the old index of that sector value 

                word old_sector_index = std::arr::index_of<word>(
                    old_cache_sectors,
                    new_sector,
                    sectors_in_cache
                    );

                // if the sector needs to be in the same place
                if (old_sector_index == i) { 
                    continue;
                }

                // the new place of the sector in the cache is free override it 
                if (old_cache_sectors[i] == disk_cache::free_sector) {
                    std::arr::copy(
                        cache_at(old_sector_index),
                        cache_at(i),
                        disk::sector_size
                        );

                    old_cache_sectors[i] = new_sector;
                    continue;
                }

                // else replace sectors in cache

                std::arr::swap_arrays<byte>(
                    cache_at(old_sector_index),
                    cache_at(i),
                    tmpBuffer,
                    disk::sector_size
                    );

                // replace values in the old sectors array
                swap(old_cache_sectors + i, old_cache_sectors + old_sector_index);
            }



        }
        

        bool is_enough_for(word len) {
            return (sectors_in_cache - used_sectors) >= len;
        }

        byte get_free_cache_sectors(word sectors_length) {
            word last_index = sectors_in_cache - sectors_length;

            for (word i = 0; i < last_index; i++) {
                if (std::arr::compare<word>(cache_sectors, disk_cache::free_sector, sectors_length)) {
                    return i;
                }
            }

            return disk_cache::not_found;
        }

        void write_sectors(word start_sector, word cache_index, word length) {
            while (start_sector < length) {
                cache_sectors[cache_index] = start_sector;
                ++start_sector;
                ++cache_index;
            }
        }

        byte make_space(byte sectors_length) {
            std::arr::shift_left<word>(cache_sectors, sectors_length, sectors_in_cache);
            word first_new_sector_index = sectors_in_cache - sectors_length;

            for (word i = 0; i < first_new_sector_index; ++i) {
                std::arr::copy(
                    cache_at(i+sectors_length),
                    cache_at(i),
                    disk::sector_size
                    );
            }

            return first_new_sector_index;
        }

        byte* get_ptr_to_cache(word sector, word sectors_length, no_space_operation op) {
            
            if (!is_enough_for(sectors_length)) {
                if (op & operations::defragment) {
                    defragment();
                } 
                
                if (!is_enough_for(sectors_length) && (op & operations::make_space)) {
                    byte cache_index = make_space(sectors_length);
                    write_sectors(sector, cache_index, sectors_length);
                    return cache_at(cache_index);

                } else {
                    return NULL;
                }
                
            }
            

            byte cache_index = get_free_cache_sectors(sectors_length);

            if (cache_index == disk_cache::not_found) { 
                return nullptr;
            }

            write_sectors(sector, cache_index, sectors_length);

            return cache_at(cache_index);
        }

        byte* get_cached_value(word sector) {
            for (word i = 0; i < sectors_in_cache; i++) {
                if (cache_sectors[i] == sector) {
                    return cache_at(i);
                }
            }

            return nullptr;
        }
    }
}