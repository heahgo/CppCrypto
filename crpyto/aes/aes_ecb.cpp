#include "../../include/aes/aes_ecb.h"
#include <cstdint>

void Aes_ecb::Encrypt(uint8_t* plain, uint8_t* cipher, uint32_t size) {
    if (size % 16 != 0)
        throw std::out_of_range("Incorrect plaintext");
    for (uint32_t i = 0; i < size; i+=16) {
        memcpy(cipher+i, plain+i, 16);
        aes_core_.EncBlock(cipher+i);
    }
}

void Aes_ecb::Decrypt(uint8_t* cipher, uint8_t* plain, uint32_t size) {
    if (size % 16 != 0)
        throw std::out_of_range("Incorrect ciphertext");
    for (uint32_t i = 0; i < size; i+=16) {
        memcpy(plain+i, cipher+i, 16);
        aes_core_.DecBlock(plain+i);
    }
}