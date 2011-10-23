#include "Engine.h"

using namespace ConsoleGameEngine;

/*---------------------------*/
/*----------Vector2----------*/
/*---------------------------*/

Vector2::Vector2()
{
    X = 0;
    Y = 0;
}

Vector2::Vector2(byte x, byte y)
{
    X = x;
    Y = y;
}

byte Vector2::operator[](const int i)
{
    switch(i)
    {
    case 0:
        return X;
    case 1:
        return Y;
    default:
        return -1;
    }
}

/*-------------------------*/
/*----------Pixel----------*/
/*-------------------------*/

Pixel::Pixel()
{
    Reset();
}

void Pixel::Reset()
{
    character = ' ';
    forecolor = LightGrey;
    backcolor = Black;
}

/*--------------------------*/
/*----------Sprite----------*/
/*--------------------------*/

Sprite::Sprite(string filename)
{
    //Todo: Esta função deve carregar o sprite do arquivo
    ifstream stream(filename.c_str(), ios_base::binary);
    char temp = 0;
    stream >> size.X >> size.Y;
    AllocData();
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
        {
            stream.get(data[x][y].character = temp);
            stream.get(temp);
            data[x][y].forecolor = (Color)temp;
            stream.get(temp);
            data[x][y].backcolor = (Color)temp;
        }

    stream.close();
    lastClearcolor = Black;
}

Sprite::Sprite(Vector2 sprite_size)
{
    size = sprite_size;
    AllocData();
    lastClearcolor = Black;
}

void Sprite::AllocData()
{
    data = new Pixel*[size.X];
    for(byte b = 0; b < size.X; ++b)
        data[b] = new Pixel[size.Y];
}

Vector2 Sprite::GetSize()
{
    return(size);
}

Sprite::~Sprite()
{
    for(byte b = 0; b < size.X; ++b)
        delete [] data[b];
    delete [] data;
}

bool Sprite::DrawSprite(const Sprite &sprite, const Vector2 &position)
{
    for(register byte x = 0; x < sprite.size.X; ++x)
        for(register byte y = 0; y < sprite.size.Y; ++y)
            if((position.X + x < size.X) && (position.Y + y < size.Y))
                data[position.X + x][position.Y + y] = sprite.data[x][y];

    return true;
}

bool Sprite::DrawSpriteCenter(const Sprite &sprite, const Vector2 &position)
{
    return(DrawSprite(sprite, Vector2(((position.X / 2) - (sprite.size.X / 2)), ((position.Y / 2) - (sprite.size.Y / 2)))));
}

void Sprite::FillBackcolor(Color backcolor)
{
    //TODO: Esta função deve deixar todas as propriedades backcolor do sprite da cor informada
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
            data[x][y].backcolor = backcolor;
}

void Sprite::FillForecolor(Color forecolor)
{
    //TODO: Esta função deve deixar todas as propriedades forecolor do sprite da cor informada
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
            data[x][y].forecolor = forecolor;
}

byte Sprite::DrawText(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    byte len = text.size();
    register byte b;

    if(position.Y >= size.Y)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.X + b) >= size.X)
            return(b);
        data[position.X + b][position.Y].character = text[b];
        if(backcolor != Transparent)
            data[position.X + b][position.Y].backcolor = backcolor;
        data[position.X + b][position.Y].forecolor = forecolor;
    }
    return b;
}

byte Sprite::DrawText_right(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    return(DrawText(text, Vector2((position.X - (text.size() -1)), position.Y), forecolor, backcolor));
}

byte Sprite::DrawTextCenter(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    return(DrawText(text, Vector2(position.X - ((text.size() -1) / 2), position.Y), forecolor, backcolor));
}

byte Sprite::DrawText_vert(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    byte len = text.size();
    register byte b;

    if(position.X >= size.X)
        return 0;

    for(b = 0; b < len; ++b)
    {
        if((position.Y + b) >= size.Y)
            return(b);
        data[position.X][position.Y + b].character = text[b];
        if(backcolor != Transparent)
            data[position.X][position.Y + b].backcolor = backcolor;
        data[position.X][position.Y + b].forecolor = forecolor;
    }
    return b;
}

byte Sprite::DrawTextVertCenter(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    return (DrawText_vert(text, Vector2(position.X, (position.Y / (text.size() -1))), forecolor, backcolor));
}

byte Sprite::DrawTextVertTop(const string text, const Vector2 &position, Color forecolor, Color backcolor)
{
    return (DrawText_vert(text, Vector2(position.X, (position.Y - (text.size() -1))), forecolor, backcolor));
}

void Sprite::Clear()
{
    Clear(Black);
}

