#pragma once
#include <std/inta.h>

namespace io {
    namespace disk {
        const word sector_size = 512;

        byte* read(word sector);

        byte* read(word sector, word sectorsToRead);

        void write(word sector, word sectorsToWrite);
    }
}