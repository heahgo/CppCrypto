#include "aes/aes_table.h"

AesTable::AesTable(Bytes& key) : AesCore(key) {
    uint8_t tmp_key[16];
    // Memory allocation for t_boxes
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
                memcpy(tmp_key, ex_key_+r*block_size_, block_size_);
                ShiftRows(tmp_key);
                t_boxes[r][i][j] = sbox[j ^ tmp_key[i]];
            }
        }
    } 
    memcpy(tmp_key, ex_key_+(round_-1)*block_size_, block_size_);
    ShiftRows(tmp_key);
    for (uint8_t i = 0; i < block_size_; i++) {
        for (uint32_t j = 0; j < 256; j++) {
            t_boxes[round_-1][i][j] = sbox[j ^ tmp_key[i]] ^ ex_key_[round_*block_size_+i];
        }
    }
    // Memory allocation for inv_t_boxes
    inv_t_boxes = new uint8_t**[round_];
    for (uint8_t r = 0; r < round_; r++) {
        inv_t_boxes[r] = new uint8_t*[block_size_];
        for (uint8_t i = 0; i < block_size_; i++) {
            inv_t_boxes[r][i] = new uint8_t[256];
        }
    }
    // Inverse T-boxes generation
    memcpy(tmp_key, ex_key_+round_*block_size_, block_size_);
    InvShiftRows(tmp_key);
    for (uint8_t i = 0; i < block_size_; i++) {
        for (uint32_t j = 0; j < 256; j++) {
            inv_t_boxes[0][i][j] = inv_sbox[j ^ tmp_key[i]] ^ ex_key_[(round_-1)*block_size_+i];
        }
    }   
    for (uint8_t r = 1; r < round_; r++) {   
        for (uint8_t i = 0; i < block_size_; i++) {
            for (uint32_t j = 0; j < 256; j++) {
                inv_t_boxes[r][i][j] = inv_sbox[j] ^ ex_key_[(round_-r-1)*block_size_+i]; 
            }
        }
    }
    // Memory allocation for ty_tables
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
    // Memory allocation for inv_ty_tables
    inv_ty_tables = new uint32_t*[4];
    for (uint8_t i = 0; i < 4; i++) {
        inv_ty_tables[i] = new uint32_t[256];
    }
    // Inverse Ty-tables generation
    for (uint32_t i = 0; i < 256; i++) {
        inv_ty_tables[0][i] = Mult8(i, 0x0E)<<24 | Mult8(i, 0x09)<<16 | Mult8(i, 0x0D)<<8 | Mult8(i, 0x0B);
        inv_ty_tables[1][i] = Mult8(i, 0x0B)<<24 | Mult8(i, 0x0E)<<16 | Mult8(i, 0x09)<<8 | Mult8(i, 0x0D);
        inv_ty_tables[2][i] = Mult8(i, 0x0D)<<24 | Mult8(i, 0x0B)<<16 | Mult8(i, 0x0E)<<8 | Mult8(i, 0x09);
        inv_ty_tables[3][i] = Mult8(i, 0x09)<<24 | Mult8(i, 0x0D)<<16 | Mult8(i, 0x0B)<<8 | Mult8(i, 0x0E);
    }
    // Memory allocation for t_boxes_ty_tables
    t_boxes_ty_tables = new uint32_t***[4];
    for (uint8_t i = 0; i < 4; i++) {
        t_boxes_ty_tables[i] = new uint32_t**[round_-1];
        for (uint8_t r = 0; r < round_-1; r++) {
            t_boxes_ty_tables[i][r] = new uint32_t*[block_size_];
            for (uint8_t j = 0; j < block_size_; j++) {
                t_boxes_ty_tables[i][r][j] = new uint32_t[256];
            }
        }
    }
    // t_boxes_ty_tables generation
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t r = 0; r < round_-1; r++) {   
            for (uint8_t j = 0; j < block_size_; j++) {
                for (uint32_t k = 0; k < 256; k++) {
                    t_boxes_ty_tables[i][r][j][k] = ty_tables[i][t_boxes[r][j][k]];
                }
            }
        }
    }
    // Memory allocation for inv_t_boxes_ty_tables
    inv_t_boxes_ty_tables = new uint32_t***[4];
    for (uint8_t i = 0; i < 4; i++) {
        inv_t_boxes_ty_tables[i] = new uint32_t**[round_-1];
        for (uint8_t r = 0; r < round_-1; r++) {
            inv_t_boxes_ty_tables[i][r] = new uint32_t*[block_size_];
            for (uint8_t j = 0; j < block_size_; j++) {
                inv_t_boxes_ty_tables[i][r][j] = new uint32_t[256];
            }
        }
    }
    // inv_t_boxes_ty_tables generation
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t r = 0; r < round_-1; r++) {   
            for (uint8_t j = 0; j < block_size_; j++) {
                for (uint32_t k = 0; k < 256; k++) {
                    inv_t_boxes_ty_tables[i][r][j][k] = inv_ty_tables[i][inv_t_boxes[r][j][k]];
                }
            }
        }
    }
    // Memory allocation for xor_tables
    // xor_tables = new uint8_t*[16];
    // for (uint8_t i = 0; i < 16; i++) {
    //     xor_tables[i] = new uint8_t[16];
    // }
    // // XOR-tables generation
    // for (uint8_t i = 0; i < 16; i++) {
    //     for (uint8_t j = 0; j < 16; j++) {
    //         xor_tables[i][j] = i ^ j;
    //     }
    // }
} 
AesTable::~AesTable() {
    // Memory deallocation for t_boxes
    for (uint8_t r = 0; r < round_; r++) {
        for (uint8_t i = 0; i < block_size_; i++) {
            delete[] t_boxes[r][i];
        }
        delete[] t_boxes[r];
    }
    delete[] t_boxes;
    // Memory deallocation for inv_t_boxes
    for (uint8_t r = 0; r < round_; r++) {
        for (uint8_t i = 0; i < block_size_; i++) {
            delete[] inv_t_boxes[r][i];
        }
        delete[] inv_t_boxes[r];
    }
    // Memory deallocation for ty_tables
    for (uint8_t i = 0; i < 4; i++) {
        delete[] ty_tables[i];
    }
    delete[] ty_tables;
    // Memory deallocation for inv_ty_tables
    for (uint8_t i = 0; i < 4; i++) {
        delete[] inv_ty_tables[i];
    }
    delete[] inv_ty_tables;
    // Memory deallocation for t_boxes_ty_tables
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t r = 0; r < round_; r++) {
            for (uint8_t j = 0; j < block_size_; j++) {
                delete[] t_boxes_ty_tables[i][r][j];
            }
            delete[] t_boxes_ty_tables[i][r];
        }
        delete[] t_boxes_ty_tables[i];
    }
    delete[] t_boxes_ty_tables;
    // Memory deallocation for inv_t_boxes_ty_tables
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t r = 0; r < round_; r++) {
            for (uint8_t j = 0; j < block_size_; j++) {
                delete[] inv_t_boxes_ty_tables[i][r][j];
            }
            delete[] inv_t_boxes_ty_tables[i][r];
        }
        delete[] inv_t_boxes_ty_tables[i];
    }
    delete[] inv_t_boxes_ty_tables;
    // Memory deallocation for xor_tables
    // for (uint8_t i = 0; i < 16; i++) {
    //     delete[] xor_tables[i];
    // }
    // delete[] xor_tables;
}

