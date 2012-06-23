#include "Input.h"

using namespace ConsoleGameEngine;
/*
bool Keyboard::GetKey(char key_code)
{
    if(key_code >= '0' && key_code <= '9')
    {
        key_code-= '0';
        return((GetAsyncKeyState(key_code + '0') == -32767) || (GetAsyncKeyState(key_code + 0x60) == -32767));
    }
    else if(key_code >= '*' && key_code <= '/')
    {
        key_code-= '+';
        return((GetAsyncKeyState(key_code + 0x6B) == -32767) || (GetAsyncKeyState(key_code + 0xBB) == -32767));
    }

    switch(key_code)
    {
    case '\n':
        key_code = VK_RETURN;
        break;
    case '\b':
        key_code = VK_BACK;
        break;
    case ',':
        key_code = 0xBE;
        break;
    case '.':
        key_code = 0xBC;
        break;
    }
    return(GetAsyncKeyState(key_code) == -32767);
}

bool Keyboard::GetKeyDown(const char key_code)
{
    return((GetAsyncKeyState(key_code) == -32768));
}

char Keyboard::GetKey()
{
    for(uint8_t b = 1; b < 256; b++)
    {
        if(GetKey(b))
        {
            return(b);

        }
    }
    return(0);
}

void Keyboard::WaitKey(char key_code)
{
    while(!GetKey(key_code)){};
}

char Keyboard::GetNextKey()
{
    char key_code = 0;
    do
    {
        key_code = GetKey();
    }
    while(!key_code);
    return(key_code);
}
*/

/*-------------------------*/
/*---------Keyboard--------*/
/*-------------------------*/

Keyboard::Keyboard()
{
    for(uint16_t i = 0; i < 257; ++i)
    {
        keyboard_state[i] = 0;
    }
}

void Keyboard::KeyEventProc(const KeyInfo keys[], const uint8_t key_state[])
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        key_buffer[i] = keys[i];
    }

    for(uint16_t i = 0; i < 257; ++i)
    {
        keyboard_state[i] = key_state[i];
    }
}

KeyInfo Keyboard::GetKeyInfo()
{
    KeyInfo result;
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())
        {
            if(key_buffer[i].down)
            {
                result = key_buffer[i];
                return(result);
            }
        }
    }
    return(result);
}

uint8_t Keyboard::GetKey()
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())
        {
            if(key_buffer[i].down)
            {
                return(key_buffer[i].code);
            }
        }
    }

    return(0);
}

char Keyboard::GetChar()
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())
        {
            if(key_buffer[i].down)
            {
                return(key_buffer[i].character);
            }
        }
    }
    return(0);
}

bool Keyboard::GetKeyUp(const keycode key_code)
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())//.code
        {
            if(key_code == key_buffer[i].code)
            {
                if(!key_buffer[i].down)
                {
                    key_buffer[i].Invalidate();
                    return(true);
                }
            }
        }
    }
    return(false);
}

bool Keyboard::GetKey(const keycode key_code)
{
    //GetKeySate
    //GetKeyStateAsync
    //if(GeyKeyState)

    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())//.code
        {
            if(key_code == key_buffer[i].code && key_buffer[i].down)
            {
                return(true);
            }
        }
    }
    return(false);
}


bool Keyboard::GetChar(const char character)
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        if(key_buffer[i].IsValid())//.code
        {
            if((character == key_buffer[i].character) && key_buffer[i].down)
            {
                return(true);
            }
        }
    }
    return(false);
}

void Keyboard::ClearKeyBuffer()
{
    for(uint8_t i = 0; i < KEY_BUFFER; ++i)
    {
        key_buffer[i].Invalidate();
    }
}

bool Keyboard::IsPrintable(const char character)
{
    return(true);
}

bool Keyboard::GetCapsLock()
{
    return(GetKeyState(0x90) | 1);
    //return(control_keys & Key::CapsLock_On);
}

bool Keyboard::GetNumLock()
{
    return(GetKeyState(0x14) | 1);
    //return(control_keys & Key::NumLock_On);
}

bool Keyboard::GetScrollLock()
{
    return(GetKeyState(0x91) & 1);
    //return(control_keys & Key::ScrollLock_On);
}

/*-------------------------*/
/*----------Mouse----------*/
/*-------------------------*/

void Mouse::MouseEventProc(MouseInfo info)
{
    mouse_info = info;
}

uint8_t Mouse::RightButton()
{
    return(mouse_info.right);
}

uint8_t Mouse::LeftButton()
{
    return(mouse_info.left);
}

int8_t Mouse::Wheel()
{
    return(mouse_info.wheel);
}

int8_t Mouse::HWheel()
{
    return(mouse_info.hwheel);
}

bool Mouse::IsMoving()
{
    return(mouse_info.moving);
}

Vector2 Mouse::GetPosition()
{
    return(mouse_info.position);
}

