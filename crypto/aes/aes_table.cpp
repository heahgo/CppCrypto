#include "../../include/aes/aes_table.h"

AesTable::AesTable(Bytes& key) : AesCore(key) {
     // Memory allocation for T-boxes
    t_boxes = new uint8_t**[round_];
    for (uint8_t r = 0; r < round_; r++) {
        t_boxes[r] = new uint8_t*[block_size_];
        for (uint8_t i = 0; i < block_size_; i++) {
            t_boxes[r][i] = new uint8_t[256];
        } 
    }
    // T-boxes generation
    for (uint8_t r = 0; r < round_-1; r++) {   
        for (uint8_t i = 0; i < block_size_; i++) {
            for (uint32_t j = 0; j < 256; j++) {
                t_boxes[r][i][j] = sbox[j ^ ex_key_[r*block_size_+i]];
            }
        }
    } 
    for (uint8_t i = 0; i < block_size_; i++) {
        for (uint32_t j = 0; j < 256; j++) {
            t_boxes[round_-1][i][j] = sbox[j ^ ex_key_[(round_-1)*block_size_+i]] ^ ex_key_[round_*block_size_+i];
        }
    }

    // Memory allocation for Ty-tables
    ty_tables = new uint32_t*[4];
    for (uint8_t i = 0; i < 4; i++) {
        ty_tables[i] = new uint32_t[256];
    }
    // Ty-tables generation
    for (uint32_t i = 0; i < 256; i++) {
        ty_tables[0][i] = Mult8(i, 0x02)<<24 | i<<16 | i<<8 | Mult8(i, 0x03);
        ty_tables[1][i] = Mult8(i, 0x03)<<24 | Mult8(i, 0x02)<<16 | i<<8 | i;
        ty_tables[2][i] = i<<24 | Mult8(i, 0x03)<<16 | Mult8(i, 0x02)<<8 | i;
        ty_tables[3][i] = i<<24 | i<<16 | Mult8(i, 0x03)<<8 | Mult8(i, 0x02);
    }
    // Memory allocation for XOR-tables
    xor_tables = new uint8_t*[16];
    for (uint8_t i = 0; i < 16; i++) {
        xor_tables[i] = new uint8_t[16];
    }
    // XOR-tables generation
    for (uint8_t i = 0; i < 16; i++) {
        for (uint8_t j = 0; j < 16; j++) {
            xor_tables[i][j] = i ^ j;
        }
    }
} 

AesTable::~AesTable() {
    // Memory deallocation for T-boxes
    for(uint8_t r = 0; r < round_; r++) {
        for (uint8_t i = 0; i < block_size_; i++) {
            delete[] t_boxes[r][i];
        }
        delete[] t_boxes[r]; 
    }
    // Memory deallocation for Ty-tables
    for (uint8_t i = 0; i < 4; i++) {
        delete[] ty_tables[i];
    }
    // Memory deallocation for XOR-tables
    for (uint8_t i = 0; i < 16; i++) {
        delete[] xor_tables[i];
    }
}
