#ifndef CGE_MISC_H
#define CGE_MISC_H

#include <iostream>
#include <windows.h>


using namespace std;

namespace ConsoleGameEngine
{

/**
*A enum with all console colors
*enumerate all suported console colors with
*this enum have two more colors(ClearColor, Transparent) used internaly on engine
*/

typedef byte color;

namespace Colors{
    const color Black = 0;
    const color DarkBlue = 1;
    const color DarkGreen = 2;
    const color DarkCyan = 3;
    const color DarkRed = 4;
    const color DarkMagenta = 5;
    const color DarkYellow = 6;
    const color Gray = 7;
    const color DarkGray = 8;
    const color Blue = 9;
    const color Green = 10;
    const color Cyan = 11;
    const color Red = 12;
    const color Magenta = 13;
    const color Yellow = 14;
    const color White = 15;
    const color Transparent = 0xFF;//17//16;
}

/**
*????
*/

class Vector2
{
public:
    uint16_t x, y;

    Vector2();
    Vector2(uint16_t x, uint16_t y);
    uint16_t operator[](const int i);
};

class Rect
{
public:
    uint16_t x, y, width, height;

    Rect(const Vector2 &position, const Vector2 &size);
    Rect();
};

/**
*A representation of a pixel on console
*This class represent a cell on console screen and store all attributes of this
*/
class Pixel
{
public:
    /**
    *this represent the character displayed
    */
    char character;
    /**
    *this represent the foreground color(font color)
    */
    color forecolor;
    /**
    *this represent the background color
    */
    color backcolor;
    /**
    *the constructor
    */
    Pixel();
    /**
    *this function reset the pixel to default values
    */
    void Reset();
};

}

#endif // CGE_MISC_H
