#include "../include/util/padding.h"
// PKCS#7 Padding

string pad(string data, uint32_t pad_size) {
    uint32_t data_size = data.size();
    uint8_t pad_byte = pad_size - data_size % pad_size;
    string pad_data(data);
    pad_data.resize(data_size + pad_byte);
    for (uint32_t i = 0; i < pad_byte; i++) 
        pad_data[data_size+i] = pad_byte;
    return pad_data;
}

string unpad(string data, uint32_t pad_size) {
    uint32_t data_size = data.size();
    if (data_size % pad_size != 0)
        throw std::length_error("unpad() Error : Incorrect data size");
    uint8_t pad_byte = data[data_size-1];
    for (uint32_t i = 1; i < pad_byte+1; i++) {
        if (data[data_size-i] != pad_byte)
            throw std::out_of_range("unpad() Error : Incorrect Padding");
    }
    string unpad_data(data);
    unpad_data.resize(data_size - pad_byte);
    return unpad_data;
}