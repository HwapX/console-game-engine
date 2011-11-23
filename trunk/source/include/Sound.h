#ifndef CGE_SOUND_H
#define CGE_SOUND_H

#include <iostream>
#include <cstdio>
#include <windows.h>
#include "Misc.h"

using namespace std;

DWORD WINAPI PlayAsync(LPVOID sound);

namespace ConsoleGameEngine
{

/**
*
*/
class Sound
{
private:
    uint32_t duration;
    uint16_t size;
    Note *notes;
    HANDLE thread_handle;

public:
    void Init();
    Sound(string const &filename);
    Sound(uint16_t const &size);
    ~Sound();
    bool Play(bool sync = false);
    bool Stop();
    bool ReplaceNote(uint16_t const &index,Note const &note);
    uint16_t Copy(Sound &sound,uint16_t const &start, uint16_t  &size);
    uint16_t GetSize();
    bool Save(string const &filename);
    Note GetNote(uint16_t const &index);
    bool IsPlaying();
    uint32_t GetDuration();

    static bool PlayBeep(Note const &note);
};

}

#endif // CGE_SOUND_H