// void AesTable::EncBlock(uint8_t block[16]) {
//     uint8_t round_key[16];
//     for (uint8_t i = 0; i < round_-1; i++) {
//         ShiftRows(block);
//         memcpy(round_key, ex_key_+i*16, 16);
//         AddRoundKey(block, round_key);
//         SubBytes(block);
//         MixColumns(block);
//     }
//     ShiftRows(block);
//     memcpy(round_key, ex_key_+(round_-1)*16, 16);
//     AddRoundKey(block, round_key);
//     SubBytes(block);
//     memcpy(round_key, ex_key_+round_*16, 16);
//     AddRoundKey(block, round_key);
// }

void AesTable::EncBlock(uint8_t block[16]) {
    uint32_t mixcol;
    for (uint8_t r = 0; r < round_-1; r++) {
        ShiftRows(block);
        for (uint8_t j = 0; j < 4; j++) {
            //t_boxes_ty_tables
            mixcol = t_boxes_ty_tables[0][r][j*4+0][block[j*4+0]] ^ 
                    t_boxes_ty_tables[1][r][j*4+1][block[j*4+1]] ^
                    t_boxes_ty_tables[2][r][j*4+2][block[j*4+2]] ^
                    t_boxes_ty_tables[3][r][j*4+3][block[j*4+3]];
            block[j*4+3] = (mixcol>>0)&0x0ff;
            block[j*4+2] = (mixcol>>8)&0x0ff;
            block[j*4+1] = (mixcol>>16)&0x0ff;
            block[j*4+0] = (mixcol>>24)&0x0ff;
        }
    }
    ShiftRows(block);
    // t_boxes
    for (uint8_t i = 0; i < block_size_; i++) {
        block[i] = t_boxes[round_-1][i][block[i]];
    }
}

// void AesTable::DecBlock(uint8_t block[16]) {
//     uint8_t inv_shift_key[16];
//     InvShiftRows(block);
//     memcpy(inv_shift_key, ex_key_+round_*block_size_, block_size_);
//     InvShiftRows(inv_shift_key);
//     AddRoundKey(block, inv_shift_key);
//     InvSubBytes(block);
//     AddRoundKey(block, ex_key_+(round_-1)*block_size_);
//     InvMixColumns(block);

//     for (uint8_t r = round_-2; 0 < r; r--) {
//         InvShiftRows(block);
//         InvSubBytes(block);
//         AddRoundKey(block, ex_key_+r*block_size_);
//         InvMixColumns(block);
//     }
//     InvShiftRows(block);
//     InvSubBytes(block);
//     AddRoundKey(block, ex_key_);
// }

void AesTable::DecBlock(uint8_t block[16]) {
    uint32_t mixcol;
    for (uint8_t r = 0; r < round_-1; r++) {
        InvShiftRows(block);
        for (uint8_t j = 0; j < 4; j++) {
            //inv_t_boxes_ty_tables
            mixcol = inv_t_boxes_ty_tables[0][r][j*4+0][block[j*4+0]] ^ 
                    inv_t_boxes_ty_tables[1][r][j*4+1][block[j*4+1]] ^
                    inv_t_boxes_ty_tables[2][r][j*4+2][block[j*4+2]] ^
                    inv_t_boxes_ty_tables[3][r][j*4+3][block[j*4+3]];
            block[j*4+3] = (mixcol>>0)&0x0ff;
            block[j*4+2] = (mixcol>>8)&0x0ff;
            block[j*4+1] = (mixcol>>16)&0x0ff;
            block[j*4+0] = (mixcol>>24)&0x0ff;
        }
    }
    InvShiftRows(block);
    // inv_t_boxes
    for (uint8_t i = 0; i < block_size_; i++) {
        block[i] = inv_t_boxes[round_-1][i][block[i]];
    }
}
