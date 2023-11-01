#pragma once
#include "./aes.h"

class Aes_ecb : public Cipher {
    public:
        AesCore aes_core_;
        void Encrypt(uint8_t* plain, uint8_t* cipher, uint32_t size);
        void Decrypt(uint8_t* cipher, uint8_t* plain, uint32_t size);
        Aes_ecb(uint8_t* key, uint8_t key_byte_size) : aes_core_(AesCore(key, key_byte_size)) {}
        virtual ~Aes_ecb() {}
};