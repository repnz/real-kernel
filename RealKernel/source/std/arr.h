#pragma once
#include <std/inta.h>

namespace std {

    namespace arr {

        template <typename T>
        void copy(const T* src, T* dst, word len) {
            for (word i = 0; i < len; ++i) {
                *(dst+i) = *(src+i);
            }
        }

        template <typename T>
        void swap_arrays(T* a, T* b, T* tmp_buffer, word len) {
            copy(a, tmp_buffer, len);
            copy(b, a, len);
            copy(tmp_buffer, b, len);
        }

        template <typename T>
        void shift_left(T* a, word shift, word len, word default_value = 0) {
            word last_shift = len - shift;

            for (word i = 0; i < last_shift; ++i) {
                a[i] = a[i + shift];
            }

            for (word i = last_shift; i < len; ++i) {
                a[i] = default_value;
            }
        }

        bool compare(const byte* left, const byte* right, word len);

        template <typename T> 
        bool compare(const T* arr, T value, word len) {
            for (word i = 0; i < len; ++i) {
                if (arr[i] != value) {
                    return false;
                }
            }

            return true;
        }

        template <typename T>
        word index_of(const T* arr, T value, word len) {
            for (word i = 0; i < len; ++i) {
                if (arr[i] == value) { return i; }
            }

            return -1;
        }

        void bubble_sort(byte* arr, word len);

        void bubble_sort(word* arr, word len);


    }

}