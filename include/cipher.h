#pragma once
#include "./util/bytes.h"

class Cipher {
    public:
        virtual Bytes Encrypt(Bytes& plain) {return Bytes();};
        virtual Bytes Decrypt(Bytes& cipher) {return Bytes();};
};
