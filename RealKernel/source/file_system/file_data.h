#pragma once
#include <std/inta.h>

namespace file_system {
    const byte max_sectors = 20;

    struct file_data {
        word is_used;
        char name[32];
        word length;
        word sectors[46];
    }; // 128 bytes
}