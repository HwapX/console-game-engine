#include "Utils.h"

string IntToStr(const uint32_t number)
{
    char num[10];
    itoa(number, num, 10);
    return num;
}

string FloatToStr(const float number, const uint8_t places)
{
    char num[25];
    string format = "%." + IntToStr(places) + "f";
    sprintf(num, format.c_str(), number);
    return(num);
}
