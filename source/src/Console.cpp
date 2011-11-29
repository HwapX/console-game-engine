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
    out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    handle = GetConsoleWindow();
    //CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    this->SetCursorSize(1, false);
    this->SetTitle("Console Game Engine");
}

void Console::PosInit()
{
    this->Resize(size);
    this->SetPosition(Vector2(this->ScreenResolution().x / 2 - this->WindowSize().x / 2, this->ScreenResolution().y / 2 - this->WindowSize().y / 2));
    this->ShowLogo();
}

Console::Console() : Sprite::Sprite(Vector2(80, 40))
{
    PreInit();
    PosInit();
}

Console::Console(const string &title) : Sprite::Sprite(Vector2(80, 40))
{
    this->PreInit();

    this->SetTitle(title);

    this->PosInit();
}

Console::Console(const Vector2 &position, const Vector2 &size) : Sprite::Sprite(size)
{
    this->PreInit();

    this->SetPosition(position);

    this->PosInit();
}

Console::Console(const Vector2 &size) : Sprite::Sprite(size)
{
    this->PreInit();

    this->PosInit();
}

Console::Console(const string &title, const Vector2 &size) : Sprite::Sprite(size)
{
    this->PreInit();

    this->SetTitle(title);

    this->PosInit();
}

Console::Console(const string &title, const Vector2 &position, const Vector2 &size) : Sprite::Sprite(size)
{
    this->PreInit();

    this->SetTitle(title);
    this->SetPosition(position);

    this->PosInit();
}

void Console::ShowLogo()
{
#define BORDER_CHAR 0xB0

    uint8_t colc = 0, colg = 0, effect = 0;
    Sprite logo(Vector2(this->GetSize().x, 14)), blood(Vector2(this->GetSize().x - 2, this->GetSize().y- 2));
    uint32_t lasttick = this->GetTick();

    Vector2 shot, nave_pos(this->GetSize().x / 2 - 3, this->GetSize().y - 8);
    Sprite nave(Vector2(5, 3));

    shot.y = -1;

    nave.Clear(Color::Transparent, Color::White, ' ');
    nave(1, 1).character = '/';
    nave(2, 0).character = 30;
    nave(3, 1).character = '\\';
    nave(0, 2).character = '(';
    nave(1, 2).character = '_';
    nave(2, 2).character = '_';
    nave(3, 2).character = '_';
    nave(4, 2).character = ')';

    logo.Clear(Color::Black, ' ');

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

#ifdef _DEBUG
    while(!Input::GetKey(Key::Escape))
#else
    while(!Input::GetKey(Key::Escape) || effect < 2)
#endif
    {
        if((GetTick() - lasttick) > 25)
        {
            this->Clear();
            if(Input::GetKey(Key::Left))
            {
                --nave_pos.x;
            }
            else if(Input::GetKey(Key::Right))
            {
                ++nave_pos.x;
            }
            if(Input::GetKey(Key::Space) && shot.y == -1)
            {
                shot.x = nave_pos.x + 2;
                shot.y = nave_pos.y;
            }

            lasttick = GetTick();

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

            if(shot.y != -1)
            {
                --shot.y;

                if(this->GetPixel(shot).character != ' ')
                {
                    logo(Vector2(shot.x, shot.y - 2)).character = ' ';
                    shot.y = -1;
                }
                else
                {
                    this->DrawText("\x1E", shot, Color::Red, Color::Transparent);
                }
            }

            if(shot.y < 2)
            {
                shot.y = -1;
            }

            this->DrawSprite(nave, nave_pos);
            this->DrawText("Developed by", Vector2(1, GetSize().y -3), Color::White, Color::Transparent);
            this->DrawText("HwapX->Luis Henrique", Vector2(1, GetSize().y -2), Color::White, Color::Transparent);

            this->DrawTextRight(VERSION,Vector2(GetSize().x-2, GetSize().y-2), Color::White, Color::Transparent);

            this->Update();
        }
    }
    Input::ClearKeyBuffer();
}

void Console::ShowError(const string &text, const bool close)
{
//    this->Resize(Vector2(80,25));
//    while(!Input::GetKey(VK_SPACE))
//    {
//        this->Clear();
//        this->DrawText(" ____ ____ ____ ____ ____ ", Vector2(0, 0), Color::White, Color::Black);
//        this->DrawText("||E |||r |||r |||o |||r ||", Vector2(0, 1), Color::White, Color::Black);
//        this->DrawText("||__|||__|||__|||__|||__||", Vector2(0, 2), Color::White, Color::Black);
//        this->DrawText("|/__\\|/__\\|/__\\|/__\\|/__\\|", Vector2(0, 3), Color::White, Color::Black);
//        this->DrawTextCenter(text, Vector2(this->GetSize().x / 2, 15), Color::Red, Color::Black);
//        this->DrawTextRight(close?"Press space to close application":"Press space to continue", Vector2(this->GetSize().x -1, this->GetSize().y -1), Color::White, Color::Black);
//        this->Update();
//        this->Clear();
//    }
    cout << string(80 * 80, ' ');
    cout << " ____ ____ ____ ____ ____ " << endl;
    cout << "||E |||r |||r |||o |||r ||" << endl;
    cout << "||__|||__|||__|||__|||__||" << endl;
    cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|" << endl;
    cout << endl << endl << endl << text.c_str() << endl;
    cout << endl << endl << (close?"Press any key to close application":"Press any key to continue") << endl;

    cin.get();

    if(close)
        exit(1);
}


