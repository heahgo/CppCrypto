#include "aes/aes.h"
#include "aes/table.h"
#include "util/padding.h"
#include <fstream>
#include <random>
#include <ctime>

Bytes KeyGen(uint32_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, ~0);

    uint32_t* key = new uint32_t[size/32];
    for (uint32_t i = 0; i < size/32; i++) {
        key[i] = dis(gen);
    }
    return Bytes((uint8_t*)key, size/8);
}

int main() {
    time_t start, end;
    std::string text;
    Bytes t;
    Bytes key = KeyGen(128);
    AES aes(key, ECB_MODE);
    AES_T aes_t(key, ECB_MODE);

    std::ifstream texts;

    // AES Encrypt test
    texts = std::ifstream("../../app/aes_test/speed/plaintext.txt");
    start = clock();
    for (uint32_t i = 0; i < 1000000; i++) {
        getline(texts, text);
        t = Bytes(text);
        aes.Encrypt(t);
    }
    end = clock();
    printf("AES-ECB-128 Encryption 1000000 plaintext(64 Bytes): %fs\n", (double)(end-start) / CLOCKS_PER_SEC);
    // AES_T Encrypt test
    texts = std::ifstream("../../app/aes_test/speed/plaintext.txt");
    start = clock();
    for (uint32_t i = 0; i < 1000000; i++) {
        getline(texts, text);
        t = Bytes(text);
        aes_t.Encrypt(t);
    }
    end = clock();
    printf("AES_T-ECB-128 Encryption 1000000 plaintext(64 Bytes): %fs\n", (double)(end-start) / CLOCKS_PER_SEC);

    // AES Decrypt test
    texts = std::ifstream("../../app/aes_test/speed/plaintext.txt");
    start = clock();
    for (uint32_t i = 0; i < 1000000; i++) {
        getline(texts, text);
        t = Bytes(text);
        aes.Decrypt(t);
    }
    end = clock();
    printf("AES-ECB-128 Decryption 1000000 plaintext(64 Bytes): %fs\n", (double)(end-start) / CLOCKS_PER_SEC);
    // AES_T Decrypt test
    texts = std::ifstream("../../app/aes_test/speed/plaintext.txt");
    start = clock();
    for (uint32_t i = 0; i < 1000000; i++) {
        getline(texts, text);
        t = Bytes(text);
        aes_t.Decrypt(t);
    }
    end = clock();
    printf("AES_T-ECB-128 Decryption 1000000 plaintext(64 Bytes): %fs\n", (double)(end-start) / CLOCKS_PER_SEC);
}
