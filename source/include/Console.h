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
#include "Utils.h"

#define VERSION "Rev 41"//"Version beta 0.8"

#define TEXT_CURSOR "\x16"

#define DEFAULT_SIZE_Y 40
#define DEFAULT_SIZE_X 80

namespace ConsoleGameEngine
{

/**
*the main class
*/
class Console : public Sprite, public Input
{
private:
    HANDLE out_handle;
    HWND handle;

    void PreInit();
    void PosInit();

    uint8_t lock_fps;
    uint16_t current_fps;
    uint16_t fps;
    uint32_t fps_time;
    uint32_t start_time;
    uint32_t delta_time;//uint16_t
    uint32_t last_time;
    int32_t sleep_time;//int16_t

    Vector2 position;

    static void ExceptionHandler();
public:

    Console();
    Console(const string &title);
    Console(const Vector2 &size);
    Console(const Vector2 &position, const Vector2 &size);
    Console(const string &title,const Vector2 &size);
    Console(const string &title, const Vector2 &position, const Vector2 &size);

    void ShowLogo();
    static void ShowError(const string &text, const bool close = true);
    bool InputDialog(const string &title, const string &text, string &result, uint8_t number_base = 0);
    bool InputDialog(const string title, const string text, int32_t &result);
    bool MsgDialog(const string &title, const string &text, const bool only_ok = true, const bool option = true);
    void ShowDebugInfo();

    bool Focus();
    void WaitFocus();

    static uint32_t GetTick();
    uint32_t GetDeltaTime();//uint16_t
    uint32_t GetLifeTime();
    uint16_t GetCurrentFps();
    void LockFps(uint8_t limit);
    uint32_t GetRandom(int seed = 0);

    bool Resize(Vector2 size);

    Vector2 WindowPosition();
    Vector2 WindowSize();
    Vector2 ScreenResolution();

    bool SetPosition(Vector2 position);
    bool SetTitle(const string &title);
    bool SetCursorPosition(Vector2 position);
    bool SetTextColor (color forecolor, color backcolor);
    bool SetCursorSize(uint8_t size, bool visible);

    void Update();
};

}

#endif // CGE_CONSOLE_H
