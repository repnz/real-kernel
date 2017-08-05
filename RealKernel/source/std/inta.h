#pragma once

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned long   dword;

#define NULL 0

template <typename T>
void swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}