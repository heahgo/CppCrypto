#include "aes/aes_core.h"

uint8_t AesCore::Mult8(uint8_t x, uint8_t y) {
    uint8_t result = 0;
    while (y) {
        if (y & 0x01) result ^= x;
        y >>= 1;
        if (x & 0x80) {
            x <<= 1;
            x^= 0x1b;
        } else {
            x <<= 1;
        }
    }
    return result & 0xff;
}

AesCore::AesCore(Bytes& key) {
    uint8_t round = 0;
    uint32_t key_byte_size = key.size();
    if (key_byte_size == 16) {
        round = 10;
    } else if (key_byte_size == 24) {
        round = 12;
    } else if (key_byte_size == 32) {
        round = 14;
    } else {
        throw std::length_error("Key Length is only used 128, 192, 256 bit!!");
    }
    round_ = round;
    ex_key_ = KeyExpantion(key, round);
}

AesCore::~AesCore() {
    delete[] ex_key_;
}

uint8_t* AesCore::KeyExpantion(Bytes& key, uint8_t round) {
    uint32_t key_byte_size = key.size();
    uint8_t rcon[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
    uint8_t* ex_key = new uint8_t[(round+1)*16];
    uint8_t nk =  key_byte_size >> 2;
    #define RotWord(dword) (dword>>8)&0xffffffff | (dword<<24)&0xffffffff
    #define XorWord(dword1, dword2) dword1 ^ dword2
    #define SubWord(dword) sbox[dword>>24]<<24 | sbox[(dword<<8)>>24]<<16 | sbox[(dword<<16)>>24]<<8 | sbox[(dword<<24)>>24]
    memcpy(ex_key, key.data(), nk*4);
    for (uint8_t i = nk; i < (round+1)*4; i++) {
        uint32_t tmp, tmp2;
        memcpy(&tmp, ex_key+(i-1)*4, 4);
        memcpy(&tmp2, ex_key+(i-nk)*4, 4);
        if (i % nk == 0) {
            tmp = RotWord(tmp);
            tmp = SubWord(tmp);
            tmp = XorWord(tmp, tmp2);
            tmp = XorWord(tmp, (uint32_t)rcon[i/nk-1]); 
            memcpy(ex_key+i*4, &tmp, 4);
        } else if (nk > 6 && i % nk == 4) {
            tmp = SubWord(tmp);
            tmp = XorWord(tmp, tmp2);
            memcpy(ex_key+i*4, &tmp, 4);
        } else {
            tmp = XorWord(tmp, tmp2);
            memcpy(ex_key+i*4, &tmp, 4);
        }
    }
    return ex_key;
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
        // block[i*4+0] = Mult8(tmp0,0x02)^Mult8(tmp1,0x03)^Mult8(tmp2,0x01)^Mult8(tmp3,0x01);
        // block[i*4+1] = Mult8(tmp0,0x01)^Mult8(tmp1,0x02)^Mult8(tmp2,0x03)^Mult8(tmp3,0x01);
        // block[i*4+2] = Mult8(tmp0,0x01)^Mult8(tmp1,0x01)^Mult8(tmp2,0x02)^Mult8(tmp3,0x03);
        // block[i*4+3] = Mult8(tmp0,0x03)^Mult8(tmp1,0x01)^Mult8(tmp2,0x01)^Mult8(tmp3,0x02);

        // 0x01 : gmul[0], 0x02 : gmul[1], 0x03 : gmul[2]
        block[i*4+0] = gmul[1][tmp0]^gmul[2][tmp1]^gmul[0][tmp2]^gmul[0][tmp3];
        block[i*4+1] = gmul[0][tmp0]^gmul[1][tmp1]^gmul[2][tmp2]^gmul[0][tmp3];
        block[i*4+2] = gmul[0][tmp0]^gmul[0][tmp1]^gmul[1][tmp2]^gmul[2][tmp3];
        block[i*4+3] = gmul[2][tmp0]^gmul[0][tmp1]^gmul[0][tmp2]^gmul[1][tmp3];
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
        // block[i*4+0] = Mult8(tmp0,0x0E)^Mult8(tmp1,0x0B)^Mult8(tmp2,0x0D)^Mult8(tmp3,0x09);
        // block[i*4+1] = Mult8(tmp0,0x09)^Mult8(tmp1,0x0E)^Mult8(tmp2,0x0B)^Mult8(tmp3,0x0D);
        // block[i*4+2] = Mult8(tmp0,0x0D)^Mult8(tmp1,0x09)^Mult8(tmp2,0x0E)^Mult8(tmp3,0x0B);
        // block[i*4+3] = Mult8(tmp0,0x0B)^Mult8(tmp1,0x0D)^Mult8(tmp2,0x09)^Mult8(tmp3,0x0E);

        // 0x09 : inv_gmul[0], 0x0B : inv_gmul[1], 0x0D : inv_gmul[2], 0x0E : inv_gmul[3]
        block[i*4+0] = inv_gmul[3][tmp0]^inv_gmul[1][tmp1]^inv_gmul[2][tmp2]^inv_gmul[0][tmp3];
        block[i*4+1] = inv_gmul[0][tmp0]^inv_gmul[3][tmp1]^inv_gmul[1][tmp2]^inv_gmul[2][tmp3];
        block[i*4+2] = inv_gmul[2][tmp0]^inv_gmul[0][tmp1]^inv_gmul[3][tmp2]^inv_gmul[1][tmp3];
        block[i*4+3] = inv_gmul[1][tmp0]^inv_gmul[2][tmp1]^inv_gmul[0][tmp2]^inv_gmul[3][tmp3];
    }
}

void AesCore::SubBytes(uint8_t block[16]) {
    for (uint8_t i = 0; i < 16; i++) {
        block[i] = sbox[block[i]];
    }
}

void AesCore::InvSubBytes(uint8_t block[16]) {
    for (uint8_t i = 0; i < 16; i++) {
        block[i] = inv_sbox[block[i]];
    }
}

void AesCore::EncBlock(uint8_t block[16]) {
    uint8_t round_key[16];
    AddRoundKey(block, ex_key_); 
    for (uint8_t i = 1; i < round_; i++) {
        memcpy(round_key, ex_key_+i*16, 16);
        SubBytes(block);
        ShiftRows(block);
        MixColumns(block);
        AddRoundKey(block, round_key);
    }
    memcpy(round_key, ex_key_+round_*16, 16);
    SubBytes(block);
    ShiftRows(block);
    AddRoundKey(block, round_key);
}

void AesCore::DecBlock(uint8_t block[16]) {
    uint8_t round_key[16];
    memcpy(round_key, ex_key_+round_*16, 16);
    AddRoundKey(block, round_key); 
    for (uint8_t i = round_-1; 0 < i; i--) {
        memcpy(round_key, ex_key_+i*16, 16);
        InvShiftRows(block);
        InvSubBytes(block);
        AddRoundKey(block, round_key);
        InvMixColumns(block);
    }
    InvShiftRows(block);                         
    InvSubBytes(block);
    AddRoundKey(block, ex_key_);
}
