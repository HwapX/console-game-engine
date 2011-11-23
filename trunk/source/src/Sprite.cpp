#include "Sprite.h"
#include <Vector>
using namespace ConsoleGameEngine;

uint32_t CompressRLE(uint8_t *data, uint32_t size, uint8_t **result)
{
    //return new size
}

uint32_t UnCompressRLE(uint8_t *data, uint32_t size, uint8_t *result)
{
    //return new size
}

Sprite::Sprite(const string &filename)
{
    uint8_t temp = 0;
    Vector2 temp_size;
    std::FILE* in = std::fopen(filename.c_str(), "rb");

    if(in == NULL)
        std::fprintf(stderr, "Can't Open sprite file");

    std::fread((void*)&temp_size.x, 2, 1, in);
    std::fread((void*)&temp_size.y, 2, 1, in);

    if(!this->AllocData(temp_size))
    {
        return;
    }

    for(register uint16_t x = 0; x < temp_size.x; ++x)
    {
        for(register uint16_t y = 0; y < temp_size.y; ++y)
        {
            std::fread((void*)&data[x][y].character, 1, 1, in);

            std::fread((void*)&temp, 1, 1, in);
            this->data[x][y].forecolor = (color)temp;

            std::fread((void*)&temp, 1, 1, in);
            this->data[x][y].backcolor = (color)temp;
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

bool Sprite::CreateFromTileset(Sprite &tileset, const Vector2 &tilesize, const uint8_t index)
{
    uint8_t cx = 0, px = 0, py = 0;

    cx = tileset.GetSize().x / tilesize.x;

    px = index % cx;
    py = index / cx;

    if(!this->AllocData(tilesize))
    {
        return(false);
    }
    this->Clear(Colors::Transparent);
    this->DrawSprite(tileset, Vector2(0, 0), Rect(Vector2(px * tilesize.x, py * tilesize.y), tilesize));
    return(true);
}

Sprite::Sprite(Sprite &tileset, const Vector2 &tilesize, const uint8_t index)
{
    this->CreateFromTileset(tileset, tilesize, index);
}

Sprite::Sprite(const string &filename, const Vector2 &tilesize, const uint8_t index)
{
    Sprite tileset(filename);
    CreateFromTileset(tileset, tilesize, index);
}

Sprite::Sprite(const Vector2 &sprite_size)
{
    AllocData(sprite_size);
}

bool Sprite::AllocData(const Vector2 &data_size)
{
    data = new Pixel*[data_size.x];

    for(register uint16_t i = 0; i < data_size.x; ++i)
    {
        this->data[i] = new Pixel[data_size.y];
    }
    size = data_size;
    return(true);
}

Vector2 Sprite::GetSize()
{
    return(size);
}

void Sprite::DeallocData(const uint16_t size_x)
{
    for(register uint16_t i = 0; i < size_x; ++i)
    {
        delete [] this->data[i];
    }
    delete [] this->data;
    this->size = Vector2(0, 0);
}

Sprite::~Sprite()
{
    DeallocData(this->size.x);
}

bool Sprite::DrawSprite(const Sprite &sprite, const Vector2 &position)
{
    return(this->DrawSprite(sprite, position, Rect(Vector2(0, 0), sprite.size)));
}

bool Sprite::DrawSprite(const Sprite &sprite, const Vector2 &position, const Rect &rect)
{
    for(register uint16_t x = 0; x < rect.width; ++x)
    {
        for(register uint16_t y = 0; y < rect.height; ++y)
        {
            if((position.x + x < this->size.x) && (position.y + y < this->size.y))
            {
                if(sprite.data[x + rect.x][y + rect.y].backcolor != Colors::Transparent)
                {
                    this->data[position.x + x][position.y + y].backcolor = sprite.data[x + rect.x][y + rect.y].backcolor;
                }
                this->data[position.x + x][position.y + y].forecolor = sprite.data[x + rect.x][y + rect.y].forecolor;
                this->data[position.x + x][position.y + y].character = sprite.data[x + rect.x][y + rect.y].character;
            }
        }
    }
    return(true);
}

bool Sprite::DrawSpriteCenter(const Sprite &sprite, const Vector2 &position)
{
    return(this->DrawSprite(sprite, Vector2((position.x - (sprite.size.x / 2)), position.y)));
}


void Sprite::FillBackcolor(const color backcolor)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].backcolor = backcolor;
        }
    }
}

void Sprite::FillForecolor(const color forecolor)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].forecolor = forecolor;
        }
    }
}

uint8_t Sprite::DrawText(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    uint8_t len = text.size();
    register uint8_t b;

    if(position.y >= this->size.y)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.x + b) >= this->size.x)
            return(b);
        this->data[position.x + b][position.y].character = text[b];
        if(backcolor != Colors::Transparent)
            this->data[position.x + b][position.y].backcolor = backcolor;
        this->data[position.x + b][position.y].forecolor = forecolor;
    }
    return b;
}

uint8_t Sprite::DrawTextRight(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(this->DrawText(text, Vector2((position.x - (text.size() -1)), position.y), forecolor, backcolor));
}

uint8_t Sprite::DrawTextCenter(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(this->DrawText(text, Vector2(position.x - ((text.size() -1) / 2), position.y), forecolor, backcolor));
}

