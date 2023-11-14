#pragma once
#include "./bytes.h"

Bytes Pad(Bytes& data, uint8_t pad_size);
Bytes Unpad(Bytes& data, uint8_t pad_size);