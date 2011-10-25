#include "Sprite.h"

using namespace ConsoleGameEngine;

Sprite::Sprite(const string &filename)
{
    byte temp = 0;
    std::FILE* in = fopen(filename.c_str(), "r");

    if(in == NULL)
        std::fprintf(stderr, "Can't Open sprite file");

    std::fread((void*)&size.x, 2, 1, in);
    std::fread((void*)&size.y, 2, 1, in);

    AllocData();
    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            std::fread((void*)&data[x][y].character, 1, 1, in);

            std::fread((void*)&temp, 1, 1, in);
            data[x][y].forecolor = (color)temp;

            std::fread((void*)&temp, 1, 1, in);
            data[x][y].backcolor = (color)temp;
        }
    }

    std::fclose(in);
    /*
    ifstream stream(filename.c_str(), ios_base::binary);
    char temp = 0;

    stream >> size.x >> size.y;

    //only to recovery old images
    //stream >> temp;
    //size.x = temp;
    //stream >> temp;
    //size.y = temp;



    AllocData();
    for(uint16_t x = 0; x < size.x; ++x)
        for(uint16_t y = 0; y < size.y; ++y)
        {
            stream.get(data[x][y].character);
            stream.get(temp);
            data[x][y].forecolor = (color)temp;
            stream.get(temp);
            data[x][y].backcolor = (color)temp;
        }

    stream.close();*/
}

Sprite::Sprite(const string &filename, const Vector2 &tilesize, const byte index)
{
    Sprite tileset(filename);
    byte cx = 0, cy = 0, px = 0, py = 0;

    size = tilesize;
    cx = tileset.GetSize().x / tilesize.x;
    cy = tileset.GetSize().y / tilesize.y;
    px = index > cx?index % cx:index;
    py = index > cx?index / cx:0;

    AllocData();
    Clear(Colors::Transparent);
    DrawSprite(tileset, Vector2(0, 0), Rect(Vector2((px -1) * tilesize.x, py * tilesize.y), tilesize));

}

Sprite::Sprite(const Vector2 &sprite_size)
{
    size = sprite_size;
    AllocData();
}

//informar o tamanho da imagem
void Sprite::AllocData()
{
    data = new Pixel*[size.x];
    for(register uint16_t i = 0; i < size.x; ++i)
    {
        data[i] = new Pixel[size.y];
        //verificar a memoria alocada
    }
}

Vector2 Sprite::GetSize()
{
    return(size);
}

Sprite::~Sprite()
{
    for(register uint16_t b = 0; b < size.x; ++b)
    {
        delete [] data[b];
    }
    delete [] data;
}

bool Sprite::DrawSprite(const Sprite &sprite, const Vector2 &position)
{
    for(register uint16_t x = 0; x < sprite.size.x; ++x)
    {
        for(register uint16_t y = 0; y < sprite.size.y; ++y)
        {
            if((position.x + x < size.x) && (position.y + y < size.y))
            {
                if(sprite.data[x][y].backcolor != Colors::Transparent)
                {
                    data[position.x + x][position.y + y] = sprite.data[x][y];
                }
            }
        }
    }

    return true;
}

bool Sprite::DrawSprite(const Sprite &sprite, const Vector2 &position, const Rect &rect)
{
    for(register uint16_t x = 0; x < rect.width; ++x)
    {
        for(register uint16_t y = 0; y < rect.height; ++y)
        {
            if((position.x + x < size.x) && (position.y + y < size.y))
            {
                if(sprite.data[x + rect.x][y + rect.y].backcolor != Colors::Transparent)
                {
                    data[position.x + x][position.y + y] = sprite.data[x + rect.x][y + rect.y];
                }
            }
        }
    }
    return(true);
}

bool Sprite::DrawSpriteCenter(const Sprite &sprite, const Vector2 &position)
{
    return(DrawSprite(sprite, Vector2(((position.x / 2) - (sprite.size.x / 2)), ((position.y / 2) - (sprite.size.y / 2)))));
}


