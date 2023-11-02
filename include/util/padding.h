#pragma once
#include <cstdint>
#include <iostream>

using std::string;

string pad(string data, uint32_t pad_size);
string unpad(string data, uint32_t pad_size);