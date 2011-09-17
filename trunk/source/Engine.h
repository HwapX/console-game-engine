#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <fstream>

/*Sobre escreve a versão informada em windows.h*/
#define WINVER 0x0501
#include <windows.h>
/*---------------------------------------------*/

using namespace std;

namespace Console_Engine
{
/**
*A enum with all console colors
*enumerate all suported console colors with
*this enum have two more colors(ClearColor, Transparent) used internaly on engine
*/
enum Color
{
    Black       = 0,
    b        = FOREGROUND_INTENSITY,
    LightGrey   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    White       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    Blue        = FOREGROUND_BLUE,
    Green       = FOREGROUND_GREEN,
    Cyan        = FOREGROUND_GREEN | FOREGROUND_BLUE,
    Red         = FOREGROUND_RED,
    Purple      = FOREGROUND_RED   | FOREGROUND_BLUE,
    LightBlue   = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LightCyan   = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightRed    = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    LightPurple = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    Orange      = FOREGROUND_RED   | FOREGROUND_GREEN,
    Yellow      = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    ClearColor  = 0x00FFFFFF,
    Transparent = 0xFFFFFFFF,
};

/**
*????
*/

class Vector2
{
public:
    byte X, Y;

    Vector2();
    Vector2(byte x, byte y);
    byte operator[](const int i);
};

/**
*A representation of a pixel on console
*This class represent a cell on console screen and store all attributes of this
*/
class Pixel
{
public:
    /**
    *this represent the character displayed
    */
    char character;
    /**
    *this represent the foreground color(font color)
    */
    Color forecolor;
    /**
    *this represent the background color
    */
    Color backcolor;
    /**
    *the constructor
    */
    Pixel();
    /**
    *this function reset the pixel to default values
    */
    void reset();
};

/**
*Represent a image on engine
*?
*/
class Sprite
{
private:
    void alloc_data();
public:
    /**
    *last color with the clear function is called.
    */
    byte lastclearcolor;
    /**
    *deixar essa variavel privada futuramente e criar uma função para pegar o valor dela
    */
    Vector2 size;
    /**
    *a two-dimensional matrix of pixel, that represent all pixels of sprite.
    */
    Pixel** data;
    /**
    *load a sprite from file.
    *@param filename path of file to load.
    */
    Sprite(string filename);
    /**
    *create a sprite with informed size.
    */
    Sprite(Vector2 sprite_size);
    ~Sprite();

