#include "aes/table.h"

AES_T::AES_T(Bytes& key, uint8_t mode, Bytes iv) {
    if (mode == ECB_MODE) {
        cipher_ = new Table_ecb(key);
    }
}

Bytes AES_T::Encrypt(Bytes& plain) {
    return cipher_->Encrypt(plain);
}

Bytes AES_T::Decrypt(Bytes& cipher) {
    return cipher_->Decrypt(cipher);
}
