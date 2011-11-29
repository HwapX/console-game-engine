#ifndef CGE_INPUT_H
#define CGE_INPUT_H

#include <windows.h>
#include <iostream>
#include <cassert>

using namespace std;

#include "Misc.h"

namespace ConsoleGameEngine
{

#define KEY_BUFFER 10

class Keyboard
{
private:
    KeyInfo key_buffer[KEY_BUFFER];
    uint8_t keyboard_state[256];

protected:
    void KeyEventProc(const KeyInfo key[], const uint8_t key_state[]);

public:
    /*
    static bool GetKey(char key);
    static bool GetKeyDown(const char key);
    //revisar as funções abaixo da classe
    static char GetKey();
    static char GetNextKey();
    static void WaitKey(char key);
    */
    //static char TranslateKey(const char key);
    //void WaitKey(char key);
    //char GetNextKey();
    //char GetChar();

    Keyboard();

    keycode GetKey();
    bool GetKey(const keycode key);
    bool GetKeyUp(const keycode key);
    virtual void WaitKey(const keycode key) = 0;
    virtual keycode WaitKey() = 0;

    char GetChar();
    bool GetChar(const char character);
    virtual void WaitChar(const char character) = 0;
    virtual char WaitChar() = 0;

    KeyInfo GetKeyInfo();

    //uint8_t GetControlKeys();
    bool GetCapsLock();
    bool GetNumLock();
    bool GetScrollLock();

    bool IsPrintable(const char character);

    void ClearKeyBuffer();
};

class Mouse
{
private:
    MouseInfo mouse_info;
protected:
    virtual void MouseEventProc(MouseInfo mouse);
public:
    static const uint8_t MouseLeft = 2;
    static const uint8_t MouseRight = 4;
    static const uint8_t MouseWheel = 8;
    static const uint8_t MouseHWheel = 16;

    static const uint8_t ButtonPressed = 1;
    static const uint8_t ButtonClick = 2;
    static const uint8_t ButtonDoubleClick = 3;

    Vector2 GetPosition();
    uint8_t GetButton();
    uint8_t RightButton();
    uint8_t LeftButton();
    uint8_t GetMiddle();
    int8_t Wheel();
    int8_t HWheel();
    bool IsMoving();
};

typedef void*(*KeyProc)(KeyInfo *);
typedef void*(*MouseProc)(Mouse *);

class Input : public Keyboard, public Mouse
{
private:
protected:
    HANDLE in_handle;
    KeyProc key_proc;
    MouseProc mouse_proc;

    void ProcessEvents();
public:
    Input();

    void WaitKey(const keycode key);
    keycode WaitKey();
    void WaitChar(const char character);
    char WaitChar();

    uint8_t GetNumber();
    uint8_t GetCharNumber();

    void RegisterMouseProc(const MouseProc proc);
    void RegisterKeyProc(const KeyProc proc);
};

}

#endif // CGE_INPUT_H
