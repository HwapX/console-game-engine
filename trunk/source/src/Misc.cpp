#include "Misc.h"

using namespace ConsoleGameEngine;

/*---------------------------*/
/*----------Vector2----------*/
/*---------------------------*/

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(int16_t x, int16_t y)
{
    this->x = x;
    this->y = y;
}

/*-------------------------*/
/*----------Rect-----------*/
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

/*-------------------------*/
/*----------Pixel----------*/
/*-------------------------*/

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

/*-------------------------*/
/*----------Pixel----------*/
/*-------------------------*/

Note::Note()
{
    frequence = 0;
    duration = 0;
}

Note::Note(uint16_t frequence, uint16_t duration)
{
    this->frequence = frequence;
    this->duration = duration;
}