bool Console::InputDialog(const string &title, const string &text, string &result, uint8_t number_base)
{
    bool cancel = false, blink = true;
    uint32_t blink_tick = this->GetTick();
    Sprite buffer_bkp(*this);

    result.clear();
    Input::ClearKeyBuffer();

    while(!Input::GetKey(Key::Enter))
    {
        switch(Input::GetKey())
        {
        case Key::Escape:
            return(false);
            break;
        case Key::Backspace:
            if(result.size() > 0)
            {
                result.erase(result.size() -1);
            }
            break;
        case Key::Left:
            cancel = false;
            break;
        case Key::Right:
            cancel = true;
            break;
        default:
            char last_char = Input::GetChar();
            if(last_char != 0 && result.size() < 39)
            {
                switch(number_base)
                {
                case 0:
                    result+= last_char;
                    break;
                case 10:
                    if((last_char >= '0' && last_char <= '9') || (last_char == '-' || last_char == '+'))
                    {
                        result+= last_char;
                    }
                    break;
                }
            }
            break;
        }

        if(this->GetTick() - blink_tick > 500)
        {
            blink_tick = this->GetTick();
            blink = !blink;
        }

        this->DrawTextCenter("ษออออออออออออออออออออออออออออออออออออออออป", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -3), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -2), Color::Black, Color::White);
        this->DrawTextCenter(title                                       , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -2), Color::Black, Color::White);
        this->DrawTextCenter("ฬออออออออออออออออออออออออออออออออออออออออน", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 -1), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2), Color::Black, Color::White);
        this->DrawTextCenter(text                                        , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2), Color::Black, Color::White);
        this->DrawTextCenter("ฬออออออออออออออออออออออออออออออออออออออออน", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +1), Color::Black, Color::White);
        this->DrawTextCenter("บ                                        บ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +2), Color::Black, Color::White);
        this->DrawTextCenter(result                                      , Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +2), Color::Black, Color::White);
        this->DrawTextCenter(TEXT_CURSOR                                 , Vector2(this->GetSize().x / 2 + result.size() / 2, this->GetSize().y / 2 +2), blink?Color::Black:Color::White, Color::White);
        this->DrawTextCenter("ศออออออออออออออออออออออออออออออออออออออออผ", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +3), Color::Black, Color::White);


        this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 +9, this->GetSize().y / 2 +5), Color::Black, Color::White);
        this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 +9, this->GetSize().y / 2 +6), Color::Black, Color::White);
        this->DrawTextCenter( "Cancel"  , Vector2(this->GetSize().x / 2 +9, this->GetSize().y / 2 +6), cancel?Color::White:Color::Black, cancel?Color::Black:Color::White);
        this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 +9, this->GetSize().y / 2 +7), Color::Black, Color::White);
        this->DrawTextCenter("\x1B    \x1A", Vector2(this->GetSize().x / 2-1, this->GetSize().y / 2 +6), Color::Black, Color::White);

        this->DrawTextCenter("ษออออออออป", Vector2(this->GetSize().x / 2 -11, this->GetSize().y / 2 +5), Color::Black, Color::White);
        this->DrawTextCenter("บ        บ", Vector2(this->GetSize().x / 2 -11, this->GetSize().y / 2 +6), Color::Black, Color::White);
        this->DrawTextCenter( "  Ok  "  , Vector2(this->GetSize().x / 2 -11, this->GetSize().y / 2 +6), cancel?Color::Black:Color::White, cancel?Color::White:Color::Black);
        this->DrawTextCenter("ศออออออออผ", Vector2(this->GetSize().x / 2 -11, this->GetSize().y / 2 +7), Color::Black, Color::White);

        this->Update();
    }

    this->DrawSprite(buffer_bkp, Vector2(0, 0));

    return(!cancel && !result.empty());
}

bool Console::InputDialog(const string title, const string text, int32_t &result)
{
    bool ret = false;
    string text_result;
    ret = this->InputDialog(title, text, text_result, 10);
    result = atoi(text_result.c_str());
    return(ret);
}

bool Console::MsgDialog(const string &title, const string &text, const bool only_ok, const bool option)
{
    bool cancel = !only_ok?!option:false;
    Sprite buffer_bkp(*this);

    Input::ClearKeyBuffer();

    while(!Input::GetKey(Key::Enter))
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
            switch(Input::GetKey())
            {
            case Key::Left:
                cancel = false;
                break;
            case Key::Right:
                cancel = true;
                break;
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
    }

    this->DrawSprite(buffer_bkp, Vector2(0, 0));
    return(!cancel);
}

void Console::ShowDebugInfo()
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

    if(SetConsoleScreenBufferSize(out_handle, coord))
    {
        if(SetConsoleWindowInfo(out_handle, TRUE, &displayarea))
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
    return (SetConsoleTextAttribute (out_handle, forecolor | backcolor << 4) == TRUE);
}

bool Console::SetCursorPosition(Vector2 position)
{
    COORD coord = {position.x, position.y};
    return (SetConsoleCursorPosition(out_handle, coord) == TRUE);
}

bool Console::SetTitle(const string &title)
{
    return SetConsoleTitle ((LPCSTR)title.c_str());
}

bool Console::SetCursorSize(uint8_t new_size, bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo = { new_size, visible };
    return (SetConsoleCursorInfo (this->out_handle, &cursorinfo) == TRUE);
}

Vector2 Console::WindowSize()
{
    RECT rect;
    GetWindowRect(this->handle, &rect);
    return(Vector2(rect.right - rect.left, rect.bottom - rect.top));
}

Vector2 Console::WindowPosition()
{
    RECT rect;
    GetWindowRect(this->handle, &rect);
    return(Vector2(rect.left, rect.top));
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
    WriteConsoleOutput(out_handle, (CHAR_INFO*)winbuffer, size, start, &srect);

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
    this->ProcessEvents();
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
