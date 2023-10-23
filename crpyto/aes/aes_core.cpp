#include "../../include/aes/aes.h"

uint8_t Mult8(uint8_t x, uint8_t y) {
    uint8_t result = 0;
    while (y) {
        if (y & 0x01) result ^= x;
        y >>= 1;
        x <<= 1;
        if (x & 0x100) x^= 0x1b;
    }
    return result;
}

AesCore::AesCore(uint8_t* key, uint8_t key_byte_size) {
    uint8_t cols;
    if (key_byte_size == 16) {
        cols = 10;
    } else if (key_byte_size == 24) {
        cols = 12;
    } else if (key_byte_size == 32) {
        cols = 14;
    } else {
        throw std::length_error("Key Length is only used 128, 192, 256 bit!!");
    }

    ex_key_ = KeyExpantion(key, key_byte_size, cols);
}

AesCore::~AesCore() {
    delete[] ex_key_;
}

uint8_t* AesCore::KeyExpantion(uint8_t* key, uint8_t key_byte_size, uint8_t cols) {
    uint8_t rcon[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

    // int* ex_key = new int[]
    // return ex_key
}

void AesCore::AddRoundKey(uint8_t block[16], uint8_t key[16]) {
    for (int i = 0; i < 16; i++) {
        block[i] ^= key[i];
    }
    return;
}

void AesCore::ShiftRows(uint8_t block[16]) {
    
    //  +----+----+----+----+             +----+----+----+----+
    //  | 00 | 04 | 08 | 12 |             | 00 | 04 | 08 | 12 |
    //  +----+----+----+----+             +----+----+----+----+
    //  | 01 | 05 | 09 | 13 |  ShiftRows  | 05 | 09 | 13 | 01 |
    //  +----+----+----+----+      =>     +----+----+----+----+
    //  | 02 | 06 | 10 | 14 |             | 10 | 14 | 02 | 06 |
    //  +----+----+----+----+             +----+----+----+----+
    //  | 03 | 07 | 11 | 15 |             | 15 | 03 | 07 | 11 |
    //  +----+----+----+----+             +----+----+----+----+

    uint8_t tmp;
    tmp = block[1];
    block[1] = block[5];
    block[5] = block[9];
    block[9] = block[13];
    block[13] = tmp;

    tmp = block[6];
    block[6] = block[14];
    block[14] = tmp;
    tmp = block[10];
    block[10] = block[2];
    block[2] = tmp;

    tmp = block[3];
    block[3] = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7] = tmp;
}

void AesCore::InvShiftRows(uint8_t block[16]) {

    //  +----+----+----+----+                +----+----+----+----+
    //  | 00 | 04 | 08 | 12 |                | 00 | 04 | 08 | 12 |
    //  +----+----+----+----+                +----+----+----+----+
    //  | 01 | 05 | 09 | 13 |  InvShiftRows  | 13 | 01 | 05 | 09 |
    //  +----+----+----+----+       =>       +----+----+----+----+
    //  | 02 | 06 | 10 | 14 |                | 10 | 14 | 02 | 06 |
    //  +----+----+----+----+                +----+----+----+----+
    //  | 03 | 07 | 11 | 15 |                | 07 | 11 | 15 | 03 |
    //  +----+----+----+----+                +----+----+----+----+

    uint8_t tmp;
    tmp = block[9];
    block[9] = block[5];
    block[5] = block[1];
    block[1] = block[13];
    block[13] = tmp;

    tmp = block[2];
    block[2] = block[10];
    block[10] = tmp;
    tmp = block[6];
    block[6] = block[14];
    block[14] = tmp;

    tmp = block[3];
    block[3] = block[7];
    block[7] = block[11];
    block[11] = block[15];
    block[15] = tmp;
}

void AesCore::MixColumns(uint8_t block[16]) {

    //         Matrix Multiplication in a Glois Filed 
    //
    //  +----+----+----+----+           +----+----+----+----+
    //  | 02 | 03 | 01 | 01 |           | 00 | 04 | 08 | 12 |
    //  +----+----+----+----+           +----+----+----+----+
    //  | 01 | 02 | 03 | 01 |           | 01 | 05 | 09 | 13 |
    //  +----+----+----+----+     *     +----+----+----+----+
    //  | 01 | 01 | 02 | 03 |           | 02 | 06 | 10 | 14 |
    //  +----+----+----+----+           +----+----+----+----+
    //  | 03 | 01 | 01 | 02 |           | 03 | 07 | 11 | 15 |
    //  +----+----+----+----+           +----+----+----+----+

    for (uint8_t i = 0; i < 4; i++) {
        uint8_t tmp0 = block[i*4];
        uint8_t tmp1 = block[i*4+1];
        uint8_t tmp2 = block[i*4+2];
        uint8_t tmp3 = block[i*4+3];

        block[i*4+0] = Mult8(tmp0,0x02)^Mult8(tmp1,0x03)^Mult8(tmp2,0x01)^Mult8(tmp3,0x01);
        block[i*4+1] = Mult8(tmp0,0x01)^Mult8(tmp1,0x02)^Mult8(tmp2,0x03)^Mult8(tmp3,0x01);
        block[i*4+2] = Mult8(tmp0,0x01)^Mult8(tmp1,0x01)^Mult8(tmp2,0x02)^Mult8(tmp3,0x03);
        block[i*4+3] = Mult8(tmp0,0x03)^Mult8(tmp1,0x01)^Mult8(tmp2,0x01)^Mult8(tmp3,0x02);
    }
}

void AesCore::InvMixColumns(uint8_t block[16]) {

    //         Matrix Multiplication in a Glois Filed 
    //
    //  +----+----+----+----+           +----+----+----+----+
    //  | 0E | 0B | 0D | 09 |           | 00 | 04 | 08 | 12 |
    //  +----+----+----+----+           +----+----+----+----+
    //  | 09 | 0E | 0B | 0D |           | 01 | 05 | 09 | 13 |
    //  +----+----+----+----+     *     +----+----+----+----+
    //  | 0D | 09 | 0E | 0B |           | 02 | 06 | 10 | 14 |
    //  +----+----+----+----+           +----+----+----+----+
    //  | 0B | 0D | 09 | 0E |           | 03 | 07 | 11 | 15 |
    //  +----+----+----+----+           +----+----+----+----+

    for (uint8_t i = 0; i < 4; i++) {
        uint8_t tmp0 = block[i*4];
        uint8_t tmp1 = block[i*4+1];
        uint8_t tmp2 = block[i*4+2];
        uint8_t tmp3 = block[i*4+3];

        block[i*4+0] = Mult8(tmp0,0x0E)^Mult8(tmp1,0x0B)^Mult8(tmp2,0x0D)^Mult8(tmp3,0x09);
        block[i*4+1] = Mult8(tmp0,0x09)^Mult8(tmp1,0x0E)^Mult8(tmp2,0x0B)^Mult8(tmp3,0x0D);
        block[i*4+2] = Mult8(tmp0,0x0D)^Mult8(tmp1,0x09)^Mult8(tmp2,0x0E)^Mult8(tmp3,0x0B);
        block[i*4+3] = Mult8(tmp0,0x0B)^Mult8(tmp1,0x0D)^Mult8(tmp2,0x09)^Mult8(tmp3,0x0E);
    }
}