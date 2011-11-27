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

//typedef uint8_t key;

class Keyboard
{
private:
    KeyInfo key_buffer[KEY_BUFFER];

protected:
    void KeyEventProc(const KeyInfo key[]);

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
    virtual uint8_t RightButton();
    virtual uint8_t LeftButton();
    virtual int8_t Whell();
    virtual int8_t HWhell();
    virtual bool IsMoving();
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
