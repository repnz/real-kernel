#include <std/arr.h>

namespace std {

    namespace arr {        

        bool compare(const char* left, const char* right, word len) {
            for (word i = 0; i < len; ++i) {
                if (left[i] != right[i]) {
                    return false;
                }
            }

            return true;
        }

        template <typename T> 
        void bubble_sort(T* arr, word len) {

            for (word i = 0; i < len; ++i) {
                for (word j = i+1; j < len; j++) {
                    if (arr[i] > arr[j]) {
                        swap(arr + i, arr + j);
                    }
                }
            }
        }


        void bubble_sort(byte* arr, word len) {
            return bubble_sort<byte>(arr, len);
        }

        void bubble_sort(word* arr, word len) {
            return bubble_sort<word>(arr, len);
        }
    }
}