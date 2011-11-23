#include "Sound.h"
#include <Windows.h>

using namespace ConsoleGameEngine;

void Sound::Init()
{
    this->thread_handle = 0;
    this->notes = NULL;
    this->size = 0;
    this->duration = 0;
}

Sound::Sound(string const &filename)
{
    this->Init();
    std::FILE* file = std::fopen(filename.c_str(), "rb");

    std::fseek(file, 0, SEEK_END);
    this->size = (std::ftell(file) / 4);//4 = size of note data
    std::fseek(file, 0, SEEK_SET);

    this->notes = new Note[this->size];

    for(uint16_t i = 0; i < this->size; ++i)
    {
        std::fread(&notes[i].frequence, 2, 1, file);
        std::fread(&notes[i].duration, 2, 1, file);
        this->duration+=notes[i].duration;
    }
}

Sound::Sound(uint16_t const &size)
{
    this->Init();
    this->notes = new Note[size];
    this->size = size;
}

Sound::~Sound()
{

}

DWORD WINAPI PlayAsync(LPVOID sound)
{
    ((Sound*)sound)->Play(true);
    //Sound* sound =
    return(0);
}

bool Sound::Play(bool sync)
{
    if(sync)
    {
        //TODO: Esta função não é thread safe ainda
        for(uint16_t i = 0; i < this->size; ++i)
        {
            this->PlayBeep(notes[i]);
        }
        thread_handle = NULL;
        return(true);
    }
    else
    {
        thread_handle = CreateThread(NULL, 0, PlayAsync, (void*)this, 0, NULL);
        return(thread_handle);
    }
}

bool Sound::IsPlaying()
{
    return(thread_handle);
}

bool Sound::Stop()
{
    if(thread_handle != 0)
    {
        bool result = TerminateThread(thread_handle, 0);
        thread_handle = NULL;
        return(result);
    }
    else
    {
        return(false);
    }
}

bool Sound::ReplaceNote(uint16_t const &index, Note const &note)
{
    if(index >= 0 && index < size)
    {
        this->duration-=notes[index].duration;
        this->duration+=note.duration;
        notes[index] = note;
        return(true);
    }

    return(false);
}

Note Sound::GetNote(uint16_t const &index)
{
    if(index >= 0 && index < size)
    {
        return(notes[index]);
    }
    return(Note(0, 0));
}

uint32_t Sound::GetDuration()
{
    return(this->duration);
}

uint16_t Sound::Copy(Sound &sound,uint16_t const &start, uint16_t  &size)
{
    if(size > this->size)
        size = this->size;

    for(uint16_t i = start; i < size; ++i)
    {
        notes[i - start] = sound.GetNote(i);
    }
    return(size);
}

bool Sound::PlayBeep(Note const &note)
{
    return(Beep(note.frequence, note.duration));
}
