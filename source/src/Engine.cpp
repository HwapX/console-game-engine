#include "Engine.h"

using namespace ConsoleGameEngine;

void Engine::PreInit()
{
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_handle = GetConsoleWindow();
    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    SetCursorSize(1, false);
    SetWindowTitle("Console Game Engine");
    currentfps = 0;
    fps = 0;
    fpstick = 0;
    buffer = NULL;
    console_size.x = 80;
    console_size.y = 25;

}

void Engine::PosInit()
{
    SetWindowSize(console_size);
    ShowLogo();
}

Engine::Engine()
{
    PreInit();

    PosInit();
}

Engine::Engine(const string &title)
{
    PreInit();

    SetWindowTitle(title);

    PosInit();
}

Engine::Engine(const Vector2 &position, const Vector2 &size)
{
    PreInit();

    console_size = size;
    SetWindowPosition(position);

    PosInit();
}

Engine::Engine(const Vector2 &size)
{
    PreInit();

    console_size = size;

    PosInit();
}

Engine::Engine(const string &title, const Vector2 &size)
{
    PreInit();

    SetWindowTitle(title);
    console_size = size;

    PosInit();
}

Engine::Engine(const string &title, const Vector2 &position, const Vector2 &size)
{
    PreInit();

    SetWindowTitle(title);
    console_size = size;
    SetWindowPosition(position);

    PosInit();
}

void Engine::ShowLogo()
{
#ifndef OLDLOGO
    byte colc = 0, colg = 0, effect = 0;
    Sprite logo(Vector2(buffer->GetSize().x, 14)), blood(Vector2(buffer->GetSize().x - 2, buffer->GetSize().y- 2));
    int lasttick = GetTick(), blinktick = GetTick();
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
                byte count = 0;
                for(register byte x = 0; x < blood.GetSize().x; ++x)
                {
                    for(register byte y = 0; y < blood.GetSize().y; ++y)
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
            for(register byte row = 2; row < 9; ++row)
            {
                for(register byte x = 20; x < colc; ++x)
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
                for(register byte row = 9; row < 16; ++row)
                {
                    for(register byte x = 6; x < colg; ++x)
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

            for(register byte x = 0; x < GetWindowSize().x; ++x)
            {
                for(register byte y = 0; y < GetWindowSize().y; ++y)
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

    byte col = 0;

    while(!Keyboard::GetKey(VK_SPACE))
    {

        for(register byte x = 0; x < GetWindowSize().x; ++x)
            for(register byte y = 0; y < GetWindowSize().y; ++y)
                if(y == 0 || x == 0 || y == GetWindowSize().y-1 || x == GetWindowSize().x-1)
                {
                    buffer->data[x][y].character = '*';
                    buffer->data[x][y].forecolor = Colors::Blue;
                }

        buffer->DrawTextCenter("  ______                       _       ",     Vector2(GetWindowSize().x / 2, 2), Colors::White, Colors::Black);
        buffer->DrawTextCenter(" / _____)                     | |      ",     Vector2(GetWindowSize().x / 2, 3), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(GetWindowSize().x / 2, 4), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(GetWindowSize().x / 2, 5), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(GetWindowSize().x / 2, 6), Colors::White, Colors::Black);
        buffer->DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(GetWindowSize().x / 2, 7), Colors::White, Colors::Black);

        buffer->DrawTextCenter("  ______                      _______             _             ",        Vector2(GetWindowSize().x / 2, 10), Colors::White, Colors::Black);
        buffer->DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(GetWindowSize().x / 2, 11), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(GetWindowSize().x / 2, 12), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(GetWindowSize().x / 2, 13), Colors::White, Colors::Black);
        buffer->DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(GetWindowSize().x / 2, 14), Colors::White, Colors::Black);
        buffer->DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(GetWindowSize().x / 2, 15), Colors::White, Colors::Black);
        buffer->DrawTextCenter("                                           (_____|              ",        Vector2(GetWindowSize().x / 2, 16), Colors::White, Colors::Black);

        //effect
        static int lastpp = 0;

        if(((GetTick() - lastpp) > 100) && (col < (GetWindowSize().x / 2)))
        {
            lastpp = GetTick();
            ++col;
        }

        for(register byte y = 2; y < 17; ++y)
            for(register byte x = 2; x < GetWindowSize().x; ++x)
            {
                if((col <= (GetWindowSize().x / 2)) && x < col)
                {
                    buffer->data[x][y].forecolor = Colors::DarkGreen;
                    buffer->data[(GetWindowSize().x-1) - x][y].forecolor = Colors::Yellow;
                }
            }

        buffer->data[59][10].forecolor = Colors::Blue;
        buffer->data[59][11].forecolor = Colors::Blue;
        buffer->data[58][11].forecolor = Colors::Blue;
        buffer->data[60][11].forecolor = Colors::Blue;
        //effect

        buffer->DrawText("Developed by", Vector2(1, GetWindowSize().y -3), Colors::White, Colors::Black);
        buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(1, GetWindowSize().y -2), Colors::White, Colors::Black);

        buffer->DrawTextRight(VERSION,Vector2(GetWindowSize().x-2, GetWindowSize().y-2), Colors::White, Colors::Black);

        buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().x / 2, 19), Colors::White, Colors::Black);

        UpdateConsole();
        buffer->Clear();
    }

#endif
}

