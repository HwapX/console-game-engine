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

string BoolToStr(const bool expression, const string &yes, const string &no)
{
    if(expression)
    {
        return(yes);
    }
    else
    {
        return(no);
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

bool FileExists(const string &filename)
{
    return(GetFileAttributes(filename.c_str()) != 0xFFFFFFFF);
}
/*
uint32_t CompressRLE(const std::vector &data, const uint32_t size, char result[])
{
    uint32_t sequence_size = 0;
    char current = data[0];

}*/
