#ifndef CGE_SOUND_H
#define CGE_SOUND_H

#include <iostream>

using namespace std;

namespace ConsoleGameEngine
{

/**
*nothing
*/
class Sound
{
private:
    string filepath;
public:
    Sound(string filename);
    bool Play();
    bool Stop();
    static bool PlaySound(string filename);
    static bool StopSound(string filename);
};

}

#endif // CGE_SOUND_H