void Sprite::FillBackcolor(color backcolor)
{
    for(register uint16_t x = 0; x < size.x; ++x)
        for(register uint16_t y = 0; y < size.y; ++y)
            data[x][y].backcolor = backcolor;
}

void Sprite::FillForecolor(color forecolor)
{
    for(register uint16_t x = 0; x < size.x; ++x)
        for(register uint16_t y = 0; y < size.y; ++y)
            data[x][y].forecolor = forecolor;
}

byte Sprite::DrawText(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    byte len = text.size();
    register byte b;

    if(position.y >= size.y)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.x + b) >= size.x)
            return(b);
        data[position.x + b][position.y].character = text[b];
        if(backcolor != Colors::Transparent)
            data[position.x + b][position.y].backcolor = backcolor;
        data[position.x + b][position.y].forecolor = forecolor;
    }
    return b;
}

byte Sprite::DrawTextRight(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(DrawText(text, Vector2((position.x - (text.size() -1)), position.y), forecolor, backcolor));
}

byte Sprite::DrawTextCenter(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(DrawText(text, Vector2(position.x - ((text.size() -1) / 2), position.y), forecolor, backcolor));
}

byte Sprite::DrawTextVert(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    byte len = text.size();
    register byte b;

    if(position.x >= size.x)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.y + b) >= size.y)
            return(b);
        data[position.x][position.y + b].character = text[b];
        if(backcolor != Colors::Transparent)
            data[position.x][position.y + b].backcolor = backcolor;
        data[position.x][position.y + b].forecolor = forecolor;
    }
    return b;
}

byte Sprite::DrawTextVertCenter(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (DrawTextVert(text, Vector2(position.x, (position.y / (text.size() -1))), forecolor, backcolor));
}

byte Sprite::DrawTextVertTop(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (DrawTextVert(text, Vector2(position.x, (position.y - (text.size() -1))), forecolor, backcolor));
}

void Sprite::Clear()
{
    Clear(Colors::Black);
}

void Sprite::ReplaceBackcolor(color oldcolor, color newcolor)
{
    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            if(data[x][y].backcolor == oldcolor)
                data[x][y].backcolor = newcolor;
        }
    }
}

void Sprite::ReplaceForecolor(color oldcolor, color newcolor)
{
    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            if(data[x][y].forecolor == oldcolor)
                data[x][y].forecolor = newcolor;
        }
    }
}

void Sprite::Clear(color backcolor)
{
    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            data[x][y].Reset();
            data[x][y].backcolor = backcolor;
        }
    }
}

bool Sprite::DoesItFit(Sprite& sprite, Vector2 position)
{
    if(((position.x + sprite.size.x) >= size.x) &&
            ((position.y + sprite.size.y) >= size.y))
        return false;
    else
        return true;
}

void Sprite::Rotate(uint16_t graus)
{
    //Todo: Esta função deve fazer a rotação do sprite
}

void Sprite::Save(const string &filename)
{
    byte temp = 0;
    FILE* out = std::fopen(filename.c_str(), "w");

    std::fwrite((void*)&size.x, 2, 1, out);
    std::fwrite((void*)&size.y, 2, 1, out);

    if(out == NULL)
        std::fprintf(stderr, "Can't save sprite file");

    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            std::fwrite((void*)&data[x][y].character, 1, 1, out);

            temp = (byte)data[x][y].forecolor;
            std::fwrite((void*)&temp, 1, 1, out);

            temp = (byte)data[x][y].backcolor;
            std::fwrite((void*)&temp, 1, 1, out);
        }
    }

    std::fclose(out);

    /*ofstream stream(filename.c_str(), ios_base::out | ios_base::binary);
    stream.write << size.x << size.y;

    byte temp = 0;

    for(uint16_t x = 0; x < size.x; ++x)
    {
        for(uint16_t y = 0; y < size.y; ++y)
        {
            stream << data[x][y].character;
            temp = (byte)data[x][y].forecolor;
            stream << temp;
            temp = (byte)data[x][y].backcolor;
            stream << temp;
        }
    }

    stream.close();*/
}
