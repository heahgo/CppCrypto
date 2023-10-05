#pragma once

class AesCore {
    private:
        int* ex_key_;
        int* KeyExpantion(int* key, int size);
        int* AddRoundKey(int block[16]);
        int* ShiftRows(int block[16]);
        int* InvShirfRows(int block[16]);
        int* MixColumns(int block[16]);
        int* InvMixColumns(int block[16]);
        int* SubBytes(int block[16]);
        int* InvSubBytes(int block[16]);
        int* EncBlock(int block[16]);
        int* DecBlock(int block[16]);

    public:
        AesCore(int* key, int size) {
            ex_key_ = KeyExpantion(key, size);
        }
        ~AesCore() {
            delete[] ex_key_;
        }
};


