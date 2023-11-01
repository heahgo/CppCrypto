#pragma once
#include "./aes.h"

class Aes_ecb : public Cipher {
    public:
        AesCore aes_core_;
        uint8_t* Encrypt(uint8_t* plain, uint8_t* cipher, uint32_t size);
        uint8_t* Decrypt(uint8_t* cipher, uint8_t* plain, uint32_t size);
        Aes_ecb();
        Aes_ecb(uint8_t* key, uint8_t key_byte_size) : aes_core_(AesCore(key, key_byte_size)) {};
        virtual ~Aes_ecb();
};