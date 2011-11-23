#include "Engine.h"
#include "Utils.h"

#define CURSOR_ICON 0xF4//0xFE//0x7F

using namespace ConsoleGameEngine;

int main()
{
    Engine engine("Console Game Engine Sound Editor", Vector2(80, 25));

    uint8_t chanels = 15, notes = 20;
    uint16_t duration = 100;
    uint16_t max_frequence = 20000;

    Sound *audio = new Sound(78);
    Sprite table(Vector2(78, 15));
    Vector2 cursor;

    for(uint8_t i = 0; i < audio->GetSize(); ++i)
    {
        audio->ReplaceNote(i, Note(i*200, 300));
    }

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.buffer->Clear();
        table.Clear(Colors::Transparent);

        if(Keyboard::GetKey('S'))
        {

        }
        else if(Keyboard::GetKey('L'))
        {

        }
        if(Keyboard::GetKey('P'))
        {
            if(audio->IsPlaying() && !audio->Paused())
            {
                audio->Pause();
            }
            else
            {
                audio->Play();
            }
        }
        else if(Keyboard::GetKey('O'))
        {
            audio->Stop();
        }
        else if(Keyboard::GetKey('Y'))
        {
            Sound note(1);
            note.ReplaceNote(0, audio->GetNote(cursor.x));
            note.Play(true);
        }
        else if(Keyboard::GetKey('T'))
        {
            Sound note(1);
            note.ReplaceNote(0, Note(cursor.y, duration));
            note.Play(true);
        }
        else if(Keyboard::GetKey(' '))
        {
            audio->ReplaceNote(cursor.x ,Note(cursor.y, duration));
        }
        else if(Keyboard::GetKey('-'))
        {
            if(duration > 0)
                duration-=10;
        }
        else if(Keyboard::GetKey('+'))
        {
            duration+=10;
        }

        if(Keyboard::GetKey(VK_UP))
        {
            if(cursor.y > 0)
                cursor.y-=50;
        }
        else if(Keyboard::GetKey(VK_DOWN))
        {
            if(cursor.y < max_frequence)
            cursor.y+=50;
        }
        else if(Keyboard::GetKey(VK_LEFT))
        {
            if(cursor.x > 0)
                cursor.x--;
        }
        else if(Keyboard::GetKey(VK_RIGHT))
        {
            if(cursor.x < table.GetSize().x-1)
                cursor.x++;
        }



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

        engine.buffer->DrawText("(S)ave (L)oad (C)hanels (D)istance (F)requence (R)esize (P)lay/Pause St(o)p", Vector2(1, 1), Colors::White, Colors::Transparent);
        engine.buffer->DrawText("(+)Duration(-) (Up)Frequence(Down) (A)ctual (T)est", Vector2(1, 3), Colors::White, Colors::Transparent);

        engine.buffer->DrawText(" Frequence = " + IntToStr(audio->GetNote(cursor.x).frequence) + " Duration = " + IntToStr(audio->GetNote(cursor.x).duration),
                                 Vector2(1, engine.buffer->GetSize().y - 2), Colors::White, Colors::Transparent);
        engine.buffer->DrawTextRight("Note = " + IntToStr(cursor.x) + " Frequence = " + IntToStr(cursor.y) + " Duration = " + IntToStr(duration),
                                 Vector2(engine.buffer->GetSize().x -2, engine.buffer->GetSize().y - 2), Colors::White, Colors::Transparent);

        /*for(uint8_t i = 0; i < audio->GetSize(); ++i)
        {
            if(audio->GetNote(i).frequence > max_frequence)
            {
                max_frequence = audio->GetNote(i).frequence;
            }
        }*/

        for(uint8_t x = 0; x < audio->GetSize(); ++x)
        {
            uint8_t y = audio->GetNote(x).frequence?(audio->GetNote(x).frequence * chanels) / max_frequence:0;
            table.data[x][y].backcolor = y+1;
        }
        if(audio->IsPlaying() && !audio->Paused())
        {
            uint8_t y = audio->GetNote(audio->GetCurrent()).frequence?(audio->GetNote(audio->GetCurrent()).frequence * chanels) / max_frequence:0;
            table.data[audio->GetCurrent()][y].character = CURSOR_ICON;
            table.data[audio->GetCurrent()][y].forecolor = Colors::White;
        }
        else
        {
            table.data[cursor.x][cursor.y * chanels / max_frequence].character = CURSOR_ICON;
            table.data[cursor.x][cursor.y * chanels / max_frequence].forecolor = Colors::White;
        }

        engine.buffer->DrawSprite(table, Vector2(1, 5));

        engine.UpdateConsole();
    }

    return(0);
}
