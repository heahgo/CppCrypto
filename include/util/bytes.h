#pragma once
#include <cstdint>
#include <cstring>
#include <string>

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

        Bytes(std::string hex) {   // hex example : a1b2c3d4...
            size_ = hex.length() / 2;                  
            bytes_ = new uint8_t[size_];
            for (uint32_t i = 0; i < size_; i++) {
                bytes_[i] = stoul(hex.substr(i*2, 2), 0, 16);
            }
        }

        virtual ~Bytes() {
            delete[] bytes_;
        }

        Bytes operator+(const Bytes& bytes) {
            uint8_t* result_bytes = new uint8_t[size_ + bytes.size_];
            memcpy(result_bytes, bytes_, size_);
            memcpy(result_bytes + size_, bytes.bytes_, bytes.size_);
            return Bytes(result_bytes, size_ + bytes.size_);
        }

        Bytes& operator=(const Bytes& bytes) {
            delete[] bytes_;
            size_ = bytes.size_;
            bytes_ = new uint8_t[bytes.size_];
            memcpy(bytes_, bytes.bytes_, size_);
            size_ = bytes.size_;
            return *this;
        }
};