#include "./aes_core.h"

class AesTable : public AesCore {
    private:
        uint8_t t_boxes[9][16][256];
        uint32_t ty_tables[4][256];
        uint32_t t_boxes_ty_tables[4][9][16][256];
        uint8_t xor_tables[16][16];
    public:
        void EncBlock(uint8_t block[16]);
        AesTable(Bytes& key);
        ~AesTable();
};