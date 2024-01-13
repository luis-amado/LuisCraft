#include "NibbleArray.h"
#include <iostream>

NibbleArray::NibbleArray()
    : size(0), data(nullptr) {}

NibbleArray::NibbleArray(unsigned int _size)
    : size(_size) {

    data = new unsigned char[(size+1) / 2];
}

NibbleArray::~NibbleArray() {
    delete[] data;
}

void NibbleArray::init(unsigned int _size, unsigned char initialData) {
    size = _size;
    data = new unsigned char[(size + 1) / 2];

    unsigned char initData = initialData | (initialData << 4);
    for (int i = 0; i < (size + 1) / 2; i++) {
        data[i] = initData;
    }
}

void NibbleArray::set(unsigned int index, unsigned char newData) {
    // convert index into position in the array, and the side of the byte
    unsigned int position = index / 2;
    char side = index % 2;

    unsigned char mask;

    if (side == 0) {
        mask = 0b00001111;
    } else {
        mask = 0b11110000;
        newData <<= 4;
    }

    data[position] = (newData & mask) | (data[position] & ~mask);

}

unsigned char NibbleArray::get(unsigned int index) const {
    unsigned int position = index / 2;
    char side = index % 2;

    if (side == 0) {
        return data[position] & 0b00001111;
    } else {
        return data[position] >> 4;
    }

}