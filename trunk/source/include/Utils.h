#ifndef CGE_UTILS_H
#define CGE_UTILS_H

#include <string>
#include <cstdlib>
#include <cstdio>

#include <windows.h>

using namespace std;

string IntToStr(const uint32_t number, const uint8_t digits = 0);
string FloatToStr(const float number, const uint8_t digits = 2);
string BoolToStr(const bool expression, const string &yes = "true", const string &no = "false");
string IntToHex(const uint32_t number, const uint8_t digits = 0);

string ToUpper(const string &text);
string ToLower(const string &text);

char ToUpper(char character);
char ToLower(char character);

bool FileExists(const string &filename);


#endif // CGE_UTILS_H
