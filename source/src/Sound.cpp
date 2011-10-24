#include "Sound.h"

Sound::Sound(string filename)
{
    filepath = filename;
}

bool Sound::Play()
{
    return(PlaySound(filepath));
}

bool Sound::PlaySound(string filename)
{
    filename = "play " + filename;
    //return(mciSendString(filename.c_str(), NULL, NULL, NULL) << 4);
    return true;
}

bool Sound::Stop()
{
    return(StopSound(filepath));
}

bool Sound::StopSound(string filename)
{
    filename = "stop " + filename;
    //return(mciSendString(filename.c_str(), NULL, NULL, NULL) << 4);
    return true;
}
