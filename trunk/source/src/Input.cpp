#include "Input.h"

using namespace ConsoleGameEngine;

bool Keyboard::GetKey(char key)
{
    if(key >= '0' && key <= '9')
    {
        key-= '0';
        return((GetAsyncKeyState(key + '0') == -32767) || (GetAsyncKeyState(key + 0x60) == -32767));
    }
    else if(key >= '*' && key <= '/')
    {
        key-= '+';
        return((GetAsyncKeyState(key + 0x6B) == -32767) || (GetAsyncKeyState(key + 0xBB) == -32767));
    }

    switch(key)
    {
    case '\n':
        key = VK_RETURN;
        break;
    case '\b':
        key = VK_BACK;
        break;
    case ',':
        key = 0xBE;
        break;
    case '.':
        key = 0xBC;
        break;
    }
    return(GetAsyncKeyState(key) == -32767);
}

bool Keyboard::GetKeyDown(const char key)
{
    return((GetAsyncKeyState(key) == -32768));
}

char Keyboard::GetKey()
{
    for(uint8_t b = 1; b < 256; b++)
    {
        if(GetKey(b))
        {
            return(b);

        }
    }
    return(0);
}

char Keyboard::GetNextKey()
{
    char key = 0;
    do
    {
        key = GetKey();
    }
    while(!key);
    return(key);
}
/*
char Keyboard::TranslateKey(const char key)
{
    switch(key)
    {
    case '+':
        return(VK_ADD);
    }

    return(key);
}
*/
