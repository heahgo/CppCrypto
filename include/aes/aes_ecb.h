#pragma once
#include "./aes_core.h"

class Aes_ecb : public Cipher {
    public:
        AesCore aes_core_;
        Bytes Encrypt(Bytes& plain);
        Bytes Decrypt(Bytes& cipher);
        Aes_ecb(Bytes key) : aes_core_(AesCore(key)) {}
        virtual ~Aes_ecb() {}
};