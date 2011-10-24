#ifndef CGE_MISC_H
#define CGE_MISC_H

#include <iostream>
#include <windows.h>


using namespace std;

/**
*A enum with all console colors
*enumerate all suported console colors with
*this enum have two more colors(ClearColor, Transparent) used internaly on engine
*/
enum Color
{
    Black       = 0,
    b        = FOREGROUND_INTENSITY,
    LightGrey   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    White       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    Blue        = FOREGROUND_BLUE,
    Green       = FOREGROUND_GREEN,
    Cyan        = FOREGROUND_GREEN | FOREGROUND_BLUE,
    Red         = FOREGROUND_RED,
    Purple      = FOREGROUND_RED   | FOREGROUND_BLUE,
    LightBlue   = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LightCyan   = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightRed    = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    LightPurple = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    Orange      = FOREGROUND_RED   | FOREGROUND_GREEN,
    Yellow      = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    ClearColor  = 0x00FFFFFF,
    Transparent = 0xFFFFFFFF,
};


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
    Color forecolor;
    /**
    *this represent the background color
    */
    Color backcolor;
    /**
    *the constructor
    */
    Pixel();
    /**
    *this function reset the pixel to default values
    */
    void Reset();
};

#endif // CGE_MISC_H
