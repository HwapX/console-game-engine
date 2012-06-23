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

uint32_t CompressRLE(const char data[], const uint32_t size, char **result);
uint32_t DecompressRLE(const char data[], const uint32_t size, char **result);

bool CopyFile(string source, string dest);
int FindDataInFile(char filepath[], char data[], uint16_t size, int start = 0);

bool CompareFileData(char filepath[], int position, char data[], int size);
bool CompareData(char data1[], char data2[], int size);
bool CompareFileWithFile(char filepath1[], int offset1, char filepath2[], int offset2, int size);

int GetResource(short resid, char type[], void **result);

#endif // CGE_UTILS_H
