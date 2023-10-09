#include "../../include/aes/aes.h"

uint8_t mult8(uint8_t x, uint8_t y) {
    
}

uint8_t* AesCore::KeyExpantion(uint8_t* key, uint8_t key_byte_size) {
    if (key_byte_size == 16) {

    } else if (key_byte_size == 24) {

    } else if (key_byte_size == 32) {

    } else {
        throw std::length_error("Key Length is only used 128, 192, 256 bit!!");
    }
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
    // block[0] block[4] block[8] block[12]      block[0]  block[4]  block[8]  block[12]
    // block[1] block[5] block[9] block[13]  =>  block[5]  block[9]  block[13] block[1]
    // block[2] block[6] block[10] block[14]     block[10] block[14] block[2]  block[6]
    // block[3] block[7] block[11] block[15]     block[15] block[3]  block[7]  block[11]
}
void InvShiftRows(uint8_t block[16]) {
    // block[0] block[4] block[8] block[12]      block[0]  block[4]  block[8]  block[12]
    // block[1] block[5] block[9] block[13]  =>  block[13] block[1]  block[5]  block[9]
    // block[2] block[6] block[10] block[14]     block[10] block[14] block[2]  block[6]
    // block[3] block[7] block[11] block[15]     block[7]  block[11] block[15] block[3]
}
void MixColumns(int block[16]);
void InvMixColumns(int block[16]);
void SubBytes(int block[16]);
void InvSubBytes(int block[16]);
void EncBlock(int block[16]);
void DecBlock(int block[16]);