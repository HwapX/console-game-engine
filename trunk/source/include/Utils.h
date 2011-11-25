#ifndef CGE_UTILS_H
#define CGE_UTILS_H

#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

string IntToStr(const uint32_t number);
string FloatToStr(const float number, const uint8_t places = 2);

#endif // CGE_UTILS_H