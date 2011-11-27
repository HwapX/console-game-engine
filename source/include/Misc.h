#ifndef CGE_MISC_H
#define CGE_MISC_H

#include <iostream>
#include <windows.h>

#define TRANSPARENT_CHAR 0xFF

using namespace std;

namespace ConsoleGameEngine
{

/**
*A enum with all console colors
*enumerate all suported console colors with
*this enum have two more colors(ClearColor, Transparent) used internaly on engine
*/

typedef uint8_t color;

namespace Color
{
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
const color InvertBF = 0xFE;
const color Invert = 0xFD;
const color Transparent = 0xFF;//17//16;
}

typedef uint8_t keycode;

namespace Key
{
const keycode Left = VK_LEFT;
const keycode Right = VK_RIGHT;
const keycode Up = VK_UP;
const keycode Down = VK_DOWN;
const keycode Backspace = VK_BACK;
const keycode Enter = VK_RETURN;
const keycode Escape = VK_ESCAPE;

//const keycode Numpad1
//const keycode Num1
//const keycode A
}

class Vector2
{
public:
    int16_t x, y;

    Vector2();
    Vector2(int16_t x, int16_t y);
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

class Note
{
public:
    uint16_t frequence;
    uint16_t duration;
    Note();
    Note(uint16_t frequence, uint16_t duration);
};

class KeyInfo
{
public:
    bool down;
    uint8_t code;
    char character;

    KeyInfo();
    bool IsValid();
    void Invalidate();
};

class MouseInfo
{
public:
    Vector2 position;
    uint8_t left;
    uint8_t right;
    int8_t wheel;
    int8_t hwheel;
    bool moving;

    MouseInfo();
};
}

#endif // CGE_MISC_H
