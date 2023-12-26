#include "aes/aes_table.h"

AesTable::AesTable(Bytes& key) : AesCore(key) {
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
    // Ty-tables generation
    for (uint32_t i = 0; i < 256; i++) {
        ty_tables[0][i] = Mult8(i, 0x02)<<24 | i<<16 | i<<8 | Mult8(i, 0x03);
        ty_tables[1][i] = Mult8(i, 0x03)<<24 | Mult8(i, 0x02)<<16 | i<<8 | i;
        ty_tables[2][i] = i<<24 | Mult8(i, 0x03)<<16 | Mult8(i, 0x02)<<8 | i;
        ty_tables[3][i] = i<<24 | i<<16 | Mult8(i, 0x03)<<8 | Mult8(i, 0x02);
    }
    // composed T-boxes/Ty-tables generation
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t r = 0; r < round_-1; r++) {
            for (uint8_t j = 0; j < block_size_; j++) {
                for (uint32_t k = 0; k < 256; k++) {
                    t_boxes_ty_tables[i][r][j][k] = ty_tables[i][t_boxes[r][j][k]];
                }
            }
        }
    }
    // XOR-tables generation
    for (uint8_t i = 0; i < 16; i++) {
        for (uint8_t j = 0; j < 16; j++) {
            xor_tables[i][j] = i ^ j;
        }
    }
} 

void AesTable::EncBlock(uint8_t block[16]) {
    uint32_t a, b, c, d;
    for (uint8_t i = 0; i < round_-1; i++) {
        ShiftRows(block);
        for (uint8_t j = 0; j < 4; j++) {
            //t_boxes_ty_tables
            a = t_boxes_ty_tables[0][i][j*4+0][block[j*4+0]];
            b = t_boxes_ty_tables[1][i][j*4+1][block[j*4+1]];
            c = t_boxes_ty_tables[2][i][j*4+2][block[j*4+2]];
            d = t_boxes_ty_tables[3][i][j*4+3][block[j*4+3]];
            //xor_tables
            block[j*4+0] = (xor_tables[xor_tables[(a>>0)&0x0f][(b>>0)&0x0f]][xor_tables[(c>>0)&0x0f][(d>>0)&0x0f]]) |
                            (xor_tables[xor_tables[(a>>4)&0x0f][(b>>4)&0x0f]][xor_tables[(c>>4)&0x0f][(d>>4)&0x0f]]<<4);
            block[j*4+1] = (xor_tables[xor_tables[(a>>8)&0x0f][(b>>8)&0x0f]][xor_tables[(c>>8)&0x0f][(d>>8)&0x0f]]) |
                            (xor_tables[xor_tables[(a>>12)&0x0f][(b>>12)&0x0f]][xor_tables[(c>>12)&0x0f][(d>>12)&0x0f]]<<4);
            block[j*4+2] = (xor_tables[xor_tables[(a>>16)&0x0f][(b>>16)&0x0f]][xor_tables[(c>>16)&0x0f][(d>>16)&0x0f]]) |
                            (xor_tables[xor_tables[(a>>20)&0x0f][(b>>20)&0x0f]][xor_tables[(c>>20)&0x0f][(d>>20)&0x0f]]<<4);
            block[j*4+3] = (xor_tables[xor_tables[(a>>24)&0x0f][(b>>24)&0x0f]][xor_tables[(c>>24)&0x0f][(d>>24)&0x0f]]) |
                            (xor_tables[xor_tables[(a>>28)&0x0f][(b>>28)&0x0f]][xor_tables[(c>>28)&0x0f][(d>>28)&0x0f]]<<4);
        }
    }
    ShiftRows(block);
    //t_boxes
    for (uint8_t i = 0; i < block_size_; i++) {
        block[i] = t_boxes[round_-1][i][block[i]];
    }
}