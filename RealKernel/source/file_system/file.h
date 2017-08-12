#pragma once
#include <std/inta.h>
#include <file_system/file_data.h>

namespace file_system {
    class file {
    private:
        file_data* _data;
        word _file_index;
        word _sector_index;
        const char* _name;
        file(const char* name, file_data* data) : _name(name), _data(data) {}
        byte* get_sector();
    public:
        static file open(const char* name);
        const char* name() const { return _name; }
        void rename(const char* name);
        word read(byte* buf, word len);
        void write(byte* buf, word len);
        void seek(word index, byte dir);
        void close();
    };
}