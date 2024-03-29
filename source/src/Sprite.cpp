#include "Sprite.h"

using namespace ConsoleGameEngine;

Sprite::Sprite(Sprite &sprite)
{
    //AllocData(sprite.GetSize());
    data = NULL;
    *this = sprite;
}

Sprite::Sprite(const string &filename)
{
    Vector2 temp_size;
    std::FILE* in = std::fopen(filename.c_str(), "rb");

    if(in == NULL)
    {
        throw("Cant open file");
    }

    std::fread((void*)&temp_size.x, 2, 1, in);
    std::fread((void*)&temp_size.y, 2, 1, in);

    this->AllocData(temp_size);

    for(register uint16_t x = 0; x < temp_size.x; ++x)
    {
        for(register uint16_t y = 0; y < temp_size.y; ++y)
        {
            std::fread((void*)&data[x][y].character, 1, 1, in);
            std::fread((void*)&this->data[x][y].forecolor, 1, 1, in);
            std::fread((void*)&this->data[x][y].backcolor, 1, 1, in);
        }
    }

    std::fclose(in);
}

bool Sprite::CreateFromTileset(Sprite &tileset, const Vector2 &tilesize, const uint8_t index)
{
    uint8_t cx = 0, px = 0, py = 0;

    cx = tileset.GetSize().x / tilesize.x;

    px = index % cx;
    py = index / cx;

    this->AllocData(tilesize);
    this->Clear(Color::Transparent);
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

Sprite::Sprite(const short resid)
{
    char *resdata = NULL;
    int ressize = GetResource(resid, RT_RCDATA, (void**)&resdata);
    if(ressize > 0)
    {
        uint16_t p = 4;
        AllocData(Vector2(*(short*)&resdata[0], *(short*)&resdata[2]));
        for(register uint16_t x = 0; x < size.x; ++x)
        {
            for(register uint16_t y = 0; y < size.y; ++y)
            {
                data[x][y].character = resdata[p];
                ++p;
                this->data[x][y].forecolor = resdata[p];
                ++p;
                this->data[x][y].backcolor = resdata[p];
                ++p;
            }
        }
    }
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

void Sprite::DeallocData()
{
    if(this->data != NULL)
    {
        for(register uint16_t i = 0; i < size.x; ++i)
        {
            delete [] this->data[i];
        }
        delete [] this->data;
        this->size = Vector2(0, 0);
    }
}

Sprite::~Sprite()
{
    DeallocData();
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
            if((position.x + x < this->size.x) && (position.y + y < this->size.y) && (position.x + x >= 0 && position.y + y >= 0))
            {
                if(sprite.data[x + rect.x][y + rect.y].backcolor != Color::Transparent)
                {
                    this->data[position.x + x][position.y + y].backcolor = sprite.data[x + rect.x][y + rect.y].backcolor;
                }
                if(sprite.data[x + rect.x][y + rect.y].character != 0)
                {
                    this->data[position.x + x][position.y + y].character = sprite.data[x + rect.x][y + rect.y].character;
                }
                if(sprite.data[x + rect.x][y + rect.y].forecolor != Color::Transparent)
                {
                    this->data[position.x + x][position.y + y].forecolor = sprite.data[x + rect.x][y + rect.y].forecolor;
                }
            }
        }
    }
    return(true);
}

bool Sprite::DrawSpriteCenter(const Sprite &sprite, const Vector2 &position)
{
    return(this->DrawSprite(sprite, Vector2((position.x - (sprite.size.x / 2)), position.y)));
}


void Sprite::FillCharacter(const char character, const Rect &rect)
{
    for(register uint16_t x = rect.x; x < rect.x + rect.width; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].character = character;
        }
    }
}

void Sprite::FillBackcolor(const color backcolor, const Rect &rect)
{
    for(register uint16_t x = rect.x; x < rect.x + rect.width; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].backcolor = backcolor;
        }
    }
}

void Sprite::FillForecolor(const color forecolor, const Rect &rect)
{
    for(register uint16_t x = rect.x; x < rect.x + rect.width; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].forecolor = forecolor;
        }
    }
}

void Sprite::FillBackcolor(const color backcolor)
{
    this->FillBackcolor(backcolor, Rect(Vector2(0, 0), size));
}

void Sprite::FillForecolor(const color forecolor)
{
    this->FillForecolor(forecolor, Rect(Vector2(0, 0), size));
}

void Sprite::FillCharacter(const char character)
{
    this->FillCharacter(character, Rect(Vector2(0, 0), size));
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
        {
            return(b);
        }
//        if(text[b] != '\0')
//        {
        this->data[position.x + b][position.y].character = text[b];
//        }
        if(backcolor != Color::Transparent)
        {
            this->data[position.x + b][position.y].backcolor = backcolor;
        }
        if(forecolor != Color::Transparent)
        {
            this->data[position.x + b][position.y].forecolor = forecolor;
        }
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
        if(backcolor != Color::Transparent)
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

void Sprite::FloodBackcolor(const Vector2 &position, const color newcolor)
{
    color oldcolor = this->GetPixel(position).backcolor;
    if(oldcolor == newcolor)
        return;
    if(position.x < this->size.x && position.y < this->size.y && position.x >= 0 && position.y >= 0)
    {
        this->data[position.x][position.y].backcolor = newcolor;
    }
    if(position.x+1 < this->size.x)
    {
        if(this->data[position.x +1][position.y].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x+1, position.y),newcolor);
    }
    if(position.x-1 >= 0)
    {
        if(this->data[position.x-1][position.y].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x-1, position.y), newcolor);
    }
    if(position.y+1 < this->size.y)
    {
        if(this->data[position.x][position.y +1].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x, position.y+1), newcolor);
    }
    if(position.y-1 >= 0)
    {
        if(this->data[position.x][position.y-1].backcolor == oldcolor)
            this->FloodBackcolor(Vector2(position.x, position.y -1), newcolor);
    }
}

