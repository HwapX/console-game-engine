#include "Sprite.h"

using namespace ConsoleGameEngine;

Sprite::Sprite(const string &filename)
{
    byte temp = 0;
    Vector2 temp_size;
    std::FILE* in = fopen(filename.c_str(), "r");

    if(in == NULL)
        std::fprintf(stderr, "Can't Open sprite file");

    std::fread((void*)&temp_size.x, 2, 1, in);
    std::fread((void*)&temp_size.y, 2, 1, in);

    if(!AllocData(temp_size))
    {
        return;
    }

    for(register uint16_t x = 0; x < temp_size.x; ++x)
    {
        for(register uint16_t y = 0; y < temp_size.y; ++y)
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

    cx = tileset.GetSize().x / tilesize.x;
    cy = tileset.GetSize().y / tilesize.y;
    px = index > cx?index % cx:index;
    py = index > cx?index / cx:0;

    if(!AllocData(tilesize))
    {
        return;
    }
    Clear(Colors::Transparent);
    DrawSprite(tileset, Vector2(0, 0), Rect(Vector2((px -1) * tilesize.x, py * tilesize.y), tilesize));

}

Sprite::Sprite(const Vector2 &sprite_size)
{
    AllocData(sprite_size);
}

//informar o tamanho da imagem
bool Sprite::AllocData(const Vector2 &data_size)
{
    data = new Pixel*[data_size.x];
    if(this->data == NULL)
    {
        std::fprintf(stderr, "Can't allocate memory");
        return(false);
    }
    for(register uint16_t i = 0; i < data_size.x; ++i)
    {
        this->data[i] = new Pixel[data_size.y];
        if(this->data[i] == NULL)
        {
            std::fprintf(stderr, "Can't allocate memory");
            DeallocData(i);
            return(false);
        }
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

byte Sprite::DrawText(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    byte len = text.size();
    register byte b;

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

byte Sprite::DrawTextRight(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(this->DrawText(text, Vector2((position.x - (text.size() -1)), position.y), forecolor, backcolor));
}

byte Sprite::DrawTextCenter(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    return(this->DrawText(text, Vector2(position.x - ((text.size() -1) / 2), position.y), forecolor, backcolor));
}

byte Sprite::DrawTextVert(const string &text, const Vector2 &position, const color forecolor, const color backcolor)
{
    byte len = text.size();
    register byte b;

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

byte Sprite::DrawTextVertCenter(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (this->DrawTextVert(text, Vector2(position.x, (position.y / (text.size() -1))), forecolor, backcolor));
}

byte Sprite::DrawTextVertTop(const string &text, const Vector2 &position, color forecolor, color backcolor)
{
    return (this->DrawTextVert(text, Vector2(position.x, (position.y - (text.size() -1))), forecolor, backcolor));
}

void Sprite::Clear()
{
    this->Clear(Colors::Black);
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

Pixel *Sprite::GetPixel(const Vector2 &coord)
{
    if((coord.x < this->size.x && coord.y < this->size.y) && !(coord.x < 0 && coord.y < 0))
    {
        return(&this->data[coord.x][coord.y]);
    }

    return(NULL);
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
    Sprite bkp(this->size);

    bkp.DrawSprite(*this, Vector2(0, 0));
    this->DeallocData(this->size.x);
    if(!this->AllocData(newsize))
    {
        return (false);
    }
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
    //Todo: Esta função deve fazer a rotação do sprite
}

void Sprite::Save(const string &filename)
{
    byte temp = 0;
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

            temp = (byte)this->data[x][y].forecolor;
            std::fwrite((void*)&temp, 1, 1, out);

            temp = (byte)this->data[x][y].backcolor;
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
