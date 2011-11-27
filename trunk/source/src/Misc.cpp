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
    forecolor = Color::Gray;
    backcolor = Color::Black;
}

/*-------------------------*/
/*-----------Note----------*/
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

/*-------------------------*/
/*----------KeyInfo--------*/
/*-------------------------*/

KeyInfo::KeyInfo()
{
    this->Invalidate();
}

bool KeyInfo::IsValid()
{
    return(this->code);// + this->character);
}

void KeyInfo::Invalidate()
{
    this->code = 0;
    this->character = 0;
    this->down = false;
}

/*-------------------------*/
/*--------MouseInfo--------*/
/*-------------------------*/

MouseInfo::MouseInfo()
{
    wheel = 0;
    hwheel = 0;
    left =0;
    right = 0;
    moving = false;
}
