#include "Animation.h"


void Animation::CreateAnimation(Sprite &tileset, const Vector2 &tilesize, const uint8_t start, const uint8_t count, const uint16_t interval)
{
    this->frame_count = count;
    this->frames = new Sprite*[count];
    this->current_frame = 0;
    this->frame_interval = interval;
    this->lasttick = 0;
    this->paused = true;
    this->repeat = false;

    for(register uint8_t b = 0; b < count; ++b)
    {
        this->frames[b] = new Sprite(tileset, tilesize, start + b);
    }
}

Animation::Animation(Sprite &tileset, const Vector2 &tilesize, const uint8_t start, const uint8_t count, const uint16_t interval)
{
    CreateAnimation(tileset, tilesize, start, count, interval);
}

Animation::Animation(const string &filename, const Vector2 &tilesize, const uint8_t start, const uint8_t count, const uint16_t interval)
{
    Sprite tileset(filename);
    CreateAnimation(tileset, tilesize, start, count, interval);
}

Animation::~Animation()
{
    for(register uint8_t b = 0; b < this->frame_count; ++b)
    {
        delete this->frames[b];
    }

    delete [] this->frames;
}

Sprite &Animation::CurrentFrame()
{
    if(((Console::GetTick() - this->lasttick) > this->frame_interval) && !this->paused)
    {
        this->lasttick = Console::GetTick();
        if(this->current_frame < this->frame_count-1) {
            ++this->current_frame;
        } else if (this->repeat) {
            this->current_frame = 0;
        }
    }
    return(*this->frames[this->current_frame]);
}

void Animation::Play() {
    this->paused = false;
}

void Animation::Pause() {
    this->paused = true;
}

uint8_t Animation::GetFrame() {
    return(this->current_frame);
}

bool Animation::SetFrame(uint8_t frame) {
    if(frame < frame_count) {
        this->current_frame = frame;
        return(true);
    } else {
        return(false);
    }
}

void Animation::SetRepeat(bool value) {
    this->repeat = value;
}
