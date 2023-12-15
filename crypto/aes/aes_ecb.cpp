#include "aes/aes_ecb.h"
#include <cstdint>

Bytes Aes_ecb::Encrypt(Bytes& plain) {
    uint8_t size = plain.size();
    if (size % 16 != 0)
        throw std::out_of_range("Encrypt Error : Incorrect plaintext length");
    uint8_t* cipher = new uint8_t[size];
    const uint8_t* p = plain.data();
    for (uint32_t i = 0; i < size; i+=16) {
        memcpy(cipher+i, p+i, 16);
        aes_core_.EncBlock(cipher+i);
    }
    return Bytes(cipher, size);
}

Bytes Aes_ecb::Decrypt(Bytes& cipher) {
    uint8_t size = cipher.size();
    if (size % 16 != 0)
        throw std::out_of_range("Decrypt Error : Incorrect ciphertext lengrh");
    uint8_t* plain = new uint8_t[size];
    const uint8_t* c = cipher.data();
    for (uint32_t i = 0; i < size; i+=16) {
        memcpy(plain+i, c+i, 16);
        aes_core_.DecBlock(plain+i);
    }
    return Bytes(plain, size);
}