#pragma once
#include "../aes.h"

class Aes_ecb(AesCore) {
    public:
        uint8_t* Encryption(uint8_t block);
        uint8_t* Decryption(uint8_t block);
}