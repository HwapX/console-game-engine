#include "Engine.h"

using namespace ConsoleGameEngine;

int main()
{
    Engine engine("Console Game Engine Sound Editor");

    uint8_t chanels = 5, notes = 50;
    uint16_t d_duration = 100, d_distance = 200;

    Sprite table(Vector2(10, 80));

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.buffer->Clear();

        for(uint8_t x = 0; x < engine.GetWindowSize().x; ++x)
        {
            for(uint8_t y = 0; y < engine.GetWindowSize().y; ++y)
            {
                if(y == 0 || y == engine.GetWindowSize().y-1 ||
                        y == 2 || y == 4 ||
                        y == engine.GetWindowSize().y - 3)
                {
                    engine.buffer->data[x][y].character = 0xCD;
                    engine.buffer->data[x][y].forecolor = Colors::Gray;
                }
                else if(x == 0 || x == engine.GetWindowSize().x-1)
                {
                    engine.buffer->data[x][y].character = 0xBA;
                    engine.buffer->data[x][y].forecolor = Colors::Gray;
                }
            }
        }
        engine.buffer->data[0][0].character = 0xC9;
        engine.buffer->data[0][0].forecolor = Colors::Gray;
        engine.buffer->data[0][2].character = 0xCC;
        engine.buffer->data[0][2].forecolor = Colors::Gray;
        engine.buffer->data[0][4].character = 0xCC;
        engine.buffer->data[0][4].forecolor = Colors::Gray;

        engine.buffer->DrawText("(C)hanels (D)istance (F)requence (R)esize", Vector2(1, 1), Colors::White, Colors::Transparent);
        engine.buffer->DrawText("(+)Duration(-) (Up)Frequence(Down)", Vector2(1, 3), Colors::White, Colors::Transparent);

        engine.UpdateConsole();
    }

    return(0);
}
