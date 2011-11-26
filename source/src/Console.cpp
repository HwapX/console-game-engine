#include "Console.h"

using namespace ConsoleGameEngine;

void Console::PreInit()
{
    current_fps = 0;
    fps = 0;
    fps_time = 0;
    lock_fps = 0;
    sleep_time = 0;
    start_time = GetTick();
    delta_time = 0;
    std::set_terminate(ExceptionHandler);
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    handle = GetConsoleWindow();
    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    SetCursorSize(1, false);
    SetTitle("Console Game Engine");
}

void Console::PosInit()
{
    Resize(size);
    ShowLogo();
}

Console::Console() : Sprite::Sprite(Vector2(80, 25))
{
    PreInit();
    PosInit();
}

Console::Console(const string &title) : Sprite::Sprite(Vector2(80, 25))
{
    PreInit();

    SetTitle(title);

    PosInit();
}

Console::Console(const Vector2 &position, const Vector2 &size) : Sprite::Sprite(size)
{
    PreInit();

    SetPosition(position);

    PosInit();
}

Console::Console(const Vector2 &size) : Sprite::Sprite(size)
{
    PreInit();

    PosInit();
}

Console::Console(const string &title, const Vector2 &size) : Sprite::Sprite(size)
{
    PreInit();

    SetTitle(title);

    PosInit();
}

Console::Console(const string &title, const Vector2 &position, const Vector2 &size) : Sprite::Sprite(size)
{
    PreInit();

    SetTitle(title);
    SetPosition(position);

    PosInit();
}

