#pragma once
#include "./table_ecb.h"

#define ECB_MODE 0

class AES_T {
    private:
        Cipher* cipher_;

    public:
        Bytes Encrypt(Bytes& plain);
        Bytes Decrypt(Bytes& cipher);
        AES_T(Bytes& key, uint8_t mode, Bytes iv = Bytes());
        ~AES_T() {};
};