void Sprite::Clear(Color backcolor)
{
    lastClearcolor = backcolor;
    for(register byte x = 0; x < size.X; ++x)
        for(register byte y = 0; y < size.Y; ++y)
        {
            data[x][y].Reset();
            data[x][y].backcolor = backcolor;
        }
}

bool Sprite::DoesItFit(Sprite& sprite, Vector2 position)
{
    if(((position.X + sprite.size.X) >= size.X) &&
            ((position.Y + sprite.size.Y) >= size.Y))
        return false;
    else
        return true;
}

void Sprite::Rotate(short int graus)
{
    //Todo: Esta função deve fazer a rotação do sprite
}

void Sprite::Save(string filename)
{
    //DeleteFile(filename.c_str());

    ofstream stream(filename.c_str(), ios_base::out);
    stream << size.X << size.Y;

    byte temp = 0;

    for(byte x = 0; x < size.X; ++x)
    {
        for(byte y = 0; y < size.Y; ++y)
        {
            stream << data[x][y].character;
            temp = (byte)data[x][y].forecolor;
            stream << temp;
            temp = (byte)data[x][y].backcolor;
            stream << temp;
        }
    }

    stream.close();
}

/*--------------------------*/
/*----------Engine----------*/
/*--------------------------*/

void Engine::PreInit()
{
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_handle = GetConsoleWindow();
    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    SetCursorSize(1, false);
    SetWindowTitle("Console Game Engine");
    currentfps = 0;
    buffer = NULL;
    console_size.X = 80;
    console_size.Y = 25;
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

Engine::Engine(string title)
{
    PreInit();

    SetWindowTitle(title);

    PosInit();
}

Engine::Engine(Vector2 position, Vector2 size)
{
    PreInit();

    console_size = size;
    SetWindowPosition(position);

    PosInit();
}

Engine::Engine(Vector2 size)
{
    PreInit();

    console_size = size;

    PosInit();
}

Engine::Engine(string title, Vector2 size)
{
    PreInit();

    SetWindowTitle(title);
    console_size = size;

    PosInit();
}

Engine::Engine(string title, Vector2 position, Vector2 size)
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
    Sprite logo = Sprite(Vector2(buffer->GetSize().X, 14)), blood = Sprite(Vector2(buffer->GetSize().X - 2, buffer->GetSize().Y- 2));
    int lasttick = GetTickCount(), blinktick = GetTickCount();
    bool blink = false;

    std::srand(GetTickCount());

    logo.DrawTextCenter("  ______                       _       ",     Vector2(logo.GetSize().X / 2, 0), LightBlue, White);
    logo.DrawTextCenter(" / _____)                     | |      ",     Vector2(logo.GetSize().X / 2, 1), LightBlue, White);
    logo.DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(logo.GetSize().X / 2, 2), LightBlue, White);
    logo.DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(logo.GetSize().X / 2, 3), LightBlue, White);
    logo.DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(logo.GetSize().X / 2, 4), LightBlue, White);
    logo.DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(logo.GetSize().X / 2, 5), LightBlue, White);

    logo.DrawTextCenter("  ______                      _______             _             ",        Vector2(logo.GetSize().X / 2, 7), LightGreen, White);
    logo.DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(logo.GetSize().X / 2, 8), LightGreen, White);
    logo.DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(logo.GetSize().X / 2, 9), LightGreen, White);
    logo.DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(logo.GetSize().X / 2, 10), LightGreen, White);
    logo.DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(logo.GetSize().X / 2, 11), LightGreen, White);
    logo.DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(logo.GetSize().X / 2, 12), LightGreen, White);
    logo.DrawTextCenter("                                           (_____|              ",        Vector2(logo.GetSize().X / 2, 13), LightGreen, White);

    while(!Keyboard::GetKey(VK_SPACE) || effect < 2)
    {
        if((GetTickCount() - lasttick) > 25)
        {
            lasttick = GetTickCount();

            //blood effect
            static bool bleed = true;
            if(effect > 1 && bleed)
            {
                byte count = 0;
                for(byte x = 0; x < blood.GetSize().X; ++x)
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
                        buffer->data[logo.GetSize().X - 1 - x][row].character = logo.data[logo.GetSize().X - 1 - x][row - 2].character;
                        buffer->data[logo.GetSize().X - 1 - x][row].forecolor = logo.data[logo.GetSize().X - 1 - x][row - 2].forecolor;
                    }
                }
            }

            if(colc < logo.GetSize().X - 6)
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
                            buffer->data[logo.GetSize().X - 1 - x][row].character = logo.data[logo.GetSize().X - 1 - x][row - 2].character;
                            buffer->data[logo.GetSize().X - 1 - x][row].forecolor = logo.data[logo.GetSize().X - 1 - x][row - 2].forecolor;
                        }
                    }
                }

                if(colg < logo.GetSize().X - 6)
                    ++colg;
                else
                    effect = 2;
            }

            for(byte x = 0; x < GetWindowSize().X; ++x)
            {
                for(byte y = 0; y < GetWindowSize().Y; ++y)
                {
                    if(y == 0 || x == 0 || y == GetWindowSize().Y-1 || x == GetWindowSize().X-1)
                    {
                        buffer->data[x][y].character = '°';
                        buffer->data[x][y].forecolor = LightRed;
                    }
                }
            }

            if((GetTickCount() - blinktick) > 1000)
            {
                blinktick = GetTickCount();
                blink = !blink;
            }

            if(effect > 1)
            {
                if(blink)
                {
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().X / 2, 17), Red, Transparent);
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().X / 2, 18), Red, Transparent);
                    buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().X / 2, 18), White, Transparent);
                    buffer->DrawTextCenter("°°°°°°°°°°°°°°°", Vector2(GetWindowSize().X / 2, 19), Red, Transparent);
                }
            }

            buffer->DrawText("Developed by", Vector2(2, GetWindowSize().Y -3), White, Transparent);
            buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(2, GetWindowSize().Y -2), White, Transparent);

            buffer->DrawText_right("Version 0.6",Vector2(GetWindowSize().X-2, GetWindowSize().Y-2), White, Transparent);

            UpdateConsole();
        }
    }

