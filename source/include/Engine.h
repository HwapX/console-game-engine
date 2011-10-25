#ifndef CGE_ENGINE_H
#define CGE_ENGINE_H

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

#define NEWLOGO

#define VERSION "Version beta 0.7"

namespace ConsoleGameEngine
{

/**
*the main class
*/
class Engine
{
private:
    HANDLE output_handle;
    HWND console_handle;

    void PreInit();
    void PosInit();

    short int currentfps;

    Vector2 console_size;
    Vector2 console_position;

public:
    /**
    *pointer to buffer
    */
    Sprite *buffer;
    /**
    *default constructor
    *initialize engine with default settings
    */
    Engine();
    /**
    *initialize engine and set console title to informed.
    *@param title console title
    */
    Engine(const string &title);
    /**
    *initilize engine with given parameters
    *@param size console window size in pixel(console cells)
    */
    Engine(const Vector2 &size);
    /**
    *initilize engine with given parameters
    *@param position console window position
    *@param size console window size in pixel(console cells)
    */
    Engine(const Vector2 &position, const Vector2 &size);
    /**
    *initilize engine with given parameters
    *@param title console title
    *@param size console window size in pixel(console cells)
    */
    Engine(const string &title,const Vector2 &size);
    /**
    *initilize engine with given parameters
    *@param title console title
    *@param position console window position
    *@param size console window size in pixel(console cells)
    */
    Engine(const string &title, const Vector2 &position, const Vector2 &size);
    /**
    *destructor
    */
    ~Engine();
    /**
    *draw engine splash
    */
    void ShowLogo();
    /**
    *Show a Error Message
    */
    void ShowError(const string &text, const bool close);



    static int GetTick();
    /**
    *check if window has focus
    *@return return true if window is in focus or false otherwise
    */
    bool Focus();
    /**
    *wait window focus
    *this function returns only when the window is in focus
    */
    void WaitFocus();
    /**
    *set console window size.
    *@param size new size.
    *@return return true if success or false otherwise
    */
    bool SetWindowSize(Vector2 size);
    /**
    *set console window position
    *@param position new position
    *@return return true if success or false otherwise
    */
    bool SetWindowPosition(Vector2 position);
    /**
    *get console window size
    *@return window size
    */
    Vector2 GetWindowSize();
    /**
    *get primary monitor resolution
    *@return return screen resolution
    */
    Vector2 GetScreenResolution();
    /**
    *set console window title
    *@param title new title
    *@return return true if success or false otherwise
    */
    bool SetWindowTitle(const string &title);
    /**
    *set console cursor position
    *@param position new position
    *@return return true if success or false otherwise
    */
    bool SetCursorPosition(Vector2 position);
    /**
    *set next write forecolor and backcolor in console
    *@param forecolor foreground color
    *@param backcolor background color
    *@return return true if success or false otherwise
    */
    bool SetTextColor (color forecolor, color backcolor);
    /**
    *set cursor size and visible state
    *@param size new cursor size
    *@param visible visible state
    *@return return true if success or false otherwise
    */
    bool SetCursorSize(byte size, bool visible);
    /**
    *copy buffer to console
    */
    void UpdateConsole();
    /**
    *get current frame rate per second
    */
    short int GetCurrentFps();
    //set font
    //get console size
    //get console position
    //get font
};

}

#endif // CGE_ENGINE_H
