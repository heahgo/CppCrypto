#include "./aes_core.h"

class AesTable : public AesCore {
    private:
        uint8_t ** T_box;
        uint8_t ** Ty_box;
    public:
        AesTable(Bytes& key);
        ~AesTable();
};