void Console::ShowLogo()
{
#ifndef OLDLOGO

    #define BORDER_CHAR 0xB0

    uint8_t colc = 0, colg = 0, effect = 0;
    Sprite logo(Vector2(this->GetSize().x, 14)), blood(Vector2(this->GetSize().x - 2, this->GetSize().y- 2));
    uint32_t lasttick = GetTick(), blinktick = GetTick();
    bool blink = false;

    std::srand(GetTick());

    logo.DrawTextCenter("  ______                       _       ",     Vector2(logo.GetSize().x / 2, 0), Color::Blue, Color::White);
    logo.DrawTextCenter(" / _____)                     | |      ",     Vector2(logo.GetSize().x / 2, 1), Color::Blue, Color::White);
    logo.DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(logo.GetSize().x / 2, 2), Color::Blue, Color::White);
    logo.DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(logo.GetSize().x / 2, 3), Color::Blue, Color::White);
    logo.DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(logo.GetSize().x / 2, 4), Color::Blue, Color::White);
    logo.DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(logo.GetSize().x / 2, 5), Color::Blue, Color::White);

    logo.DrawTextCenter("  ______                      _______             _             ",        Vector2(logo.GetSize().x / 2, 7), Color::Green, Color::White);
    logo.DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(logo.GetSize().x / 2, 8), Color::Green, Color::White);
    logo.DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(logo.GetSize().x / 2, 9), Color::Green, Color::White);
    logo.DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(logo.GetSize().x / 2, 10), Color::Green, Color::White);
    logo.DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(logo.GetSize().x / 2, 11), Color::Green, Color::White);
    logo.DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(logo.GetSize().x / 2, 12), Color::Green, Color::White);
    logo.DrawTextCenter("                                           (_____|              ",        Vector2(logo.GetSize().x / 2, 13), Color::Green, Color::White);

    while(!Keyboard::GetKey(VK_SPACE) || effect < 2)
    {
        if((GetTick() - lasttick) > 25)
        {
            lasttick = GetTick();

            //blood effect
            static bool bleed = true;
            if(effect > 1 && bleed)
            {
                uint8_t count = 0;
                for(register uint8_t x = 0; x < blood.GetSize().x; ++x)
                {
                    for(register uint8_t y = 0; y < blood.GetSize().y; ++y)
                    {
                        if(blood(Vector2(x, y)).backcolor != Color::Red)
                        {
                            if((std::rand() % 101) == 0)
                            {
                                blood(Vector2(x, y)).backcolor = Color::Red;
                                ++count;
                                if(y > 10)
                                    bleed = false;
                            }
                            break;
                        }
                    }
                    if(count > 2)
                    {
                        break;
                    }
                }

            }

            this->DrawSprite(blood, Vector2(1, 1));

            //console effect
            for(register uint8_t row = 2; row < 9; ++row)
            {
                for(register uint8_t x = 20; x < colc; ++x)
                {
                    if(row % 2)
                    {
                        this->GetPixel(Vector2(x, row)).character = logo(Vector2(x, row - 2)).character;
                        this->GetPixel(Vector2(x, row)).forecolor = logo(Vector2(x, row - 2)).forecolor;
                    }
                    else
                    {
                        this->GetPixel(Vector2(logo.GetSize().x - 1 - x, row)).character = logo(Vector2(logo.GetSize().x - 1 - x, row - 2)).character;
                        this->GetPixel(Vector2(logo.GetSize().x - 1 - x, row)).forecolor = logo(Vector2(logo.GetSize().x - 1 - x, row - 2)).forecolor;
                    }
                }
            }

            if(colc < logo.GetSize().x - 6)
                ++colc;
            else
                effect = 1;

            if(effect > 0)
            {
                for(register uint8_t row = 9; row < 16; ++row)
                {
                    for(register uint8_t x = 6; x < colg; ++x)
                    {
                        if(row % 2)
                        {
                            this->GetPixel(Vector2(x, row)).character = logo(Vector2(x, row - 2)).character;
                            this->GetPixel(Vector2(x, row)).forecolor = logo(Vector2(x, row - 2)).forecolor;
                        }
                        else
                        {
                            this->GetPixel(Vector2(logo.GetSize().x - 1 - x, row)).character = logo(Vector2(logo.GetSize().x - 1 - x, row - 2)).character;
                            this->GetPixel(Vector2(logo.GetSize().x - 1 - x, row)).forecolor = logo(Vector2(logo.GetSize().x - 1 - x, row - 2)).forecolor;
                        }
                    }
                }

                if(colg < logo.GetSize().x - 6)
                    ++colg;
                else
                    effect = 2;
            }

            for(register uint8_t x = 0; x < GetSize().x; ++x)
            {
                for(register uint8_t y = 0; y < GetSize().y; ++y)
                {
                    if(y == 0 || x == 0 || y == GetSize().y-1 || x == GetSize().x-1)
                    {
                        this->GetPixel(Vector2(x, y)).character = BORDER_CHAR;
                        this->GetPixel(Vector2(x, y)).forecolor = Color::Red;
                    }
                }
            }

            if((GetTick() - blinktick) > 1000)
            {
                blinktick = GetTick();
                blink = !blink;
            }

            if(effect > 1)
            {
                if(blink)
                {
                    this->DrawTextCenter("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ", Vector2(GetSize().x / 2, 17), Color::DarkRed, Color::Transparent);
                    this->DrawTextCenter("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ", Vector2(GetSize().x / 2, 18), Color::DarkRed, Color::Transparent);
                    this->DrawTextCenter(  "Press space"  , Vector2(GetSize().x / 2, 18), Color::White, Color::Transparent);
                    this->DrawTextCenter("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ", Vector2(GetSize().x / 2, 19), Color::DarkRed, Color::Transparent);
                }
            }

            this->DrawText("Developed by", Vector2(1, GetSize().y -3), Color::White, Color::Transparent);
            this->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(1, GetSize().y -2), Color::White, Color::Transparent);

            this->DrawTextRight(VERSION,Vector2(GetSize().x-2, GetSize().y-2), Color::White, Color::Transparent);

            this->Update();
        }
    }

