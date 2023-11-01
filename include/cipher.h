#pragma once
#include <cstdint>

class Cipher {
    virtual void Encrypt(uint8_t* plain, uint8_t* cipher, uint32_t size) = 0;
    virtual void Decrypt(uint8_t* cipher, uint8_t* plain, uint32_t size) = 0;
};
