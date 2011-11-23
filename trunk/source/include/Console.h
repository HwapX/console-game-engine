#ifndef CGE_CONSOLE_H
#define CGE_CONSOLE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

/*Necessario para VK_OEM_PLUS e VK_OEM_MINUS*/
#ifndef WINVER
    #define WINVER 0x0501
#endif

#include <windows.h>

using namespace std;

#include "Misc.h"
#include "Sprite.h"
#include "Animation.h"
#include "Input.h"
#include "Sound.h"

#define OLDLOGO

#define VERSION "Version beta 0.7"

namespace ConsoleGameEngine
{

/**
*the main class
*/
class Console : public Sprite
{
private:
    HANDLE output_handle;
    HWND handle;

    void PreInit();
    void PosInit();

    uint16_t currentfps;
    uint16_t fps;
    uint32_t fpstick;

    Vector2 position;

public:

    Console();
    Console(const string &title);
    Console(const Vector2 &size);
    Console(const Vector2 &position, const Vector2 &size);
    Console(const string &title,const Vector2 &size);
    Console(const string &title, const Vector2 &position, const Vector2 &size);

    void ShowLogo();
    void ShowError(const string &text, const bool close);
    bool ShowDialog(const string &title, const string &text, string &result);

    static uint32_t GetTick();
    bool Focus();
    void WaitFocus();
    uint16_t GetCurrentFps();
    Vector2 ScreenResolution();

    bool Resize(Vector2 size);

    bool SetPosition(Vector2 position);
    bool SetTitle(const string &title);
    bool SetCursorPosition(Vector2 position);
    bool SetTextColor (color forecolor, color backcolor);
    bool SetCursorSize(uint8_t size, bool visible);

    void Update();
    //set font
    //get font
};

}

#endif // CGE_CONSOLE_H
