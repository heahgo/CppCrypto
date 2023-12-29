#include "aes/table.h"
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
    getline(test, key);
    k = Bytes(key);
    AES_T aes = AES_T(k, ECB_MODE);
    for (uint32_t i = 0; i < 10000; i++) {
        getline(test, plaintext);
        getline(test, ciphertext);
        p = Bytes(plaintext);
        c = Bytes(ciphertext);
        p = Pad(p, 16);
        p = aes.Encrypt(p);
        if (!Compare(p,  c)) {
            printf("AES-TABLE-ECB-%u Test Failed\n", k.size()*8);
            return;
        }
    }
    printf("AES-TABLE-ECB-%u Test Passed\n", k.size()*8);
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
}  