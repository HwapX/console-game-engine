#include "Sound.h"
#include <Windows.h>

using namespace ConsoleGameEngine;

void Sound::Init()
{
    this->thread_handle = 0;
    this->notes = NULL;
    this->size = 0;
    this->duration = 0;
    this->current = 0;
    this->paused = false;
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
    fclose(file);
}

Sound::Sound(uint16_t const &size)
{
    this->Init();
    this->notes = new Note[size];
    this->size = size;
}

Sound::~Sound()
{
    this->Stop();
    delete [] notes;
}

DWORD WINAPI PlayAsync(LPVOID sound)
{
    ((Sound*)sound)->Play(true);
    //Sound* sound =
    return(0);
}

bool Sound::Play(bool sync)
{
    if(thread_handle && !sync)
    {
        if(paused)
        {
            if(ResumeThread(thread_handle) != -1)
            {
                paused = false;
                return(true);
            }
            else
            {
                return(true);
            }
        }
        else
        {
            return(false);
        }
    }
    else
    {
        if(sync)
        {
            //TODO: Esta função não é thread safe ainda
            for(uint16_t i = 0; i < this->size; ++i)
            {
                current = i;
                this->PlayBeep(notes[i]);
            }
            thread_handle = NULL;
            current = 0;
            return(true);
        }
        else
        {
            thread_handle = CreateThread(NULL, 0, PlayAsync, (void*)this, 0, NULL);
            return(thread_handle);
        }
    }
}

bool Sound::IsPlaying()
{
    return(thread_handle);
}

bool Sound::Pause()
{
    if(thread_handle && !paused)
    {
        if(SuspendThread(thread_handle) != -1)
        {
            paused = true;
            return(true);
        }
        else
        {
            return(false);
        }
    }
    return(false);
}

bool Sound::Paused()
{
    return(paused);
}

bool Sound::Stop()
{
    if(thread_handle != 0)
    {
        bool result = TerminateThread(thread_handle, 0);
        thread_handle = NULL;
        paused = false;
        current = 0;
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

uint16_t Sound::GetCurrent()
{
    return(current);
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

uint16_t Sound::GetSize()
{
    return(this->size);
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

bool Sound::Save(string const &filename)
{
    std::FILE* file = fopen(filename.c_str(), "wb");

    if(file == NULL)
    {
        return(false);
    }

    for(uint16_t i = 0;i < this->size; ++i)
    {
        fwrite((void*)&notes[i].frequence, 2, 1, file);
        fwrite((void*)&notes[i].duration, 2, 1, file);
    }
    fclose(file);

    return(true);
}

bool Sound::PlayBeep(Note const &note)
{
    return(Beep(note.frequence, note.duration));
}
