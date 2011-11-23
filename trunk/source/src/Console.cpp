#include "Console.h"

using namespace ConsoleGameEngine;

void Console::PreInit()
{
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    handle = GetConsoleWindow();
    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    SetCursorSize(1, false);
    SetTitle("Console Game Engine");
    currentfps = 0;
    fps = 0;
    fpstick = 0;
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
    uint8_t colc = 0, colg = 0, effect = 0;
    Sprite logo(Vector2(buffer->GetSize().x, 14)), blood(Vector2(buffer->GetSize().x - 2, buffer->GetSize().y- 2));
    uint32_t lasttick = GetTick(), blinktick = GetTick();
    bool blink = false;

    std::srand(GetTick());

    logo.DrawTextCenter("  ______                       _       ",     Vector2(logo.GetSize().x / 2, 0), Colors::Blue, Colors::White);
    logo.DrawTextCenter(" / _____)                     | |      ",     Vector2(logo.GetSize().x / 2, 1), Colors::Blue, Colors::White);
    logo.DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(logo.GetSize().x / 2, 2), Colors::Blue, Colors::White);
    logo.DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(logo.GetSize().x / 2, 3), Colors::Blue, Colors::White);
    logo.DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(logo.GetSize().x / 2, 4), Colors::Blue, Colors::White);
    logo.DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(logo.GetSize().x / 2, 5), Colors::Blue, Colors::White);

    logo.DrawTextCenter("  ______                      _______             _             ",        Vector2(logo.GetSize().x / 2, 7), Colors::Green, Colors::White);
    logo.DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(logo.GetSize().x / 2, 8), Colors::Green, Colors::White);
    logo.DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(logo.GetSize().x / 2, 9), Colors::Green, Colors::White);
    logo.DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(logo.GetSize().x / 2, 10), Colors::Green, Colors::White);
    logo.DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(logo.GetSize().x / 2, 11), Colors::Green, Colors::White);
    logo.DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(logo.GetSize().x / 2, 12), Colors::Green, Colors::White);
    logo.DrawTextCenter("                                           (_____|              ",        Vector2(logo.GetSize().x / 2, 13), Colors::Green, Colors::White);

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
                        if(blood.data[x][y].backcolor != Colors::Red)
                        {
                            if((std::rand() % 101) == 0)
                            {
                                blood.data[x][y].backcolor = Colors::Red;
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

            buffer->DrawSprite(blood, Vector2(1, 1));

            //console effect
            for(register uint8_t row = 2; row < 9; ++row)
            {
                for(register uint8_t x = 20; x < colc; ++x)
                {
                    if(row % 2)
                    {
                        buffer->data[x][row].character = logo.data[x][row - 2].character;
                        buffer->data[x][row].forecolor = logo.data[x][row - 2].forecolor;
                    }
                    else
                    {
                        buffer->data[logo.GetSize().x - 1 - x][row].character = logo.data[logo.GetSize().x - 1 - x][row - 2].character;
                        buffer->data[logo.GetSize().x - 1 - x][row].forecolor = logo.data[logo.GetSize().x - 1 - x][row - 2].forecolor;
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
                            buffer->data[x][row].character = logo.data[x][row - 2].character;
                            buffer->data[x][row].forecolor = logo.data[x][row - 2].forecolor;
                        }
                        else
                        {
                            buffer->data[logo.GetSize().x - 1 - x][row].character = logo.data[logo.GetSize().x - 1 - x][row - 2].character;
                            buffer->data[logo.GetSize().x - 1 - x][row].forecolor = logo.data[logo.GetSize().x - 1 - x][row - 2].forecolor;
                        }
                    }
                }

                if(colg < logo.GetSize().x - 6)
                    ++colg;
                else
                    effect = 2;
            }

            for(register uint8_t x = 0; x < GetWindowSize().x; ++x)
            {
                for(register uint8_t y = 0; y < GetWindowSize().y; ++y)
                {
                    if(y == 0 || x == 0 || y == GetWindowSize().y-1 || x == GetWindowSize().x-1)
                    {
                        buffer->data[x][y].character = '�';
                        buffer->data[x][y].forecolor = Colors::Red;
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
                    buffer->DrawTextCenter("같같같같같같같�", Vector2(GetWindowSize().x / 2, 17), Colors::DarkRed, Colors::Transparent);
                    buffer->DrawTextCenter("같같같같같같같�", Vector2(GetWindowSize().x / 2, 18), Colors::DarkRed, Colors::Transparent);
                    buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().x / 2, 18), Colors::White, Colors::Transparent);
                    buffer->DrawTextCenter("같같같같같같같�", Vector2(GetWindowSize().x / 2, 19), Colors::DarkRed, Colors::Transparent);
                }
            }

            buffer->DrawText("Developed by", Vector2(1, GetWindowSize().y -3), Colors::White, Colors::Transparent);
            buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(1, GetWindowSize().y -2), Colors::White, Colors::Transparent);

            buffer->DrawTextRight(VERSION,Vector2(GetWindowSize().x-2, GetWindowSize().y-2), Colors::White, Colors::Transparent);

            UpdateConsole();
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
                    data[x][y].forecolor = Colors::Blue;
                }

        DrawTextCenter("  ______                       _       ",     Vector2(GetSize().x / 2, 2), Colors::White, Colors::Black);
        DrawTextCenter(" / _____)                     | |      ",     Vector2(GetSize().x / 2, 3), Colors::White, Colors::Black);
        DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(GetSize().x / 2, 4), Colors::White, Colors::Black);
        DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(GetSize().x / 2, 5), Colors::White, Colors::Black);
        DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(GetSize().x / 2, 6), Colors::White, Colors::Black);
        DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(GetSize().x / 2, 7), Colors::White, Colors::Black);

        DrawTextCenter("  ______                      _______             _             ",        Vector2(GetSize().x / 2, 10), Colors::White, Colors::Black);
        DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(GetSize().x / 2, 11), Colors::White, Colors::Black);
        DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(GetSize().x / 2, 12), Colors::White, Colors::Black);
        DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(GetSize().x / 2, 13), Colors::White, Colors::Black);
        DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(GetSize().x / 2, 14), Colors::White, Colors::Black);
        DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(GetSize().x / 2, 15), Colors::White, Colors::Black);
        DrawTextCenter("                                           (_____|              ",        Vector2(GetSize().x / 2, 16), Colors::White, Colors::Black);

        //effect
        static uint32_t lastpp = 0;

        if(((GetTick() - lastpp) > 100) && (col < (GetSize().x / 2)))
        {
            lastpp = GetTick();
            ++col;
        }

        for(register uint8_t y = 2; y < 17; ++y)
            for(register uint8_t x = 2; x < GetSize().x; ++x)
            {
                if((col <= (GetSize().x / 2)) && x < col)
                {
                    data[x][y].forecolor = Colors::DarkGreen;
                    data[(GetSize().x-1) - x][y].forecolor = Colors::Yellow;
                }
            }

        data[59][10].forecolor = Colors::Blue;
        data[59][11].forecolor = Colors::Blue;
        data[58][11].forecolor = Colors::Blue;
        data[60][11].forecolor = Colors::Blue;
        //effect

        DrawText("Developed by", Vector2(1, GetSize().y -3), Colors::White, Colors::Black);
        DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(1, GetSize().y -2), Colors::White, Colors::Black);

        DrawTextRight(VERSION,Vector2(GetSize().x-2, GetSize().y-2), Colors::White, Colors::Black);

        DrawTextCenter("Press space", Vector2(GetSize().x / 2, 19), Colors::White, Colors::Black);

        Update();
        Clear();
    }

