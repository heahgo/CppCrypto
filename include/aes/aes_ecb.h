#pragma once
#include "./aes.h"

class Aes_ecb : public Cipher {
    public:
        AesCore aes_core_;
        Bytes Encrypt(Bytes& plain);
        Bytes Decrypt(Bytes& cipher);
        Aes_ecb(uint8_t* key, uint8_t key_byte_size) : aes_core_(AesCore(key, key_byte_size)) {}
        virtual ~Aes_ecb() {}
};