    /**
    *this function draw a sprite on this sprite
    *@param sprite the sprite to draw
    *@param position the position to draw
    *@return return true if the draw as succeeded or false if fail
    */
    bool draw_sprite(const Sprite &sprite, const Vector2 position);
    /**
    *this function draw a sprite on center of relative position informed.
    *@param sprite the sprite to draw
    *@param position the position to draw
    *@return return true if the draw as succeeded or false if fail
    *@see draw_sprite
    */
    bool draw_sprite_center(const Sprite &sprite, const Vector2 position);
    /**
    *Draw a text
    *this function draw a text on position informed, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_center
    *@see draw_text_right
    *@see draw_text_vert
    *@see draw_text_vert_top
    *@see draw_text_vert_center
    */
    byte draw_text(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *Draw a text
    *this function draw a vectical text on informed position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_center
    *@see draw_text_right
    *@see draw_text_vert_top
    *@see draw_text_vert_center
    *@see draw_text
    */
    byte draw_text_vert(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *Draw a text
    *this function draw a text on right of position informed, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_center
    *@see draw_text_vert
    *@see draw_text_vert_top
    *@see draw_text_vert_center
    *@see draw_text
    */
    byte draw_text_right(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *Draw a text
    *this function draw a text in a center relative position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_right
    *@see draw_text_vert
    *@see draw_text_vert_top
    *@see draw_text_vert_center
    *@see draw_text
    */
    byte draw_text_center(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *Draw a text
    *this function draw a vectical text in a given vectical relative position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_center
    *@see draw_text_right
    *@see draw_text_vert
    *@see draw_text_vert_top
    *@see draw_text
    */
    byte draw_text_vert_center(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *Draw a text
    *this function draw a text on top of informed position, containing its forecolor and backcolor informed.
    *@param text the text to draw
    *@param position the position to draw
    *@param forecolor the text color
    *@param backcolor the text backcolor
    *@return return number of chars written
    *@see Pixel
    *@see draw_text_center
    *@see draw_text_right
    *@see draw_text_vert
    *@see draw_text_vert_center
    *@see draw_text
    */
    byte draw_text_vert_top(const string text, const Vector2 position, Color forecolor, Color backcolor);
    /**
    *this function check if a sprite fit this drawing in a informed position.
    *@param sprite the sprite to check
    *@param position the position to test
    *@return return true if fit  or false if not;
    */
    bool does_itfit(Sprite& sprite, Vector2 position);
    /**
    *nothing actually
    */
    void rotate(short int graus);
    /**
    *fill all sprite background color with color informed.
    *@param backcolor background color to fill
    *@see fill_backcolor
    */
    void fill_backcolor(Color backcolor);
    /**
    *fill all sprite foreground color with color informed.
    *@param forecolor foreground color to fill
    *@see fill_forecolor
    */
    void fill_forecolor(Color forecolor);
    /**
    *clear all sprite and fill with color informed.
    */
    void clear(Color backcolor);
    /**
    *clear all sprite and fill with black color.
    */
    void clear();
    /**
    *save sprite with file name informed.
    *@param savename name that the file should be saved
    */
    void save(string savename);
};


/**
*the main class
*/
class Engine
{
private:
    HANDLE output_handle;
    HWND console_handle;

    void pre_initialize();
    void pos_initialize();

    short int currentfps;

    Vector2 console_size;
    Vector2 console_position;

public:
    /**
    *pointer to buffer
    */
    Sprite *buffer;
    /**
    *default constructor
    *initialize engine with default settings
    */
    Engine();
    /**
    *initialize engine and set console title to informed.
    *@param title console title
    */
    Engine(string title);
    /**
    *initilize engine with given parameters
    *@param size console window size in pixel(console cells)
    */
    Engine(Vector2 size);
    /**
    *initilize engine with given parameters
    *@param position console window position
    *@param size console window size in pixel(console cells)
    */
    Engine(Vector2 position, Vector2 size);
    /**
    *initilize engine with given parameters
    *@param title console title
    *@param size console window size in pixel(console cells)
    */
    Engine(string title, Vector2 size);
    /**
    *initilize engine with given parameters
    *@param title console title
    *@param position console window position
    *@param size console window size in pixel(console cells)
    */
    Engine(string title, Vector2 position, Vector2 size);
    /**
    *destructor
    */
    ~Engine();
    /**
    *draw engine splash
    */
    void display_splash();
    /**
    *check if window has focus
    *@return return true if window is in focus or false otherwise
    */
    bool focus();
    /**
    *wait window focus
    *this function returns only when the window is in focus
    */
    void wait_focus();
    /**
    *set console window size.
    *@param size new size.
    *@return return true if success or false otherwise
    */
    bool set_size(Vector2 size);
    /**
    *set console window position
    *@param position new position
    *@return return true if success or false otherwise
    */
    bool set_position(Vector2 position);
    /**
    *get console window size
    *@return window size
    */
    Vector2 get_size();
    /**
    *get primary monitor resolution
    *@return return screen resolution
    */
    Vector2 get_screen_resolution();
    /**
    *set console window title
    *@param title new title
    *@return return true if success or false otherwise
    */
    bool set_title(string title);
    /**
    *set console cursor position
    *@param position new position
    *@return return true if success or false otherwise
    */
    bool set_cursor_pos(Vector2 position);
    /**
    *set next write forecolor and backcolor in console
    *@param forecolor foreground color
    *@param backcolor background color
    *@return return true if success or false otherwise
    */
    bool set_text_color (Color forecolor, Color backcolor);
    /**
    *set cursor size and visible state
    *@param size new cursor size
    *@param visible visible state
    *@return return true if success or false otherwise
    */
    bool set_cursor_size(byte size, bool visible);
    /**
    *copy buffer to console
    */
    void update_console();
    /**
    *get current frame rate per second
    */
    short int get_fps();
    //set font
    //get console size
    //get console position
    //get font
};
/**
*class to manipulate user input on keyboard
*/
class Keyboard
{
public:
    /**
    *check key informed
    *@param key key to check
    *@return ?
    */
    static bool get_key(int key);
    /**
    *check key if key informed are down
    *@param key key to check
    *@return return true if are pressed or false otherwise
    */
    static bool get_key_down(int key);
    //revisar as funções abaixo da classe
    static byte get_key();
    static byte get_next_key();
    static string get_string();
    static char get_next_char();
    static string get_string(byte maxsize);
    static int get_numbers(byte maxdigits);
    static int get_numbers(int maxnumber);
};
/**
*nothing currently
*/
class Sound
{
private:
    string filepath;
public:
    Sound(string filename);
    bool play();
    bool stop();
    static bool play_sound(string filename);
    static bool stop_sound(string filename);
};
}

#endif // ENGINE_H_INCLUDED
