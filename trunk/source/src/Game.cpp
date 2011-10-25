#include "Engine.h"
#include <stdlib.h>
#include <ctime>
#include <sstream>

using namespace ConsoleGameEngine;

typedef struct sbrick
{
    string num;
    char pos;
} brick;

string inttostr(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

int Game()
{
    Engine engine("Brick game", Vector2(80, 27));
    brick bricks[40];
    srand(time(NULL));
    for(byte b = 0; b < 40; ++b)
    {
        bricks[b].num = inttostr(rand());
        bricks[b].pos = -1;
    }

    int lasttick = 0, points = 0;
    byte current = 0, interval = 10;
    string str;
    while(!Keyboard::GetKey(VK_ESCAPE) || interval == 2)
    {
        //engine.WaitFocus();
        for(byte b = 0; b <= current; b++)
        {
            if(bricks[b].pos != -1)
            {
                if(((current != b) && (bricks[current].pos + 3 == bricks[b].pos)) || (bricks[current].pos + 3 == engine.GetWindowSize().y))
                {
                    if(bricks[b].pos == 3)
                        return 1;
                    ++current;
                    str.clear();
                }
                engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, bricks[b].pos   ), Colors::White, Colors::DarkBlue);
                engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().x / 2, bricks[b].pos +1), Colors::White, Colors::DarkBlue);
                engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, bricks[b].pos +2), Colors::White, Colors::DarkBlue);
                engine.buffer->DrawTextCenter(bricks[b].num, Vector2(engine.GetWindowSize().x / 2, bricks[b].pos +1), Colors::White, Colors::DarkBlue);
            }
        }

        if((GetTickCount() - lasttick) > 25 * interval)
        {
            ++bricks[current].pos;
            lasttick = GetTickCount();
        }

        for(byte b = 0; b < 255; b++)
            if(Keyboard::GetKey(b))
                str+= b;


        if(str != bricks[current].num.substr(0, str.size()))
        {
            str.clear();
        }
        else if(str == bricks[current].num)
        {
            points+= 1000 / interval;
            bricks[current].pos = -1;
            ++current;
            --interval;
        }

        engine.buffer->DrawText(str, Vector2((engine.GetWindowSize().x / 2) - ((bricks[current].num.size()-1) / 2), bricks[current].pos +1), Colors::Green, Colors::DarkBlue);
        engine.buffer->DrawText(inttostr(points), Vector2(0, 0), Colors::Yellow, Colors::DarkBlue);

        engine.UpdateConsole();
        engine.buffer->Clear(Colors::Blue);
    }

    return 0;
}
