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
    void DeallocData(const uint16_t size_x);
public:

    Vector2 GetSize();

    bool PutPixel(const Vector2&, const Pixel&);
    Pixel &GetPixel(const Vector2&);
    Pixel &operator()(Vector2);

    void FloodBackcolor(const Vector2 &position, const color oldcolor, const color newcolor);

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

    void FillForecolor(color forecolor);

    void Clear(color backcolor, color forecolor);

    void Clear(color backcolor);

    void Clear();

    void Save(const string &savename);
};

}

#endif // CGE_SPRITE_H
