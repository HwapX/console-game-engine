#include "Engine.h"

using namespace Console_Engine;

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
    reset();
}

void Pixel::reset()
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
    alloc_data();
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
        {
            stream.get(data[x][y].character);
            stream.get(temp);
            data[x][y].forecolor = (Color)temp;
            stream.get(temp);
            data[x][y].backcolor = (Color)temp;
        }

    stream.close();
    lastclearcolor = Black;
}

Sprite::Sprite(Vector2 sprite_size)
{
    size = sprite_size;
    alloc_data();
    lastclearcolor = Black;
}

void Sprite::alloc_data()
{
    data = new Pixel*[size.X];
    for(byte b = 0; b < size.X; ++b)
        data[b] = new Pixel[size.Y];
}

Sprite::~Sprite()
{
    for(byte b = 0; b < size.X; ++b)
        delete [] data[b];
    delete [] data;
}

bool Sprite::draw_sprite(const Sprite &sprite, const Vector2 position)
{
    for(register byte x = 0; x < sprite.size.X; ++x)
        for(register byte y = 0; y < sprite.size.Y; ++y)
            if((position.X + x < size.X) && (position.Y + y < size.Y))
                data[position.X + x][position.Y + y] = sprite.data[x][y];

    return true;
}

bool Sprite::draw_sprite_center(const Sprite &sprite, const Vector2 position)
{
    return(draw_sprite(sprite, Vector2(((position.X / 2) - (sprite.size.X / 2)), ((position.Y / 2) - (sprite.size.Y / 2)))));
}

void Sprite::fill_backcolor(Color backcolor)
{
    //TODO: Esta função deve deixar todas as propriedades backcolor do sprite da cor informada
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
            data[x][y].backcolor = backcolor;
}

void Sprite::fill_forecolor(Color forecolor)
{
    //TODO: Esta função deve deixar todas as propriedades forecolor do sprite da cor informada
    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
            data[x][y].forecolor = forecolor;
}

byte Sprite::draw_text(const string text, const Vector2 position, Color forecolor, Color backcolor)
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
        data[position.X + b][position.Y].backcolor = backcolor;
        data[position.X + b][position.Y].forecolor = forecolor;
    }
    return b;
}

byte Sprite::draw_text_right(const string text, const Vector2 position, Color forecolor, Color backcolor)
{
    return(draw_text(text, Vector2((position.X - (text.size() -1)), position.Y), forecolor, backcolor));
}

byte Sprite::draw_text_center(const string text, const Vector2 position, Color forecolor, Color backcolor)
{
    return(draw_text(text, Vector2(position.X - ((text.size() -1) / 2), position.Y), forecolor, backcolor));
}

byte Sprite::draw_text_vert(const string text, const Vector2 position, Color forecolor, Color backcolor)
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
        data[position.X][position.Y + b].backcolor = backcolor;
        data[position.X][position.Y + b].forecolor = forecolor;
    }
    return b;
}

byte Sprite::draw_text_vert_center(const string text, const Vector2 position, Color forecolor, Color backcolor)
{
    return (draw_text_vert(text, Vector2(position.X, (position.Y / (text.size() -1))), forecolor, backcolor));
}

byte Sprite::draw_text_vert_top(const string text, const Vector2 position, Color forecolor, Color backcolor)
{
    return (draw_text_vert(text, Vector2(position.X, (position.Y - (text.size() -1))), forecolor, backcolor));
}

void Sprite::clear()
{
    clear(Black);
}

void Sprite::clear(Color backcolor)
{
    lastclearcolor = backcolor;
    for(register byte x = 0; x < size.X; ++x)
        for(register byte y = 0; y < size.Y; ++y)
        {
            data[x][y].reset();
            data[x][y].backcolor = backcolor;
        }
}

bool Sprite::does_itfit(Sprite& sprite, Vector2 position)
{
    if(((position.X + sprite.size.X) >= size.X) &&
            ((position.Y + sprite.size.Y) >= size.Y))
        return false;
    else
        return true;
}

void Sprite::rotate(short int graus)
{
    //Todo: Esta função deve fazer a rotação do sprite
}

void Sprite::save(string filename)
{

    DeleteFile(filename.c_str());

    ofstream stream(filename.c_str(), ios_base::out);
    stream << size.X << size.Y;

    char temp = 0;

    for(byte x = 0; x < size.X; ++x)
        for(byte y = 0; y < size.Y; ++y)
        {
            stream << data[x][y].character;
            temp = data[x][y].forecolor;
            stream << temp;
            temp = data[x][y].backcolor;
            stream << temp;
        }

    stream.close();
}

