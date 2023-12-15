#include "aes/aes.h"
#include "util/padding.h"

void PrintHex(const uint8_t* const bytes, uint32_t size) {  
    for (uint32_t i = 0; i < size; i++) {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}

int main() {
    uint8_t k[16] = {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79, 0x20, 0x4B, 0x75, 0x6E, 0x67, 0x20, 0x46, 0x75};
    uint8_t plain[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t a[] = {0x12, 0x34, 0x56, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    Bytes key(k, 16);
    Bytes p(plain, 16);
    Aes_ecb crypto = Aes_ecb(key);
    PrintHex(p.data(), p.size());
    p = Pad(p, 16);
    p = crypto.Encrypt(p);
    PrintHex(p.data(), p.size());
    p = crypto.Decrypt(p);
    p = Unpad(p, 16);
    PrintHex(p.data(), p.size());
    AES aes = AES(key, ECB_MODE);
    p = Pad(p, 16);
    p = aes.Encrypt(p);
    PrintHex(p.data(), p.size());
    p = aes.Decrypt(p);
    p = Unpad(p, 16);
    PrintHex(p.data(), p.size());
}  
