#include "./aes_core.h"

class AesTable : public AesCore {
    private:
        uint8_t*** t_boxes;
        uint32_t ** ty_tables;
        uint8_t **xor_tables;
    public:
        void PrintTyTables();
        AesTable(Bytes& key);
        ~AesTable();
};