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
    //TODO: Refazer função, mostrar os creditos, logo, versão e nome dos desenvolvedores

#ifdef NEWLOGO
    byte colc = 0, colg = 0, effect = 0;
    Sprite logo(Vector2(buffer->GetSize().x, 14)), blood(Vector2(buffer->GetSize().x - 2, buffer->GetSize().Y- 2));
    int lasttick = GetTick(), blinktick = GetTick();
    bool blink = false;

    std::srand(GetTick());

    logo.DrawTextCenter("  ______                       _       ",     Vector2(logo.GetSize().x / 2, 0), LightBlue, White);
    logo.DrawTextCenter(" / _____)                     | |      ",     Vector2(logo.GetSize().x / 2, 1), LightBlue, White);
    logo.DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(logo.GetSize().x / 2, 2), LightBlue, White);
    logo.DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(logo.GetSize().x / 2, 3), LightBlue, White);
    logo.DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(logo.GetSize().x / 2, 4), LightBlue, White);
    logo.DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(logo.GetSize().x / 2, 5), LightBlue, White);

    logo.DrawTextCenter("  ______                      _______             _             ",        Vector2(logo.GetSize().x / 2, 7), LightGreen, White);
    logo.DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(logo.GetSize().x / 2, 8), LightGreen, White);
    logo.DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(logo.GetSize().x / 2, 9), LightGreen, White);
    logo.DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(logo.GetSize().x / 2, 10), LightGreen, White);
    logo.DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(logo.GetSize().x / 2, 11), LightGreen, White);
    logo.DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(logo.GetSize().x / 2, 12), LightGreen, White);
    logo.DrawTextCenter("                                           (_____|              ",        Vector2(logo.GetSize().x / 2, 13), LightGreen, White);

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
                for(byte x = 0; x < blood.GetSize().x; ++x)
                {
                    for(byte y = 0; y < blood.GetSize().Y; ++y)
                    {
                        if(blood.data[x][y].backcolor != LightRed)
                        {
                            if((std::rand() % 101) == 0)
                            {
                                blood.data[x][y].backcolor = LightRed;
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
            for(byte row = 2; row < 9; ++row)
            {
                for(byte x = 20; x < colc; ++x)
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
                for(byte row = 9; row < 16; ++row)
                {
                    for(byte x = 6; x < colg; ++x)
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

            for(byte x = 0; x < GetWindowSize().x; ++x)
            {
                for(byte y = 0; y < GetWindowSize().y; ++y)
                {
                    if(y == 0 || x == 0 || y == GetWindowSize().y-1 || x == GetWindowSize().x-1)
                    {
                        buffer->data[x][y].character = '°';
                        buffer->data[x][y].forecolor = LightRed;
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
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().x / 2, 17), Red, Transparent);
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().x / 2, 18), Red, Transparent);
                    buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().x / 2, 18), White, Transparent);
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().x / 2, 19), Red, Transparent);
                }
            }

            buffer->DrawText("Developed by", Vector2(2, GetWindowSize().y -3), White, Transparent);
            buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(2, GetWindowSize().y -2), White, Transparent);

            buffer->DrawText_right("Version 0.6",Vector2(GetWindowSize().x-2, GetWindowSize().y-2), White, Transparent);

            UpdateConsole();
        }
    }

#else

    byte col = 0;

    while(!Keyboard::GetKey(VK_SPACE))
    {

        for(byte x = 0; x < GetWindowSize().x; ++x)
            for(byte y = 0; y < GetWindowSize().y; ++y)
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

        for(byte y = 2; y < 17; ++y)
            for(byte x = 2; x < GetWindowSize().x; ++x)
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

        buffer->DrawText("Developed by", Vector2(2, GetWindowSize().y -3), Colors::White, Colors::Black);
        buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(2, GetWindowSize().y -2), Colors::White, Colors::Black);

        buffer->DrawTextRight("Version 0.6",Vector2(GetWindowSize().x-2, GetWindowSize().y-2), Colors::White, Colors::Black);

        buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().x / 2, 19), Colors::White, Colors::Black);

        UpdateConsole();
        buffer->Clear();
    }

#endif
}

void Engine::ShowError(const string &text)
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
    //COORD coord = {size.x, size.y};
    //return(SetConsoleScreenBufferSize(output_handle, coord));
    SMALL_RECT displayarea;

    displayarea.Top = 0;
    displayarea.Left = 0;
    displayarea.Bottom = size.y-1;
    displayarea.Right = size.x-1;

    //TODO: verificar o retorno antes de mudar o valor
    console_size = size;

    if(buffer != NULL)
        delete buffer;
    buffer = new Sprite(console_size);

    return(SetConsoleWindowInfo(output_handle, TRUE, &displayarea));
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
    return(currentfps);
}

void Engine::UpdateConsole()
{
    SetCursorPosition(Vector2(0, 0));
    //TODO: fazer backup da posição anterior do cursor e restaurar novamente no final da função
    CHAR_INFO winbuffer[console_size.y][console_size.x];

    static short int fps = 0;
    static int lasttick = 0;

    if((GetTick() - lasttick) > 1000)
    {
        lasttick = GetTick();
        currentfps = fps;
        fps = 0;
    }
    fps++;

    for(register byte x = 0; x < console_size.x; ++x)
        for(register byte y = 0; y < console_size.y; ++y)
        {
            winbuffer[y][x].Char.AsciiChar = buffer->data[x][y].character;
            winbuffer[y][x].Attributes = buffer->data[x][y].forecolor | buffer->data[x][y].backcolor << 4;
        }
    COORD size = {console_size.x, console_size.y};
    COORD start = {0, 0};
    SMALL_RECT srect = {0, 0, console_size.x, console_size.y};
    WriteConsoleOutput(output_handle, (CHAR_INFO*)winbuffer, size, start, &srect);
}
