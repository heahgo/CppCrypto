#include "aes/aes.h"
#include "util/padding.h"
#include <fstream>
#include <string>
#include <iostream>

using std::ifstream, std::string, std::cout, std::endl;

void PrintHex(const uint8_t* const bytes, uint32_t size) {  
    for (uint32_t i = 0; i < size; i++) {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}

bool Compare(Bytes &a, Bytes &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (uint32_t i = 0; i < a.size(); i++) {
        if (a.data()[i] != b.data()[i]) {
            return false;
        }
    }
    return true;
}

void Test(ifstream &test) {
    Bytes k, p,c ;
    string key, plaintext, ciphertext;
    for (uint32_t i = 0; i < 10000; i++) {
        getline(test, key);
        getline(test, plaintext);
        getline(test, ciphertext);
        k = Bytes(key);
        p = Bytes(plaintext);
        c = Bytes(ciphertext);
        AES aes = AES(k, ECB_MODE);
        p = Pad(p, 16);
        p = aes.Encrypt(p);
        if (!Compare(p,  c)) {
            printf("AES-ECB-%u Test Failed\n", k.size()*8);
            return;
        }
    }
    printf("AES-ECB-%u Test Passed\n", k.size()*8);
}

int main() {
    
    ifstream test_128("../../app/aes_test/ecb_test/test-128.txt");
    ifstream test_192("../../app/aes_test/ecb_test/test-192.txt");
    ifstream test_256("../../app/aes_test/ecb_test/test-256.txt");

    Test(test_128);
    Test(test_192);
    Test(test_256);

    test_128.close();
    test_192.close();
    test_256.close();

    // uint8_t k[16] = {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79, 0x20, 0x4B, 0x75, 0x6E, 0x67, 0x20, 0x46, 0x75};
    // uint8_t plain[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    // uint8_t a[] = {0x12, 0x34, 0x56, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    // Bytes key(k, 16);
    // Bytes p(plain, 16);
    // Aes_ecb crypto = Aes_ecb(key);
    // PrintHex(p.data(), p.size());
    // p = Pad(p, 16);
    // p = crypto.Encrypt(p);
    // PrintHex(p.data(), p.size());
    // p = crypto.Decrypt(p);
    // p = Unpad(p, 16);
    // PrintHex(p.data(), p.size());
    // AES aes = AES(key, ECB_MODE);
    // p = Pad(p, 16);
    // p = aes.Encrypt(p);
    // PrintHex(p.data(), p.size());
    // p = aes.Decrypt(p);
    // p = Unpad(p, 16);
    // PrintHex(p.data(), p.size());
}  
