#include "../../include/aes/aes.h"

AES::AES(Bytes& key, uint8_t mode, Bytes iv) {
    if (mode == ECB_MODE) {
        cipher_ = new Aes_ecb(key);
    }
}

Bytes AES::Encrypt(Bytes& plain) {
    return cipher_->Encrypt(plain);
}

Bytes AES::Decrypt(Bytes& cipher) {
    return cipher_->Decrypt(cipher);
}
