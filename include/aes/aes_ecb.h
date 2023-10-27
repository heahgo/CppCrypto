#pragma once
#include "../aes.h"

class Aes_ecb(AesCore) {
    public:
        uint8_t* Encryption(uint8_t plain, uint32_t size);
        uint8_t* Decryption(uint8_t cipher, uint32_t size);
}