uint8_t Mouse::GetButton()
{
    uint8_t result = 0;
    if(this->LeftButton())
    {
        result = result | MouseLeft;
    }
    else if(this->RightButton())
    {
        result = result | MouseRight;
    }
    else if(this->Wheel())
    {
        result = result | MouseWheel;
    }
    else if(this->HWheel())
    {
        result = result | MouseHWheel;
    }
    return(result);
    //return(this->LeftButton() | this->RightButton() | this->Wheel() | this->HWheel());
}

/*-------------------------*/
/*----------Input----------*/
/*-------------------------*/

Input::Input()
{
    in_handle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(in_handle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void Input::WaitKey(const keycode key)
{
    while(!this->GetKey(key))
    {
        this->ProcessEvents();
    };
}

keycode Input::WaitKey()
{
    keycode key = 0;
    do
    {
        this->ProcessEvents();
        key = this->GetKey();
    }
    while(key == 0);
    return(key);
}

void Input::WaitChar(const char character)
{
    while(!this->GetChar(character))
    {
        this->ProcessEvents();
    };
}

char Input::WaitChar()
{
    char character = 0;
    do
    {
        this->ProcessEvents();
        character = this->GetChar();
    }
    while(character == 0);
    return(character);
}

void Input::ProcessEvents()
{
    uint32_t total = 0;
    KeyInfo keys[KEY_BUFFER];
    MouseInfo mouse_info;
    uint8_t key_state[256];

    GetNumberOfConsoleInputEvents(in_handle, (DWORD*)&total);
    if(total > 0)
    {
        INPUT_RECORD events[total];
        uint32_t events_read = 0;
        if(ReadConsoleInput(in_handle, (struct _INPUT_RECORD*)&events, total, (DWORD*)&events_read))
        {
            uint8_t key_count = 0;
            for(int16_t i = (events_read -1); i >= 0; --i)
            {
                switch(events[i].EventType)
                {
                case KEY_EVENT:
                    if(key_count < KEY_BUFFER)
                    {
                        bool flag = true;
                        for(uint8_t e = 0; e < key_count; ++e)
                        {
                            if(keys[e].code == events[i].Event.KeyEvent.wVirtualKeyCode && keys[e].down == events[i].Event.KeyEvent.bKeyDown)
                            {
                                flag = false;
                            }
                        }
                        if(flag == true)
                        {
                            keys[key_count].down = events[i].Event.KeyEvent.bKeyDown;
                            keys[key_count].code = events[i].Event.KeyEvent.wVirtualKeyCode;
                            keys[key_count].character = events[i].Event.KeyEvent.uChar.AsciiChar;
                            ++key_count;
                        }
                    }
                    break;
                case MOUSE_EVENT:
                    switch(events[i].Event.MouseEvent.dwEventFlags)
                    {
                    case 0:
                        switch(events[i].Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            mouse_info.left = Mouse::ButtonClick;
                            break;
                        case RIGHTMOST_BUTTON_PRESSED:
                            mouse_info.right = Mouse::ButtonClick;
                            break;
                        case FROM_LEFT_2ND_BUTTON_PRESSED:
                            mouse_info.middle = Mouse::ButtonClick;
                            break;
                            //case 0:
                            //any button up
                        }
                        break;
                    case DOUBLE_CLICK:
                        switch(events[i].Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            mouse_info.left = Mouse::ButtonDoubleClick;
                            break;
                        case RIGHTMOST_BUTTON_PRESSED:
                            mouse_info.right = Mouse::ButtonDoubleClick;
                            break;
                        case FROM_LEFT_2ND_BUTTON_PRESSED:
                            mouse_info.middle = Mouse::ButtonDoubleClick;
                            break;
                            //case 0:
                            //?
                        }
                        break;
                    case MOUSE_MOVED:
                        mouse_info.moving = true;
                        switch(events[i].Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            mouse_info.left = Mouse::ButtonPressed;
                            break;
                        case RIGHTMOST_BUTTON_PRESSED:
                            mouse_info.right = Mouse::ButtonPressed;
                            break;
                        case FROM_LEFT_2ND_BUTTON_PRESSED:
                            mouse_info.middle = Mouse::ButtonPressed;
                            break;
                            //case 0:
                            //???????????????
                        }
                        break;
                    case MOUSE_WHEELED:
                        mouse_info.wheel = 3;//terminar
                        break;
                    case 0x0008://MOUSE_HWHEELED:
                        mouse_info.hwheel = 3;//terminar
                        break;
//                    default:
//                        break;
                    }
                    mouse_info.position.x = events[i].Event.MouseEvent.dwMousePosition.X;
                    mouse_info.position.y = events[i].Event.MouseEvent.dwMousePosition.Y;
                    this->MouseEventProc(mouse_info);
                    break;
                }
            }
        }
    }

    for(uint16_t i = 0; i < 256; ++i)
    {
        key_state[i] = 0;
    }

    GetKeyboardState(key_state);


    this->KeyEventProc(keys, key_state);
}