#else

    byte col = 0;

    while(!Keyboard::GetKey(VK_SPACE))
    {

        for(byte x = 0; x < GetWindowSize().X; ++x)
            for(byte y = 0; y < GetWindowSize().Y; ++y)
                if(y == 0 || x == 0 || y == GetWindowSize().Y-1 || x == GetWindowSize().X-1)
                {
                    buffer->data[x][y].character = '*';
                    buffer->data[x][y].forecolor = LightBlue;
                }

        buffer->DrawTextCenter("  ______                       _       ",     Vector2(GetWindowSize().X / 2, 2), White, Black);
        buffer->DrawTextCenter(" / _____)                     | |      ",     Vector2(GetWindowSize().X / 2, 3), White, Black);
        buffer->DrawTextCenter("| /      ___  ____   ___  ___ | | ____ ",     Vector2(GetWindowSize().X / 2, 4), White, Black);
        buffer->DrawTextCenter("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(GetWindowSize().X / 2, 5), White, Black);
        buffer->DrawTextCenter("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(GetWindowSize().X / 2, 6), White, Black);
        buffer->DrawTextCenter(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(GetWindowSize().X / 2, 7), White, Black);

        buffer->DrawTextCenter("  ______                      _______             _             ",        Vector2(GetWindowSize().X / 2, 10), White, Black);
        buffer->DrawTextCenter(" / _____)                    (_______)           (_)            ",        Vector2(GetWindowSize().X / 2, 11), White, Black);
        buffer->DrawTextCenter("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(GetWindowSize().X / 2, 12), White, Black);
        buffer->DrawTextCenter("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(GetWindowSize().X / 2, 13), White, Black);
        buffer->DrawTextCenter("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(GetWindowSize().X / 2, 14), White, Black);
        buffer->DrawTextCenter(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(GetWindowSize().X / 2, 15), White, Black);
        buffer->DrawTextCenter("                                           (_____|              ",        Vector2(GetWindowSize().X / 2, 16), White, Black);

        //effect
        static int lastpp = 0;

        if(((GetTickCount() - lastpp) > 100) && (col < (GetWindowSize().X / 2)))
        {
            lastpp = GetTickCount();
            ++col;
        }

        for(byte y = 2; y < 17; ++y)
            for(byte x = 2; x < GetWindowSize().X; ++x)
            {
                if((col <= (GetWindowSize().X / 2)) && x < col)
                {
                    buffer->data[x][y].forecolor = Green;
                    buffer->data[(GetWindowSize().X-1) - x][y].forecolor = Yellow;
                }
            }

        buffer->data[59][10].forecolor = LightBlue;
        buffer->data[59][11].forecolor = LightBlue;
        buffer->data[58][11].forecolor = LightBlue;
        buffer->data[60][11].forecolor = LightBlue;
        //effect

        buffer->DrawText("Developed by", Vector2(2, GetWindowSize().Y -3), White, Black);
        buffer->DrawText("HwapX->Luis Henrique Barbosa de Lima", Vector2(2, GetWindowSize().Y -2), White, Black);

        buffer->DrawText_right("Version 0.6",Vector2(GetWindowSize().X-2, GetWindowSize().Y-2), White, Black);

        buffer->DrawTextCenter("Press space", Vector2(GetWindowSize().X / 2, 19), White, Black);

        UpdateConsole();
        buffer->Clear();
    }

#endif
}

bool Engine::SetWindowPosition(Vector2 position)
{
    return(SetWindowPos(console_handle, HWND_TOP, position.X, position.Y, NULL, NULL, SWP_NOSIZE));
}

Engine::~Engine()
{
    delete buffer;
}

bool Engine::SetWindowSize(Vector2 size)
{
    //COORD coord = {size.X, size.Y};
    //return(SetConsoleScreenBufferSize(output_handle, coord));
    SMALL_RECT displayarea;

    displayarea.Top = 0;
    displayarea.Left = 0;
    displayarea.Bottom = size.Y-1;
    displayarea.Right = size.X-1;

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
    return (Vector2(coninfo.dwSize.X, coninfo.dwSize.Y));*/
    return(console_size);
}

Vector2 Engine::GetScreenResolution()
{
    Vector2 temp;
    temp.X = GetSystemMetrics(SM_CXSCREEN);
    temp.Y = GetSystemMetrics(SM_CYSCREEN);
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

bool Engine::SetTextColor (Color forecolor, Color backcolor)
{
    return (SetConsoleTextAttribute (output_handle, forecolor | backcolor << 4) == TRUE);
}

bool Engine::SetCursorPosition(Vector2 position)
{
    COORD coord = {position.X, position.Y};
    return (SetConsoleCursorPosition(output_handle, coord) == TRUE);
}

bool Engine::SetWindowTitle(string title)
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
    CHAR_INFO winbuffer[console_size.Y][console_size.X];

    static short int fps = 0;
    static int lasttick = 0;

    if((GetTickCount() - lasttick) > 1000)
    {
        lasttick = GetTickCount();
        currentfps = fps;
        fps = 0;
    }
    fps++;

    for(register byte x = 0; x < console_size.X; ++x)
        for(register byte y = 0; y < console_size.Y; ++y)
        {
            winbuffer[y][x].Char.AsciiChar = buffer->data[x][y].character;
            if(buffer->data[x][y].backcolor == ClearColor)
            {
                //FIX: Rever, por algum motivo não esta funcionando
                winbuffer[y][x].Attributes = buffer->data[x][y].forecolor | buffer->lastClearcolor << 4;
            }
            if(buffer->data[x][y].backcolor == Transparent)
            {
                //TODO:Este codigo esta gastando muito processamento e é possivel otimizalo/
                //FIX:Codigo com problema
                COORD coord = {y, x};
                WORD attr;
                DWORD trash;
                ReadConsoleOutputAttribute(output_handle, &attr, sizeof(WORD), coord, &trash);
                winbuffer[y][x].Attributes = attr;
            }
            else
                winbuffer[y][x].Attributes = buffer->data[x][y].forecolor | buffer->data[x][y].backcolor << 4;
        }
    COORD size = {console_size.X, console_size.Y};
    COORD start = {0, 0};
    SMALL_RECT srect = {0, 0, console_size.X, console_size.Y};
    WriteConsoleOutput(output_handle, (CHAR_INFO*)winbuffer, size, start, &srect);
}

/*----------------------------*/
/*----------Keyboard----------*/
/*----------------------------*/

bool Keyboard::GetKey(int key)
{
    return(GetAsyncKeyState(key) == -32767);
}

bool Keyboard::GetKey_down(int key)
{
    return((GetAsyncKeyState(key) == -32768));
}

byte Keyboard::GetKey()
{
    //for(char b = 32;b < 127;b++)
    for(byte b = 1; b < 256; b++)
        if(GetKey(b))
            return b;
    return(0);
}

byte Keyboard::GetNextKey()
{
    byte key = 0;
    do
    {
        key = GetKey();
    }
    while(!key);
    return(key);
}

/*-------------------------*/
/*----------Sound----------*/
/*-------------------------*/

Sound::Sound(string filename)
{
    filepath = filename;
}

bool Sound::Play()
{
    return(PlaySound(filepath));
}

bool Sound::PlaySound(string filename)
{
    filename = "play " + filename;
    //return(mciSendString(filename.c_str(), NULL, NULL, NULL) << 4);
    return true;
}

bool Sound::Stop()
{
    return(StopSound(filepath));
}

bool Sound::StopSound(string filename)
{
    filename = "stop " + filename;
    //return(mciSendString(filename.c_str(), NULL, NULL, NULL) << 4);
    return true;
}

//Codigos uteis no futuro
//restaura stdin
/*
            HANDLE old = GetStdHandle(STD_INPUT_HANDLE);
            SetStdHandle(STD_INPUT_HANDLE, CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL));
*/
