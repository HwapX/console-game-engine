#include "Console.h"
#include "Utils.h"

#define CURSOR_ICON 0x9E//0xFE//0x7F

#define NOTE_ICON 0xF4

using namespace ConsoleGameEngine;

int main()
{
    Console console("Console Game Engine Sound Editor", Vector2(80, 25));

    uint8_t chanels = 15, notes = 20;
    uint16_t duration = 100;
    uint16_t max_frequence = 20000;

    Sound *audio = new Sound(78);
    Sprite table(Vector2(78, 15));
    Vector2 cursor;

    for(uint8_t i = 0; i < audio->GetSize(); ++i)
    {
        audio->ReplaceNote(i, Note(i*200, 150));
    }

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        console.Clear();
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



        for(uint8_t x = 0; x < console.GetSize().x; ++x)
        {
            for(uint8_t y = 0; y < console.GetSize().y; ++y)
            {
                if(y == 0 || y == console.GetSize().y-1 ||
                        y == 2 || y == 4 ||
                        y == console.GetSize().y - 3)
                {
                    console(Vector2(x, y)).character = 0xCD;
                    console(Vector2(x, y)).forecolor = Colors::Gray;
                }
                else if(x == 0 || x == console.GetSize().x-1)
                {
                    console(Vector2(x, y)).character = 0xBA;
                    console(Vector2(x, y)).forecolor = Colors::Gray;
                }
            }
        }
        console(Vector2(0, 0)).character = 0xC9;
        console(Vector2(0, 0)).forecolor = Colors::Gray;
        console(Vector2(0, 2)).character = 0xCC;
        console(Vector2(0, 2)).forecolor = Colors::Gray;
        console(Vector2(0, 4)).character = 0xCC;
        console(Vector2(0, 4)).forecolor = Colors::Gray;

        console.DrawText("(S)ave (L)oad (C)hanels (D)istance (F)requence (R)esize (P)lay/Pause St(o)p", Vector2(1, 1), Colors::White, Colors::Transparent);
        console.DrawText("(+)Duration(-) (Up)Frequence(Down) (A)ctual (T)est", Vector2(1, 3), Colors::White, Colors::Transparent);

        console.DrawText(" Frequence = " + IntToStr(audio->GetNote(cursor.x).frequence) + " Duration = " + IntToStr(audio->GetNote(cursor.x).duration),
                                 Vector2(1, console.GetSize().y - 2), Colors::White, Colors::Transparent);
        console.DrawTextRight("Note = " + IntToStr(cursor.x) + " Frequence = " + IntToStr(cursor.y) + " Duration = " + IntToStr(duration),
                                 Vector2(console.GetSize().x -2, console.GetSize().y - 2), Colors::White, Colors::Transparent);

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
            table(Vector2(x, y)).forecolor = y+1;
            table(Vector2(x, y)).character = NOTE_ICON;
            if(audio->IsPlaying() && x == audio->GetCurrent())
            {
                table(Vector2(x, y)).backcolor = y+1;
            }
        }
        table(Vector2(cursor.x, cursor.y * chanels / max_frequence)).character = CURSOR_ICON;
        table(Vector2(cursor.x, cursor.y * chanels / max_frequence)).forecolor = (audio->GetNote(cursor.x).frequence?(audio->GetNote(cursor.x).frequence * chanels) / max_frequence:0) + 1;

        console.DrawSprite(table, Vector2(1, 5));

        console.Update();
    }

    return(0);
}
