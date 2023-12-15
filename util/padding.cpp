#include "util/padding.h"
#include <iostream>
// PKCS#7 Padding

Bytes Pad(Bytes& data, uint8_t pad_size) {
    uint8_t pad_byte = pad_size - data.size() % 16;
    Bytes padding(pad_byte, pad_byte);
    return data + padding;
}

Bytes Unpad(Bytes& data, uint8_t pad_size) {
    if (data.size() % pad_size != 0)
        throw std::length_error("Unpad Error : Incorrect data size");
        
    uint8_t pad_byte = *(data.data() + data.size() - 1); 
    for (uint8_t i = 0; i < pad_byte; i++) {
        if (*(data.data() + data.size()-i-1) != pad_byte)
            throw std::length_error("Unpad Error : Incorrect padding");
    }
    uint8_t unpad_size = data.size()-pad_byte;
    uint8_t* unpad_data = new uint8_t[unpad_size];
    memcpy(unpad_data, data.data(), unpad_size);
    return Bytes(unpad_data, unpad_size);
}