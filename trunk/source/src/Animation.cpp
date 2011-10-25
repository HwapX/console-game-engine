#include "Animation.h"

Animation::Animation(const string &filename, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval)
{
    frame_count = count;
    frames = new Sprite*[count];
    current_frame = 0;
    frame_interval = interval;
    lasttick = 0;

    for(register byte b = 0; b < count; ++b)
    {
        frames[b] = new Sprite(filename, tilesize, start + b);
    }

}

Animation::~Animation()
{
    for(register byte b = 0; b < frame_count; ++b)
    {
        delete frames[b];
    }

    delete [] frames;
}

Sprite &Animation::CurrentFrame()
{
    if((Engine::GetTick() - lasttick) > frame_interval)
    {
        lasttick = Engine::GetTick();
        ++current_frame;
        if(current_frame == frame_count)
            current_frame = 0;
    }
    return(*frames[current_frame]);
}