#endif
}

void Console::ShowError(const string &text, const bool close)
{
    Resize(Vector2(80,25));
    while(!Keyboard::GetKey(VK_SPACE))
    {
        Clear();
        DrawText(" ____ ____ ____ ____ ____ ", Vector2(0, 0), Colors::White, Colors::Black);
        this->DrawText("||E |||r |||r |||o |||r ||", Vector2(0, 1), Colors::White, Colors::Black);
        this->DrawText("||__|||__|||__|||__|||__||", Vector2(0, 2), Colors::White, Colors::Black);
        this->DrawText("|/__\\|/__\\|/__\\|/__\\|/__\\|", Vector2(0, 3), Colors::White, Colors::Black);
        this->DrawTextCenter(text, Vector2(this->GetSize().x / 2, 15), Colors::Red, Colors::Black);
        this->DrawTextRight("Press space to close application", Vector2(this->GetSize().x -1, this->GetSize().y -1), Colors::White, Colors::Black);
        this->Update();
        this->Clear();
    }
    exit(1);
}

bool Console::ShowDialog(const string &title, const string &text, string &result)
{
    result.clear();
    char lastkey = 0;
    bool cancel = false;

    while(!cancel)
    {
        if(lastkey == VK_ESCAPE)
        {
            return(false);
        }
        if(lastkey == '\n')
        {
            if(result.empty())
            {
                return(false);
            }
            else
            {
                return(true);
            }
        }
        else if(lastkey == VK_BACK)
        {
            if(result.size() > 0)
            {
                result.erase(result.size() -1);
            }
        }
        else if((lastkey > 64 && lastkey < 91) || (lastkey > 47 && lastkey < 58) || lastkey == ' ')
        {
            result+= lastkey;
        }

        this->Clear(Colors::White);
        this->DrawTextCenter(       "******************************************"           ,Vector2(this->GetSize().x / 2, 5), Colors::Black, Colors::White);
        this->DrawTextCenter(       "*                                        *"           , Vector2(this->GetSize().x / 2, 6), Colors::Black, Colors::White);
        this->DrawTextCenter(title                                                         , Vector2(this->GetSize().x / 2, 6), Colors::Black, Colors::White);

        this->DrawTextCenter("************************************************************", Vector2(this->GetSize().x / 2, 7), Colors::Black, Colors::White);

        this->DrawTextCenter("*                                                          *", Vector2(this->GetSize().x / 2, 8), Colors::Black, Colors::White);
        this->DrawTextCenter(text                                                          , Vector2(this->GetSize().x / 2, 8), Colors::Black, Colors::White);
        this->DrawTextCenter("************************************************************", Vector2(this->GetSize().x / 2, 9), Colors::Black, Colors::White);
        this->DrawTextCenter("*                                                          *", Vector2(this->GetSize().x / 2, 10), Colors::Black, Colors::White);
        this->DrawTextCenter(result                                                        , Vector2(this->GetSize().x / 2, 10), Colors::Black, Colors::White);
        this->DrawTextCenter("************************************************************", Vector2(this->GetSize().x / 2, 11), Colors::Black, Colors::White);

        this->Update();
        lastkey = Keyboard::GetNextKey();
    }

    return(false);
}

uint32_t Console::GetTick()
{
    return(GetTickCount());
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

uint16_t Console::GetCurrentFps()
{
    return(this->currentfps);
}

void Console::Update()
{
    this->SetCursorPosition(Vector2(0, 0));
    //TODO: fazer backup da posi豫o anterior do cursor e restaurar novamente no final da fun豫o
    CHAR_INFO winbuffer[this->size.y][this->size.x];
    //TODO:Corrigir o x e y invertido acima
    if((this->GetTick() - this->fpstick) > 1000)
    {
        this->fpstick = this->GetTick();
        this->currentfps = this->fps;
        this->fps = 0;
    }
    this->fps++;

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
}
