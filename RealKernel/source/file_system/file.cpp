#include <file_system/file.h>
#include <file_system/directory.h>
#include <std/str.h>
#include <io/disk.h>
#include <std/arr.h>

namespace file_system {
    file file::open(const char* name) {
        file_data* data = directory::get_file_data(name);
        return file(name, data);
    }

    void file::rename(const char* name) {
        std::str_tools::copy(name, _data->name);
    }

    word file::read(byte* buf, word len) {
         
        if (_file_index >= _data->length) {
            return -1;
        }

        word read_bytes = 0;

        while (_file_index < _data->length) {
            byte* sector_buffer = get_sector();
            word bytes_to_read = min(len, io::disk::sector_size);
            std::arr::copy(sector_buffer, buf, bytes_to_read);
            len -= io::disk::sector_size;
            _file_index += bytes_to_read;
            read_bytes += bytes_to_read;
        }

        return read_bytes;
    }

    byte* file::get_sector() {
        byte block_index = (_file_index / io::disk::sector_size);
        byte sector = _data->sectors[block_index];
        return io::disk::read(sector);
    }

    void file::close() {
    }
}