/*--------------------------*/
/*----------Engine----------*/
/*--------------------------*/

void Engine::pre_initialize()
{
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_handle = GetConsoleWindow();
    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    set_cursor_size(1, false);
    set_title("Console Game Engine");
    currentfps = 0;
    buffer = NULL;
    console_size.X = 80;
    console_size.Y = 25;
}

void Engine::pos_initialize()
{
    set_size(console_size);
    display_splash();
}

Engine::Engine()
{
    pre_initialize();

    pos_initialize();
}

Engine::Engine(string title)
{
    pre_initialize();

    set_title(title);

    pos_initialize();
}

Engine::Engine(Vector2 position, Vector2 size)
{
    pre_initialize();

    console_size = size;
    set_position(position);

    pos_initialize();
}

Engine::Engine(Vector2 size)
{
    pre_initialize();

    console_size = size;

    pos_initialize();
}

Engine::Engine(string title, Vector2 size)
{
    pre_initialize();

    set_title(title);
    console_size = size;

    pos_initialize();
}

Engine::Engine(string title, Vector2 position, Vector2 size)
{
    pre_initialize();

    set_title(title);
    console_size = size;
    set_position(position);

    pos_initialize();
}

void Engine::display_splash()
{
    //TODO: Refazer função, mostrar os creditos, logo, versão e nome dos desenvolvedores

    byte col = 0;

    while(!Keyboard::get_key(VK_SPACE))
    {

        for(byte x = 0; x < get_size().X; ++x)
            for(byte y = 0; y < get_size().Y; ++y)
                if(y == 0 || x == 0 || y == get_size().Y-1 || x == get_size().X-1)
                {
                    buffer->data[x][y].character = '*';
                    buffer->data[x][y].forecolor = LightBlue;
                }

        buffer->draw_text_center("  ______                       _       ",     Vector2(get_size().X / 2, 2), White, Black);
        buffer->draw_text_center(" / _____)                     | |      ",     Vector2(get_size().X / 2, 3), White, Black);
        buffer->draw_text_center("| /      ___  ____   ___  ___ | | ____ ",     Vector2(get_size().X / 2, 4), White, Black);
        buffer->draw_text_center("| |     / _ \\|  _ \\ /___)/ _ \\| |/ _  )",  Vector2(get_size().X / 2, 5), White, Black);
        buffer->draw_text_center("| \\____| |_| | | | |___ | |_| | ( (/ / ",    Vector2(get_size().X / 2, 6), White, Black);
        buffer->draw_text_center(" \\______)___/|_| |_(___/ \\___/|_|\\____)",  Vector2(get_size().X / 2, 7), White, Black);

        buffer->draw_text_center("  ______                      _______             _             ",        Vector2(get_size().X / 2, 10), White, Black);
        buffer->draw_text_center(" / _____)                    (_______)           (_)            ",        Vector2(get_size().X / 2, 11), White, Black);
        buffer->draw_text_center("| /  ___  ____ ____   ____    _____   ____   ____ _ ____   ____ ",        Vector2(get_size().X / 2, 12), White, Black);
        buffer->draw_text_center("| | (___)/ _  |    \\ / _  )  |  ___) |  _ \\ / _  | |  _ \\ / _  )",     Vector2(get_size().X / 2, 13), White, Black);
        buffer->draw_text_center("| \\____/( ( | | | | ( (/ /   | |_____| | | ( ( | | | | | ( (/ / ",       Vector2(get_size().X / 2, 14), White, Black);
        buffer->draw_text_center(" \\_____/ \\_||_|_|_|_|\\____)  |_______)_| |_|\\_|| |_|_| |_|\\____)",   Vector2(get_size().X / 2, 15), White, Black);
        buffer->draw_text_center("                                           (_____|              ",        Vector2(get_size().X / 2, 16), White, Black);

        //effect
        static int lastpp;
        if(((GetTickCount() - lastpp) > 100) && (col < (get_size().X / 2)))
        {
            lastpp = GetTickCount();
            ++col;
        }
        for(byte y = 2; y < 17; ++y)
            for(byte x = 2; x < get_size().X; ++x)
            {
                if((col <= (get_size().X / 2)) && x < col)
                {
                    buffer->data[x][y].forecolor = Green;
                    buffer->data[(get_size().X-1) - x][y].forecolor = Yellow;
                }
            }

        buffer->data[59][10].forecolor = LightBlue;
        buffer->data[59][11].forecolor = LightBlue;
        buffer->data[58][11].forecolor = LightBlue;
        buffer->data[60][11].forecolor = LightBlue;
        //effect

        buffer->draw_text("Developed by", Vector2(2, 21), White, Black);
        buffer->draw_text("HwapX->Luis Henrique Barbosa de Lima", Vector2(2, 22), White, Black);
        buffer->draw_text("PBassut->Patrick Bassut", Vector2(2, 23), White, Black);

        buffer->draw_text_right("Version 0.6",Vector2(get_size().X-2, get_size().Y-2), White, Black);

        buffer->draw_text_center("Press space", Vector2(get_size().X / 2, 19), White, Black);

        update_console();
        buffer->clear();
    }

}

