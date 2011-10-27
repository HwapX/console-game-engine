#include "Input.h"

using namespace ConsoleGameEngine;

bool Keyboard::GetKey(const char key)
{
    return(GetAsyncKeyState(key) == -32767);
}

bool Keyboard::GetKeyDown(const char key)
{
    return((GetAsyncKeyState(key) == -32768));
}

char Keyboard::GetKey()
{
    for(byte b = 1; b < 256; b++)
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
