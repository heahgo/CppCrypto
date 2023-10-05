#pragma once

class AesCore {
    private:
        int* ex_key_;
        int* KeyExpantion(int* key, int size);
        void AddRoundKey(int block[16], int key[16]);
        void ShiftRows(int block[16]);
        void InvShirfRows(int block[16]);
        void MixColumns(int block[16]);
        void InvMixColumns(int block[16]);
        void SubBytes(int block[16]);
        void InvSubBytes(int block[16]);
        void EncBlock(int block[16]);
        void DecBlock(int block[16]);

    public:
        AesCore(int* key, int size) {
            ex_key_ = KeyExpantion(key, size);
        }
        ~AesCore() {
            delete[] ex_key_;
        }
};


