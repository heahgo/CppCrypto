#pragma once
#include <cstdint>

class Cipher {
    virtual uint8_t* Encrypt(uint8_t* cipher, uint32_t size) = 0;
    virtual uint8_t* Decrypt(uint8_t* cipher, uint32_t size) = 0;
};
