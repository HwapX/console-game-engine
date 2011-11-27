#include "Utils.h"

string IntToStr(const uint32_t number, const uint8_t digits)
{
    string num;
    char cnum[16];
    itoa(number, cnum, 10);
    num = cnum;
    if(num.size() < digits)
    {
        num.insert(0, digits - num.size(), '0');
    }
    return(num);
}

string FloatToStr(const float number, const uint8_t digits)
{
    char num[25];
    string format = "%." + IntToStr(digits) + "f";
    sprintf(num, format.c_str(), number);
    return(num);
}

string BoolToStr(const bool expression)
{
    if(expression)
    {
        return("true");
    }
    else
    {
        return("false");
    }
}

string IntToHex(const uint32_t number, const uint8_t digits)
{
    string num;
    char cnum[16];
    itoa(number, cnum, 16);
    num = cnum;
    if(num.size() < digits)
    {
        num.insert(0, digits - num.size(), '0');
    }
    return(num);
}

string ToUpper(const string &text)
{
    string new_text;
    for(uint16_t i = 0; i < text.size(); ++i)
    {
        new_text+= toupper(text[i]);
    }
    return(new_text);
}

string ToLower(const string &text)
{
    string new_text;
    for(uint16_t i = 0; i < text.size(); ++i)
    {
        new_text+= tolower(text[i]);
    }
    return(new_text);
}

char ToUpper(char character)
{
    return(toupper(character));
}

char ToLower(char character)
{
    return(tolower(character));
}
