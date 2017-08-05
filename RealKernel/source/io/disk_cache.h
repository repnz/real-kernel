#include <io/disk.h>

namespace io {
    namespace disk_cache {
        
        typedef byte no_space_operation;

        namespace operations {
            const no_space_operation return_error = 0x0;
            const no_space_operation defragment = 0x1;
            const no_space_operation make_space = 0x2;
        }

        

        byte* get_ptr_to_cache(word sector, word freeLength, no_space_operation op = operations::return_error);

        byte* get_cached_value(word sector);

        byte* get_continuous_memory(word sector, word sectorsToRead);

        void defragment();
    }
}