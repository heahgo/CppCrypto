#pragma once
#include "./aes_table.h"

class Table_ecb : public Cipher {
    public:
        AesTable aes_table_;
        Bytes Encrypt(Bytes& plain);
        Bytes Decrypt(Bytes& cipher);
        Table_ecb(Bytes& key) : aes_table_(AesTable(key)) {}
        virtual ~Table_ecb() {}
};