#else

    uint8_t col = 0;

    while(!Keyboard::GetKey(VK_SPACE))
    {

        for(register uint8_t x = 0; x < GetSize().x; ++x)
            for(register uint8_t y = 0; y < GetSize().y; ++y)
                if(y == 0 || x == 0 || y == GetSize().y-1 || x == GetSize().x-1)
                {
                    data[x][y].character = '*';
                    data[x][y].forecolor = Color::Blue;
                }

        DrawTextCenter("  ______                       _       ",     Vector2(GetSize().x / 2, 2), Color::White, Color::Black);
        DrawTextCenter(" / _____)                     | |      ",     Vector2(GetSize().x / 2, 3), Color::White, Color::Black);
        DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(GetSize().x / 2, 4), Color::White, Color::Black);
        DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(GetSize().x / 2, 5), Color::White, Color::Black);
        DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(GetSize().x / 2, 6), Color::White, Color::Black);
        DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(GetSize().x / 2, 7), Color::White, Color::Black);

        DrawTextCenter("  ______                      _______             _             ",        Vector2(GetSize().x / 2, 10), Color::White, Color::Black);
        DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(GetSize().x / 2, 11), Color::White, Color::Black);
        DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(GetSize().x / 2, 12), Color::White, Color::Black);
        DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(GetSize().x / 2, 13), Color::White, Color::Black);
        DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(GetSize().x / 2, 14), Color::White, Color::Black);
        DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(GetSize().x / 2, 15), Color::White, Color::Black);
        DrawTextCenter("                                           (_____|              ",        Vector2(GetSize().x / 2, 16), Color::White, Color::Black);

        //effect
        static uint32_t lastpp = 0;

        if(((GetTick() - lastpp) > 100) && (col < (GetSize().x / 2)))
        {
            lastpp = GetTick();
            ++col;
        }

        for(register uint8_t y = 2; y < 17; ++y)
        {
            for(register uint8_t x = 2; x < GetSize().x; ++x)
            {
                if((col <= (GetSize().x / 2)) && x < col)
                {
                    data[x][y].forecolor = Color::DarkGreen;
                    data[(GetSize().x-1) - x][y].forecolor = Color::Yellow;
                }
            }
        }

        data[59][10].forecolor = Color::Blue;
        data[59][11].forecolor = Color::Blue;
        data[58][11].forecolor = Color::Blue;
        data[60][11].forecolor = Color::Blue;
        //effect

        DrawText("Developed by", Vector2(1, GetSize().y -3), Color::White, Color::Black);
        DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(1, GetSize().y -2), Color::White, Color::Black);

        DrawTextRight(VERSION,Vector2(GetSize().x-2, GetSize().y-2), Color::White, Color::Black);

        DrawTextCenter("Press space", Vector2(GetSize().x / 2, 19), Color::White, Color::Black);

        Update();
        Clear();
    }

#endif
}

void Console::ShowError(const string &text, const bool close = true)
{
    this->Resize(Vector2(80,25));
    while(!Keyboard::GetKey(VK_SPACE))
    {
        this->Clear();
        this->DrawText(" ____ ____ ____ ____ ____ ", Vector2(0, 0), Color::White, Color::Black);
        this->DrawText("||E |||r |||r |||o |||r ||", Vector2(0, 1), Color::White, Color::Black);
        this->DrawText("||__|||__|||__|||__|||__||", Vector2(0, 2), Color::White, Color::Black);
        this->DrawText("|/__\\|/__\\|/__\\|/__\\|/__\\|", Vector2(0, 3), Color::White, Color::Black);
        this->DrawTextCenter(text, Vector2(this->GetSize().x / 2, 15), Color::Red, Color::Black);
        this->DrawTextRight(close?"Press space to close application":"Press space to continue", Vector2(this->GetSize().x -1, this->GetSize().y -1), Color::White, Color::Black);
        this->Update();
        this->Clear();
    }
    if(close)
        exit(1);
}


bool Console::InputDialog(const string &title, const string &text, string &result)
{
    char lastkey = 0;
    bool cancel = false;

    Sprite buffer_bkp(*this);

    result.clear();

    while(lastkey != '\n')
    {
        if(lastkey == VK_ESCAPE)
        {
            return(false);
        }
        if(lastkey == VK_BACK)
        {
            if(result.size() > 0)
            {
                result.erase(result.size() -1);
            }
        }
        else if(lastkey == VK_LEFT)
        {
            cancel = false;
        }
        else if(lastkey == VK_RIGHT)
        {
            cancel = true;
        }
        else if(((lastkey > 64 && lastkey < 91) || (lastkey > 47 && lastkey < 58) || lastkey == ' ') && result.length() < 38)
        {
            result+= lastkey;
        }

        this->DrawTextCenter("ษออออออออออออออออออออออออออออออออออออออออป", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -3), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -2), Color::Black, Color::White);
        this->DrawTextCenter(title                                       , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -2), Color::Black, Color::White);
        this->DrawTextCenter("ฬออออออออออออออออออออออออออออออออออออออออน", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -1), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2), Color::Black, Color::White);
        this->DrawTextCenter(text                                        , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2), Color::Black, Color::White);
        this->DrawTextCenter("ฬออออออออออออออออออออออออออออออออออออออออน", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +1), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +2), Color::Black, Color::White);
        this->DrawTextCenter(result + TEXT_CURSOR                        , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +2), Color::Black, Color::White);
        this->DrawTextCenter("ศออออออออออออออออออออออออออออออออออออออออผ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +3), Color::Black, Color::White);


        this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +5), Color::Black, Color::White);
        this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +6), Color::Black, Color::White);
        this->DrawTextCenter( "Cancel"  , Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +6), cancel?Color::White:Color::Black, cancel?Color::Black:Color::White);
        this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +7), Color::Black, Color::White);
        this->DrawTextCenter("\x1B    \x1A", Vector2(this->GetSize().x / 2, this->GetSize().y / 2 +6), Color::Black, Color::White);

        this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +5), Color::Black, Color::White);
        this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +6), Color::Black, Color::White);
        this->DrawTextCenter( "  Ok  "  , Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +6), cancel?Color::Black:Color::White, cancel?Color::White:Color::Black);
        this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +7), Color::Black, Color::White);

        this->Update();
        lastkey = Keyboard::GetNextKey();
    }

    this->DrawSprite(buffer_bkp, Vector2(0, 0));

    return(!cancel && !result.empty());
}

