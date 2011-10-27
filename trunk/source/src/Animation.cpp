#include "Animation.h"


void Animation::CreateAnimation(Sprite &tileset, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval)
{
    this->frame_count = count;
    this->frames = new Sprite*[count];
    this->current_frame = 0;
    this->frame_interval = interval;
    this->lasttick = 0;

    for(register byte b = 0; b < count; ++b)
    {
        this->frames[b] = new Sprite(tileset, tilesize, start + b);
    }
}

Animation::Animation(Sprite &tileset, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval)
{
    CreateAnimation(tileset, tilesize, start, count, interval);
}

Animation::Animation(const string &filename, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval)
{
    Sprite tileset(filename);
    CreateAnimation(tileset, tilesize, start, count, interval);
}

Animation::~Animation()
{
    for(register byte b = 0; b < this->frame_count; ++b)
    {
        delete this->frames[b];
    }

    delete [] this->frames;
}

Sprite &Animation::CurrentFrame()
{
    if((Engine::GetTick() - this->lasttick) > this->frame_interval)
    {
        this->lasttick = Engine::GetTick();
        ++this->current_frame;
        if(this->current_frame == this->frame_count)
            this->current_frame = 0;
    }
    return(*this->frames[this->current_frame]);
}
