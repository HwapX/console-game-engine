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
const color InvertFB = 0xFD;
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
const keycode ScrollLock = VK_SCROLL;
const keycode CapsLock = VK_CONTROL;
const keycode NumLock = VK_NUMLOCK;
const keycode Shift = VK_SHIFT;
const keycode LeftShift = VK_LSHIFT;
const keycode RightShift = VK_RSHIFT;
const keycode LeftControl = VK_LCONTROL;
const keycode RightControl = VK_RCONTROL;
const keycode Alt = VK_MENU;
const keycode LeftAlt = VK_LMENU;
const keycode RightAlt = VK_RMENU;

const keycode Space = VK_SPACE;

//const keycode Numpad1
//const keycode Num1
//const keycode A

const keycode CapsLock_On = CAPSLOCK_ON;
const keycode NumLock_On = NUMLOCK_ON;
const keycode ScrollLock_On = SCROLLLOCK_ON;
}

const char TransparentChar = 0xFF;
const char NullChar = 0;

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

class Pixel
{
public:
    char character;
    color forecolor;
    color backcolor;

    Pixel();

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
    int8_t middle;
    bool moving;

    MouseInfo();
};
}

#endif // CGE_MISC_H