bool Console::MsgDialog(const string &title, const string &text, const bool only_ok)
{
    char lastkey = 0;
    bool cancel = false;
    Sprite buffer_bkp(*this);

    buffer_bkp = *this;

    while(lastkey != '\n' && lastkey != ' ')
    {
        this->DrawTextCenter("ษออออออออออออออออออออออออออออออออออออออออป", Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 -2), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 -1), Color::Black, Color::White);
        this->DrawTextCenter(title                                       , Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 -1), Color::Black, Color::White);
        this->DrawTextCenter("ฬออออออออออออออออออออออออออออออออออออออออน", Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 +1), Color::Black, Color::White);
        this->DrawTextCenter(text                                        , Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 +1), Color::Black, Color::White);
        this->DrawTextCenter("ศออออออออออออออออออออออออออออออออออออออออผ", Vector2(this->GetSize().x / 2 -1, this->GetSize().y / 2 +2), Color::Black, Color::White);

        if(only_ok)
        {
            this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +4), Color::Black, Color::White);
            this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +5), Color::Black, Color::White);
            this->DrawTextCenter( "  Ok  "   , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +5),  Color::White, Color::Black);
            this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +6), Color::Black, Color::White);
        }
        else
        {
            if(lastkey == VK_LEFT)
            {
                cancel = false;
            }
            else if(lastkey == VK_RIGHT)
            {
                cancel = true;
            }
            this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +4), Color::Black, Color::White);
            this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +5), Color::Black, Color::White);
            this->DrawTextCenter( "Cancel"  , Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +5), cancel?Color::White:Color::Black, cancel?Color::Black:Color::White);
            this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 +10, this->GetSize().y / 2 +6), Color::Black, Color::White);
            this->DrawTextCenter("\x1B    \x1A", Vector2(this->GetSize().x / 2, this->GetSize().y / 2 +7), Color::Black, Color::White);

            this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +4), Color::Black, Color::White);
            this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +5), Color::Black, Color::White);
            this->DrawTextCenter( "  Ok  "  , Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +5), cancel?Color::Black:Color::White, cancel?Color::White:Color::Black);
            this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 -10, this->GetSize().y / 2 +6), Color::Black, Color::White);
        }

        this->Update();
        lastkey = Keyboard::GetNextKey();
    }

    this->DrawSprite(buffer_bkp, Vector2(0, 0));
    return(!cancel);
}

void Console::DrawDebugInfo()
{
    this->DrawText("Frames per second: " + IntToStr(current_fps), Vector2(0, 0), Color::White, Color::Black);
    this->DrawText("Delta time: " + IntToStr(delta_time), Vector2(0, 1), Color::White, Color::Black);
    this->DrawText("Life time: " + IntToStr(this->GetLifeTime()), Vector2(0, 2), Color::White, Color::Black);
    this->DrawText("Locked Frame: " + lock_fps > 0?"Yes":"No", Vector2(0, 3), lock_fps > 0?Color::Green:Color::Red, Color::Black);
    this->DrawText("Locked Frame at: " + IntToStr(lock_fps), Vector2(0, 4), Color::White, Color::Black);
    this->DrawText("Sleep interval: " + IntToStr(sleep_time), Vector2(0, 5), Color::White, Color::Black);
    this->DrawText("Buffer memory: " + sizeof(Pixel) * size.x * size.y, Vector2(0, 6), Color::White, Color::Black);
    this->DrawText(": " + IntToStr(sleep_time), Vector2(0, 7), Color::White, Color::Black);
}

