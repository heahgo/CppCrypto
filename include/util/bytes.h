#pragma once
#include <cstdint>
#include <cstring>

class Bytes {
    private:
        uint32_t size_;
        uint8_t* bytes_;
    public:
        const uint8_t* data() {
            const uint8_t* const bytes = bytes_;
            return bytes;
        }

        const uint32_t size() {
            const uint32_t s = size_;
            return s;
        }

        Bytes() : bytes_(NULL), size_(0) {}

        Bytes(uint8_t byte, uint32_t length) {
            uint8_t* bytes = new uint8_t[length];
            memset(bytes, byte, length);
            bytes_ = bytes;
            size_ = length;
        }

        Bytes(uint8_t* bytes, uint32_t size) {
            bytes_ = new uint8_t[size];
            size_ = size;
            memcpy(bytes_, bytes, size);
        }

        virtual ~Bytes() {
            delete[] bytes_;
        }

        Bytes operator+(Bytes& bytes) {
            uint8_t* result_bytes = new uint8_t[size_ + bytes.size_];
            memcpy(result_bytes, bytes_, size_);
            memcpy(result_bytes + size_, bytes.bytes_, bytes.size_);
            return Bytes(result_bytes, size_ + bytes.size_);
        }

        Bytes& operator=(Bytes& bytes) {
            delete[] bytes_;
            bytes_ = new uint8_t[bytes.size_];
            size_ = bytes.size_;
            memcpy(bytes_, bytes.bytes_, size_);
            return *this;
        }
};