void Engine::ShowError(const string &text, const bool close)
{
    SetWindowSize(Vector2(80,25));
    while(!Keyboard::GetKey(VK_SPACE))
    {
        buffer->Clear();
        buffer->DrawText(" ____ ____ ____ ____ ____ ", Vector2(0, 0), Colors::White, Colors::Black);
        buffer->DrawText("||E |||r |||r |||o |||r ||", Vector2(0, 1), Colors::White, Colors::Black);
        buffer->DrawText("||__|||__|||__|||__|||__||", Vector2(0, 2), Colors::White, Colors::Black);
        buffer->DrawText("|/__\\|/__\\|/__\\|/__\\|/__\\|", Vector2(0, 3), Colors::White, Colors::Black);
        buffer->DrawTextCenter(text, Vector2(buffer->GetSize().x / 2, 15), Colors::Red, Colors::Black);
        buffer->DrawTextRight("Press space to close application", Vector2(buffer->GetSize().x -1, buffer->GetSize().y -1), Colors::White, Colors::Black);
        UpdateConsole();
        buffer->Clear();
    }
    exit(1);
}

bool Engine::ShowDialog(const string &title, const string &text, string &result)
{
    result.clear();
    char lastkey = 0;
    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        if(lastkey == VK_RETURN)
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

        this->buffer->Clear(Colors::White);
        this->buffer->DrawTextCenter(       "******************************************"           ,Vector2(buffer->GetSize().x / 2, 5), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter(       "*                                        *"           , Vector2(buffer->GetSize().x / 2, 6), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter(title                                                         , Vector2(buffer->GetSize().x / 2, 6), Colors::Black, Colors::White);

        this->buffer->DrawTextCenter("************************************************************", Vector2(buffer->GetSize().x / 2, 7), Colors::Black, Colors::White);

        this->buffer->DrawTextCenter("*                                                          *", Vector2(buffer->GetSize().x / 2, 8), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter(text                                                          , Vector2(buffer->GetSize().x / 2, 8), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter("************************************************************", Vector2(buffer->GetSize().x / 2, 9), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter("*                                                          *", Vector2(buffer->GetSize().x / 2, 10), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter(result                                                        , Vector2(buffer->GetSize().x / 2, 10), Colors::Black, Colors::White);
        this->buffer->DrawTextCenter("************************************************************", Vector2(buffer->GetSize().x / 2, 11), Colors::Black, Colors::White);

        this->UpdateConsole();
        lastkey = Keyboard::GetNextKey();
    }

    return(false);
}

int Engine::GetTick()
{
    return(GetTickCount());
}

bool Engine::SetWindowPosition(Vector2 position)
{
    return(SetWindowPos(console_handle, HWND_TOP, position.x, position.y, NULL, NULL, SWP_NOSIZE));
}

Engine::~Engine()
{
    delete buffer;
}

bool Engine::SetWindowSize(Vector2 size)
{
    SMALL_RECT displayarea;

    displayarea.Top = 0;
    displayarea.Left = 0;
    displayarea.Bottom = size.y-1;
    displayarea.Right = size.x-1;

    COORD coord = {size.x, size.y};

    if(SetConsoleScreenBufferSize(output_handle, coord))
    {
        if(SetConsoleWindowInfo(output_handle, TRUE, &displayarea))
        {
            console_size = size;

            if(buffer != NULL)
            {
                delete buffer;
            }
            buffer = new Sprite(console_size);
            return (true);
        }
    }
    return (false);
}

Vector2 Engine::GetWindowSize()
{
    /*CONSOLE_SCREEN_BUFFER_INFO coninfo;

    GetConsoleScreenBufferInfo (output_handle, &coninfo);
    return (Vector2(coninfo.dwsize.x, coninfo.dwsize.y));*/
    return(console_size);
}

Vector2 Engine::GetScreenResolution()
{
    Vector2 temp;
    temp.x = GetSystemMetrics(SM_CXSCREEN);
    temp.y = GetSystemMetrics(SM_CYSCREEN);
    return temp;
}

bool Engine::Focus()
{
    if(GetForegroundWindow() == console_handle)
        return(true);
    else
        return(false);
}

void Engine::WaitFocus()
{
    while(!Focus()) {};
}

bool Engine::SetTextColor (color forecolor, color backcolor)
{
    return (SetConsoleTextAttribute (output_handle, forecolor | backcolor << 4) == TRUE);
}

bool Engine::SetCursorPosition(Vector2 position)
{
    COORD coord = {position.x, position.y};
    return (SetConsoleCursorPosition(output_handle, coord) == TRUE);
}

bool Engine::SetWindowTitle(const string &title)
{
    return SetConsoleTitle ((LPCSTR)title.c_str());
}

bool Engine::SetCursorSize(byte size, bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo = { size, visible };
    return (SetConsoleCursorInfo (output_handle, &cursorinfo) == TRUE);
}

short int Engine::GetCurrentFps()
{
    return(this->currentfps);
}

void Engine::UpdateConsole()
{
    this->SetCursorPosition(Vector2(0, 0));
    //TODO: fazer backup da posi豫o anterior do cursor e restaurar novamente no final da fun豫o
    CHAR_INFO winbuffer[this->console_size.y][this->console_size.x];

    if((this->GetTick() - this->fpstick) > 1000)
    {
        this->fpstick = this->GetTick();
        this->currentfps = this->fps;
        this->fps = 0;
    }
    this->fps++;

    for(register byte x = 0; x < this->console_size.x; ++x)
        for(register byte y = 0; y < this->console_size.y; ++y)
        {
            winbuffer[y][x].Char.AsciiChar = this->buffer->data[x][y].character;
            winbuffer[y][x].Attributes = this->buffer->data[x][y].forecolor | this->buffer->data[x][y].backcolor << 4;
        }
    COORD size = {this->console_size.x, this->console_size.y};
    COORD start = {0, 0};
    SMALL_RECT srect = {0, 0, this->console_size.x, this->console_size.y};
    WriteConsoleOutput(output_handle, (CHAR_INFO*)winbuffer, size, start, &srect);
}