uint32_t Console::GetTick()
{
    static uint64_t tick_frequence = 0;
    uint64_t counter = 0;
    if(tick_frequence == 0)
    {
        if(!QueryPerformanceFrequency((LARGE_INTEGER*)&tick_frequence))
        {
            tick_frequence = 1000;
        }
    }

    if(QueryPerformanceCounter((LARGE_INTEGER*)&counter))
    {
        return(counter / (tick_frequence / 1000));
    }
    else
    {
        return(GetTickCount());
    }
}

uint32_t Console::GetLifeTime()
{
    return(GetTick() - this->start_time);
}

uint32_t Console::GetDeltaTime()
{
    return(this->delta_time);
}

uint16_t Console::GetCurrentFps()
{
    return(this->current_fps);
}

void Console::LockFps(uint8_t limit)
{
    this->lock_fps = limit;
}

bool Console::SetPosition(Vector2 position)
{
    return(SetWindowPos(handle, HWND_TOP, position.x, position.y, NULL, NULL, SWP_NOSIZE));
}

bool Console::Resize(Vector2 new_size)
{
    SMALL_RECT displayarea;

    displayarea.Top = 0;
    displayarea.Left = 0;
    displayarea.Bottom = new_size.y-1;
    displayarea.Right = new_size.x-1;

    COORD coord = {new_size.x, new_size.y};

    if(SetConsoleScreenBufferSize(output_handle, coord))
    {
        if(SetConsoleWindowInfo(output_handle, TRUE, &displayarea))
        {
            if(this->size.x != new_size.x || this->size.y != new_size.y)
            {
                Sprite::Resize(new_size);
            }
            return (true);
        }
    }
    return (false);
}

bool Console::Focus()
{
    if(GetForegroundWindow() == handle)
        return(true);
    else
        return(false);
}

void Console::WaitFocus()
{
    while(!Focus()) {};
}

bool Console::SetTextColor (color forecolor, color backcolor)
{
    return (SetConsoleTextAttribute (output_handle, forecolor | backcolor << 4) == TRUE);
}

bool Console::SetCursorPosition(Vector2 position)
{
    COORD coord = {position.x, position.y};
    return (SetConsoleCursorPosition(output_handle, coord) == TRUE);
}

bool Console::SetTitle(const string &title)
{
    return SetConsoleTitle ((LPCSTR)title.c_str());
}

bool Console::SetCursorSize(uint8_t size, bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo = { size, visible };
    return (SetConsoleCursorInfo (output_handle, &cursorinfo) == TRUE);
}

Vector2 Console::ScreenResolution()
{
    return(Vector2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
}

void Console::Update()
{
    this->SetCursorPosition(Vector2(0, 0));
    //TODO: fazer backup da posicao anterior do cursor e restaurar novamente no final da funcao
    CHAR_INFO winbuffer[this->size.y][this->size.x];
    //TODO:Corrigir o x e y invertido acima

    for(register uint8_t x = 0; x < this->size.x; ++x)
        for(register uint8_t y = 0; y < this->size.y; ++y)
        {
            winbuffer[y][x].Char.AsciiChar = this->data[x][y].character;
            winbuffer[y][x].Attributes = this->data[x][y].forecolor | this->data[x][y].backcolor << 4;
        }
    COORD size = {this->size.x, this->size.y};
    COORD start = {0, 0};
    SMALL_RECT srect = {0, 0, this->size.x, this->size.y};
    WriteConsoleOutput(output_handle, (CHAR_INFO*)winbuffer, size, start, &srect);

    this->delta_time = this->GetLifeTime() - this->last_time;
    this->last_time = this->GetLifeTime();
    if(last_time - fps_time > 1000)
    {
        this->current_fps = this->fps;
        this->fps_time = this->last_time;
        this->fps = 0;
    }
    ++this->fps;
    if(lock_fps > 0)
    {
        sleep_time = (1000 / lock_fps) - (delta_time - sleep_time);
        if(sleep_time > 0)
        {
            Sleep(sleep_time);
        }
    }
}

void Console::ExceptionHandler()
{
    try
    {
        throw;
    }
    catch(...)
    {
        //ShowError("UNEXPECTED ERROR");
    }
}
