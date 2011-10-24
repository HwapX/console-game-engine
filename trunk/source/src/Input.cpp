#include "Input.h"

bool Keyboard::GetKey(int key)
{
    return(GetAsyncKeyState(key) == -32767);
}

bool Keyboard::GetKey_down(int key)
{
    return((GetAsyncKeyState(key) == -32768));
}

byte Keyboard::GetKey()
{
    //for(char b = 32;b < 127;b++)
    for(byte b = 1; b < 256; b++)
        if(GetKey(b))
            return b;
    return(0);
}

byte Keyboard::GetNextKey()
{
    byte key = 0;
    do
    {
        key = GetKey();
    }
    while(!key);
    return(key);
}
