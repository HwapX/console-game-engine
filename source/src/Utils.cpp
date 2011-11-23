#include "Utils.h"

string IntToStr(uint32_t number)
{
    char num[10];
    itoa(number, num, 10);
    return num;
}
