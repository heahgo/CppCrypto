#pragma once
#include "./aes_ecb.h"
using std::string;

class AES {
    private:
        string mode;

    public:
        Bytes Encrypt(Bytes plain);
        Bytes Decrypt(Bytes cipher);
        AES(Bytes key, string mode, Bytes iv = Bytes());
        virtual ~AES();
};