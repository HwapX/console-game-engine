#ifndef CGE_SPRITE_H
#define CGE_SPRITE_H

#include <iostream>
#include <cstdio>

#include "Misc.h"

using namespace std;

namespace ConsoleGameEngine
{

/**
*Represent a image on engine
*?
*/
class Sprite
{
private:
    bool CreateFromTileset(Sprite &tileset, const Vector2 &tilesize, const uint8_t index);
protected:
    Vector2 size;
    Pixel** data;
    bool AllocData(const Vector2 &data_size);
    void DeallocData();
public:

    Vector2 GetSize();

    Pixel &GetPixel(const Vector2&);
    Pixel &GetPixel(uint16_t x, uint16_t y);
    Pixel &operator()(Vector2);
    Pixel &operator()(uint16_t x, uint16_t y);
    Sprite &operator=(Sprite &sprite);

    Sprite(Sprite &sprite);
    Sprite(const string &filename);
    Sprite(const Vector2 &sprite_size);
    Sprite(Sprite &tileset, const Vector2 &tilesize, const uint8_t index);
    Sprite(const string &filename, const Vector2 &tilesize, const uint8_t index);

    void ReplaceBackcolor(const color oldcolor, const color newcolor);
    void ReplaceForecolor(const color oldcolor, const color newcolor);

    bool Resize(const Vector2 &newsize);

    ~Sprite();

    bool DrawSprite(const Sprite &sprite, const Vector2 &position);
    bool DrawSprite(const Sprite &sprite, const Vector2 &position, const Rect &rect);
    bool DrawSpriteCenter(const Sprite &sprite, const Vector2 &position);

    uint8_t DrawText(const string &text, const Vector2 &position, const color forecolor, const color backcolor);
    uint8_t DrawTextVert(const string &text, const Vector2 &position, color forecolor, const color backcolor);
    uint8_t DrawTextRight(const string &text, const Vector2 &position, color forecolor, color backcolor);
    uint8_t DrawTextCenter(const string &text, const Vector2 &position, color forecolor, color backcolor);
    uint8_t DrawTextVertCenter(const string &text, const Vector2 &position, color forecolor, color backcolor);
    uint8_t DrawTextVertTop(const string &text, const Vector2 &position, color forecolor, color backcolor);

    bool DoesItFit(Sprite& sprite, Vector2 position);
    void Rotate(uint16_t graus);

    void FillBackcolor(color backcolor);
    void FillBackcolor(const color backcolor, const Rect &rect);
    void FillForecolor(color forecolor);
    void FillForecolor(const color forecolor, const Rect &rect);
    void FillCharacter(const char character);
    void FillCharacter(const char character, const Rect &rect);

    void FloodBackcolor(const Vector2 &position, const color oldcolor, const color newcolor);
    void FloodForecolor(const Vector2 &position, const color oldcolor, const color newcolor);
    void FloodCharacter(const Vector2 &position, const color oldchar, const color newchar);

    void Clear(color backcolor, color forecolor, char character);
    void Clear(color backcolor, char character);
    void Clear(color backcolor);
    void Clear();

    void Save(const string &savename);
};

}

#endif // CGE_SPRITE_H
