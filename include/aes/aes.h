#pragma once
#include "./aes_ecb.h"

#define ECB_MODE 0

class AES {
    private:
        Cipher* cipher_;

    public:
        Bytes Encrypt(Bytes& plain);
        Bytes Decrypt(Bytes& cipher);
        AES(Bytes& key, uint8_t mode, Bytes iv = Bytes());
        ~AES() {};
};