uint8_t Sprite::DrawTextVert(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    uint8_t len = text.size();
    register uint8_t b;

    if(position.x >= this->size.x)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.y + b) >= this->size.y)
            return(b);
        this->data[position.x][position.y + b].character = text[b];
        if(backcolor != Colors::Transparent)
            this->data[position.x][position.y + b].backcolor = backcolor;
        this->data[position.x][position.y + b].forecolor = forecolor;
    }
    return b;
}

uint8_t Sprite::DrawTextVertCenter(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (this->DrawTextVert(text, Vector2(position.x, (position.y / (text.size() -1))), forecolor, backcolor));
}

uint8_t Sprite::DrawTextVertTop(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (this->DrawTextVert(text, Vector2(position.x, (position.y - (text.size() -1))), forecolor, backcolor));
}

void Sprite::Clear()
{
    this->Clear(Colors::Black);
}

void Sprite::FloodBackcolor(const Vector2 &position, const color oldcolor, const color newcolor)
{
    if(oldcolor == newcolor)
        return;
    if(position.x < this->size.x && position.y < this->size.y && position.x >= 0 && position.y >= 0)
    {
        this->data[position.x][position.y].backcolor = newcolor;
    }
    if(position.x+1 < this->size.x)
    {
        if(this->data[position.x +1][position.y].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x+1, position.y), oldcolor, newcolor);
    }
    if(position.x-1 >= 0)
    {
        if(this->data[position.x-1][position.y].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x-1, position.y), oldcolor, newcolor);
    }
    if(position.y+1 < this->size.y)
    {
        if(this->data[position.x][position.y +1].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x, position.y+1), oldcolor, newcolor);
    }
    if(position.y-1 >= 0)
    {
        if(this->data[position.x][position.y-1].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x, position.y -1), oldcolor, newcolor);
    }
}

bool Sprite::PutPixel(const Vector2 &coord, const Pixel &pixel_data)
{
    if((coord.x < this->size.x && coord.y < this->size.y) && !(coord.x < 0 && coord.y < 0))
    {
        this->data[coord.x][coord.y] = pixel_data;
        return(true);
    }

    return(false);
}

Pixel &Sprite::operator()(const Vector2 &position)
{
    if((position.x < this->size.x && position.y < this->size.y) && !(position.x < 0 && position.y < 0))
    {
        return(this->data[position.x][position.y]);
    }
    else
    {
        throw("Out memory, Invalid pixel position");
    }
}
/*
Pixel *Sprite::GetPixel(const Vector2 &coord)
{
    if((coord.x < this->size.x && coord.y < this->size.y) && !(coord.x < 0 && coord.y < 0))
    {
        return(&this->data[coord.x][coord.y]);
    }

    return(NULL);
}*/

void Sprite::ReplaceBackcolor(const color oldcolor, const color newcolor)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            if(this->data[x][y].backcolor == oldcolor)
                this->data[x][y].backcolor = newcolor;
        }
    }
}

void Sprite::ReplaceForecolor(const color oldcolor, const color newcolor)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            if(this->data[x][y].forecolor == oldcolor)
                this->data[x][y].forecolor = newcolor;
        }
    }
}

bool Sprite::Resize(const Vector2 &newsize)
{
    Sprite bkp(this->size);

    bkp.DrawSprite(*this, Vector2(0, 0));
    this->DeallocData(this->size.x);
    this->AllocData(newsize);
    this->DrawSprite(bkp, Vector2(0, 0));
    return(true);
}

void Sprite::Clear(color backcolor)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].Reset();
            this->data[x][y].backcolor = backcolor;
        }
    }
}

bool Sprite::DoesItFit(Sprite& sprite, Vector2 position)
{
    if(((position.x + sprite.size.x) >= this->size.x) &&
            ((position.y + sprite.size.y) >= this->size.y))
        return(false);
    else
        return(true);
}

void Sprite::Rotate(uint16_t graus)
{
    //Todo: Esta fun��o deve fazer a rota��o do sprite
}

void Sprite::Save(const string &filename)
{
    uint8_t temp = 0;
    FILE* out = std::fopen(filename.c_str(), "w");

    std::fwrite((void*)&this->size.x, 2, 1, out);
    std::fwrite((void*)&this->size.y, 2, 1, out);

    if(out == NULL)
        std::fprintf(stderr, "Can't save sprite file");

    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            std::fwrite((void*)&this->data[x][y].character, 1, 1, out);

            temp = (uint8_t)this->data[x][y].forecolor;
            std::fwrite((void*)&temp, 1, 1, out);

            temp = (uint8_t)this->data[x][y].backcolor;
            std::fwrite((void*)&temp, 1, 1, out);
        }
    }

    std::fclose(out);


    /*ofstream stream(filename.c_str(), ios_base::out | ios_base::binary);
    stream.write << size.x << size.y;

    uint8_t temp = 0;

    for(uint16_t x = 0; x < size.x; ++x)
    {
        for(uint16_t y = 0; y < size.y; ++y)
        {
            stream << data[x][y].character;
            temp = (uint8_t)data[x][y].forecolor;
            stream << temp;
            temp = (uint8_t)data[x][y].backcolor;
            stream << temp;
        }
    }

    stream.close();*/
}