void Sprite::FloodCharacter(const Vector2 &position, const char newchar)
{
    char oldchar = this->GetPixel(position).character;
    if(oldchar == newchar)
        return;
    if(position.x < this->size.x && position.y < this->size.y && position.x >= 0 && position.y >= 0)
    {
        this->data[position.x][position.y].character = newchar;
    }
    if(position.x+1 < this->size.x)
    {
        if(this->data[position.x +1][position.y].character == oldchar)
            this->FloodCharacter(Vector2(position.x+1, position.y), newchar);
    }
    if(position.x-1 >= 0)
    {
        if(this->data[position.x-1][position.y].character == oldchar)
            this->FloodCharacter(Vector2(position.x-1, position.y), newchar);
    }
    if(position.y+1 < this->size.y)
    {
        if(this->data[position.x][position.y +1].character == oldchar)
            this->FloodCharacter(Vector2(position.x, position.y+1), newchar);
    }
    if(position.y-1 >= 0)
    {
        if(this->data[position.x][position.y-1].character == oldchar)
            this->FloodCharacter(Vector2(position.x, position.y -1), newchar);
    }
}

void Sprite::FloodForecolor(const Vector2 &position, const color newcolor)
{
    color oldcolor = this->GetPixel(position).forecolor;
    if(oldcolor == newcolor)
        return;
    if(position.x < this->size.x && position.y < this->size.y && position.x >= 0 && position.y >= 0)
    {
        this->data[position.x][position.y].forecolor = newcolor;
    }
    if(position.x+1 < this->size.x)
    {
        if(this->data[position.x +1][position.y].forecolor == oldcolor)
            this->FloodForecolor(Vector2(position.x+1, position.y), newcolor);
    }
    if(position.x-1 >= 0)
    {
        if(this->data[position.x-1][position.y].forecolor == oldcolor)
            this->FloodForecolor(Vector2(position.x-1, position.y), newcolor);
    }
    if(position.y+1 < this->size.y)
    {
        if(this->data[position.x][position.y +1].forecolor == oldcolor)
            this->FloodForecolor(Vector2(position.x, position.y+1), newcolor);
    }
    if(position.y-1 >= 0)
    {
        if(this->data[position.x][position.y-1].forecolor == oldcolor)
            this->FloodForecolor(Vector2(position.x, position.y -1), newcolor);
    }
}

Pixel &Sprite::GetPixel(const Vector2 &coord)
{
    if((coord.x < this->size.x && coord.y < this->size.y) && (coord.x >= 0 && coord.y >= 0))
    {
        return(this->data[coord.x][coord.y]);
    }
    else
    {
        throw("Out memory");
    }
}

Pixel &Sprite::operator()(const uint16_t x, const uint16_t y)
{
    return(this->GetPixel(Vector2(x, y)));
}

Pixel &Sprite::operator()(Vector2 coord)
{
    return(this->GetPixel(coord));
}

Sprite &Sprite::operator=(Sprite &sprite)
{
    this->DeallocData();
    this->AllocData(sprite.GetSize());
    this->DrawSprite(sprite, Vector2(0, 0));
    return(*this);
}

void Sprite::ReplaceCharacter(const char oldchar, const char newchar)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            if(this->data[x][y].character == oldchar)
                this->data[x][y].character = newchar;
        }
    }
}

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
    Sprite bkp(*this);

    this->DeallocData();
    this->AllocData(newsize);
    this->DrawSprite(bkp, Vector2(0, 0));
    return(true);
}

void Sprite::Clear()
{
    this->Clear(Color::Black);
}

void Sprite::Clear(color backcolor)
{
    this->Clear(backcolor, ' ');
}

void Sprite::Clear(color backcolor, char character)
{
    this->Clear(backcolor, Color::Gray, character);
}

void Sprite::Clear(color backcolor, color forecolor, char character)
{
    for(register uint16_t x = 0; x < this->size.x; ++x)
    {
        for(register uint16_t y = 0; y < this->size.y; ++y)
        {
            this->data[x][y].character = character;
            this->data[x][y].forecolor = forecolor;
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
    //Todo: Esta funcao deve fazer a rotacao do sprite
}

void Sprite::Save(const string &filename)
{
    FILE* out = std::fopen(filename.c_str(), "wb");

    std::fwrite((void*)&this->size.x, 2, 1, out);
    std::fwrite((void*)&this->size.y, 2, 1, out);

    if(out == NULL)
    {
        throw("Can't save file");
    }

    for(register uint16_t x = 0; x < size.x; ++x)
    {
        for(register uint16_t y = 0; y < size.y; ++y)
        {
            std::fwrite((void*)&this->data[x][y].character, 1, 1, out);
            std::fwrite((void*)&this->data[x][y].forecolor, 1, 1, out);
            std::fwrite((void*)&this->data[x][y].backcolor, 1, 1, out);
        }
    }

    std::fclose(out);
}