bool Engine::set_position(Vector2 position)
{
    return(SetWindowPos(console_handle, HWND_TOP, position.X, position.Y, NULL, NULL, SWP_NOSIZE));
}

Engine::~Engine()
{
    delete buffer;
}

bool Engine::set_size(Vector2 size)
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

Vector2 Engine::get_size()
{
    /*CONSOLE_SCREEN_BUFFER_INFO coninfo;

    GetConsoleScreenBufferInfo (output_handle, &coninfo);
    return (Vector2(coninfo.dwSize.X, coninfo.dwSize.Y));*/
    return(console_size);
}

Vector2 Engine::get_screen_resolution(){
    Vector2 temp;
    temp.X = GetSystemMetrics(SM_CXSCREEN);
    temp.Y = GetSystemMetrics(SM_CYSCREEN);
    return temp;
}

bool Engine::focus(){
    if(GetForegroundWindow() == console_handle)
        return(true);
    else
        return(false);
}

void Engine::wait_focus(){
    while(!focus()){};
}

bool Engine::set_text_color (Color forecolor, Color backcolor)
{
    return (SetConsoleTextAttribute (output_handle, forecolor | backcolor << 4) == TRUE);
}

bool Engine::set_cursor_pos(Vector2 position)
{
    COORD coord = {position.X, position.Y};
    return (SetConsoleCursorPosition(output_handle, coord) == TRUE);
}

bool Engine::set_title(string title)
{
    return SetConsoleTitle ((LPCSTR)title.c_str());
}

bool Engine::set_cursor_size(byte size, bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo = { size, visible };
    return (SetConsoleCursorInfo (output_handle, &cursorinfo) == TRUE);
}

short int Engine::get_fps()
{
    return(currentfps);
}

void Engine::update_console()
{
    set_cursor_pos(Vector2(0, 0));
    //TODO: guardar a posição do cursor anterior e restaurar depois
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
                winbuffer[y][x].Attributes = buffer->data[x][y].forecolor | buffer->lastclearcolor << 4;
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

bool Keyboard::get_key(int key)
{
    return(GetAsyncKeyState(key) == -32767);
}

bool Keyboard::get_key_down(int key)
{
    return((GetAsyncKeyState(key) == -32768));
}

byte Keyboard::get_key()
{
    //for(char b = 32;b < 127;b++)
    for(byte b = 1; b < 256; b++)
        if(get_key(b))
            return b;
    return(0);
}

byte Keyboard::get_next_key()
{
    byte key = 0;
    do
    {
        key = get_key();
    }
    while(!key);
    return(key);
}

char Keyboard::get_next_char()
{
//for(char b = 32;b < 127;b++)
    byte key;
    do
    {
        key = get_next_key();
        if(!get_key(VK_SHIFT))
            key = tolower(key);

    }
    while(key < 30 && key > 0x6F);
    return(key);
}

string Keyboard::get_string()
{
    return(get_string(254));
}

string Keyboard::get_string(byte maxsize)
{
    string temp;
    char key;
    {
        key = get_next_char();
        if(key == VK_EXECUTE)
            return temp;
        temp+= key;

    }
    while((key != VK_ESCAPE) || (temp.size() > maxsize));

    return(temp);
}

int Keyboard::get_numbers(byte maxdigits)
{

}

int get_numbers(int maxnumber)
{

}

/*-------------------------*/
/*----------Sound----------*/
/*-------------------------*/

Sound::Sound(string filename)
{
    filepath = filename;
}

bool Sound::play()
{
    return(play_sound(filepath));
}

bool Sound::play_sound(string filename)
{
    filename = "play " + filename;
    //return(mciSendString(filename.c_str(), NULL, NULL, NULL) << 4);
    return true;
}

bool Sound::stop()
{
    return(stop_sound(filepath));
}

bool Sound::stop_sound(string filename)
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
