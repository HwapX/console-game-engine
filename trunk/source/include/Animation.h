#ifndef CGE_ANIMATION_H
#define CGE_ANIMATION_H

#include "Misc.h"
#include "Sprite.h"
#include "Engine.h"

using namespace ConsoleGameEngine;

namespace ConsoleGameEngine
{

class Animation
{
public:
    Animation(Sprite &sprite, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval);
    Animation(const string &filename, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval);
    virtual ~Animation();
    virtual Sprite &CurrentFrame();
protected:
    Sprite **frames;
    byte frame_count;
    byte current_frame;
    uint16_t frame_interval;
    int lasttick;
private:
    void CreateAnimation(Sprite &tileset, const Vector2 &tilesize, const byte start, const byte count, const uint16_t interval);
};

}

#endif // CGE_ANIMATION_H
