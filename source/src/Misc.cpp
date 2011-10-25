#include "Misc.h"

using namespace ConsoleGameEngine;

Pixel::Pixel()
{
    Reset();
}

void Pixel::Reset()
{
    character = ' ';
    forecolor = Colors::Gray;
    backcolor = Colors::Black;
}

/*---------------------------*/
/*----------Vector2----------*/
/*---------------------------*/

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(uint16_t x, uint16_t y)
{
    this->x = x;
    this->y = y;
}

/*-------------------------*/
/*----------Pixel----------*/
/*-------------------------*/

Rect::Rect()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

Rect::Rect(const Vector2 &position, const Vector2 &size)
{
    x = position.x;
    y = position.y;
    width = size.x;
    height = size.y;
}

