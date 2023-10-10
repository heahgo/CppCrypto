#pragma once
#include <cstdint>
#include <iostream>

class AesCore {
    private:
        uint8_t* ex_key_;
        uint8_t* KeyExpantion(uint8_t* key, uint8_t key_byte_size, uint8_t cols);
        void AddRoundKey(uint8_t block[16], uint8_t key[16]);
        void ShiftRows(uint8_t block[16]);
        void InvShiftRows(uint8_t block[16]);
        void MixColumns(uint8_t block[16]);
        void InvMixColumns(uint8_t block[16]);
        void SubBytes(uint8_t block[16]);
        void InvSubBytes(uint8_t block[16]);
        void EncBlock(uint8_t block[16]);
        void DecBlock(uint8_t block[16]);
    public:
        uint8_t Mult8(uint8_t x, uint8_t y);
        AesCore(uint8_t* key, uint8_t key_byte_size);
        ~AesCore();
};


