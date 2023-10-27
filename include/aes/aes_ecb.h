#pragma once
#include "../aes/aes.h"

class Aes_ecb : public AesCore {
    public:
        uint8_t* Encrypt(uint8_t plain, uint32_t size);
        uint8_t* Decrypt(uint8_t cipher, uint32_t size);
}