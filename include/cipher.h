#pragma once
#include "./util/bytes.h"

class Cipher {
    virtual Bytes Encrypt(Bytes& plain) = 0;
    virtual Bytes Decrypt(Bytes& cipher) = 0;
};
