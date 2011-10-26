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
protected:
    Vector2 size;
    /**
    *a two-dimensional matrix of pixel, that represent all pixels of sprite.
    */

    bool AllocData(const Vector2 &data_size);
    void DeallocData(const uint16_t size_x);
public:
    Pixel** data;
    /**
    *
    */
    Vector2 GetSize();

    bool PutPixel(const Vector2 &coord, const Pixel &pixel_data);

    Pixel *GetPixel(const Vector2 &coord);

    void FloodBackcolor(const Vector2 &position, const color oldcolor, const color newcolor);

    /**
    *load a sprite from file.
    *@param filename path of file to load.
    */
    Sprite(const string &filename);
    /**
    *create a sprite with informed size.
    */
    Sprite(const Vector2 &sprite_size);

    Sprite(const string &filename, const Vector2 &tilesize, const byte index);

    void ReplaceBackcolor(const color oldcolor, const color newcolor);

    void ReplaceForecolor(const color oldcolor, const color newcolor);

    bool Resize(const Vector2 &newsize);

    ~Sprite();

    /**
    *this function draw a sprite on this sprite
    *@param sprite the sprite to draw
    *@param position the position to draw
    *@return return true if the draw as succeeded or false if fail
    */
    bool DrawSprite(const Sprite &sprite, const Vector2 &position);

    bool DrawSprite(const Sprite &sprite, const Vector2 &position, const Rect &rect);
    /**
    *this function draw a sprite on center of relative position informed.
    *@param sprite the sprite to draw
    *@param position the position to draw
    *@return return true if the draw as succeeded or false if fail
    *@see DrawSprite
    */
    bool DrawSpriteCenter(const Sprite &sprite, const Vector2 &position);
    /**
    *Draw a text
    *this function draw a text on position informed, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawTextCenter
    *@see DrawText_right
    *@see DrawText_vert
    *@see DrawTextVertTop
    *@see DrawTextVertCenter
    */
    byte DrawText(const string &text, const Vector2 &position, const color forecolor, const color backcolor);
    /**
    *Draw a text
    *this function draw a vectical text on informed position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawTextCenter
    *@see DrawText_right
    *@see DrawTextVertTop
    *@see DrawTextVertCenter
    *@see DrawText
    */
    byte DrawTextVert(const string &text, const Vector2 &position, color forecolor, const color backcolor);
    /**
    *Draw a text
    *this function draw a text on right of position informed, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawTextCenter
    *@see DrawText_vert
    *@see DrawTextVertTop
    *@see DrawTextVertCenter
    *@see DrawText
    */
    byte DrawTextRight(const string &text, const Vector2 &position, color forecolor, color backcolor);
    /**
    *Draw a text
    *this function draw a text in a center relative position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawText_right
    *@see DrawText_vert
    *@see DrawTextVertTop
    *@see DrawTextVertCenter
    *@see DrawText
    */
    byte DrawTextCenter(const string &text, const Vector2 &position, color forecolor, color backcolor);
    /**
    *Draw a text
    *this function draw a vectical text in a given vectical relative position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawTextCenter
    *@see DrawText_right
    *@see DrawText_vert
    *@see DrawTextVertTop
    *@see DrawText
    */
    byte DrawTextVertCenter(const string &text, const Vector2 &position, color forecolor, color backcolor);
    /**
    *Draw a text
    *this function draw a text on top of informed position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see DrawTextCenter
    *@see DrawText_right
    *@see DrawText_vert
    *@see DrawTextVertCenter
    *@see DrawText
    */
    byte DrawTextVertTop(const string &text, const Vector2 &position, color forecolor, color backcolor);
    /**
    *this function check if a sprite fit this drawing in a informed position.
    *@param sprite the sprite to check
    *@param position the position to test
    *@return return true if fit  or false if not;
    */
    bool DoesItFit(Sprite& sprite, Vector2 position);
    /**
    *nothing actually
    */
    void Rotate(uint16_t graus);
    /**
    *fill all sprite background color with color informed.
    *@param backcolor background color to fill
    *@see FillBackcolor
    */
    void FillBackcolor(color backcolor);
    /**
    *fill all sprite foreground color with color informed.
    *@param forecolor foreground color to fill
    *@see FillForecolor
    */
    void FillForecolor(color forecolor);
    /**
    *Clear all sprite with backcolor and forecolor informed.
    */
    void Clear(color backcolor, color forecolor);
    /**
    *Clear all sprite and fill with color informed.
    */
    void Clear(color backcolor);
    /**
    *Clear all sprite and fill with black color.
    */
    void Clear();
    /**
    *Save sprite with file name informed.
    *@param savename name that the file should be saved
    */
    void Save(const string &savename);
};

}

#endif // CGE_SPRITE_H
