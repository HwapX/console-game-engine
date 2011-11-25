#include "Console.h"
#include "Utils.h"

#define CURSOR_ICON 0xDB//0xFE//0x7F

#define NOTE_ICON 0xF4

using namespace ConsoleGameEngine;

int main()
{
    Console console("Console Game Engine Sound Editor", Vector2(80, 37));

    Sprite frame("./frame.cges");

    uint8_t chanels = 15;
    uint16_t max_frequence = 12000;

    Sound *track = new Sound(78);
    Sprite table(Vector2(78, 29));
    Vector2 cursor;
    Note current_note(0, 500);

    for(uint8_t i = 0; i < track->GetSize(); ++i)
    {
        track->ReplaceNote(i, Note(i*100 + 2000, 300));
    }

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        console.DrawSprite(frame, Vector2(0, 0));
        table.Clear(Color::Transparent, 0);

        if(Keyboard::GetKey('S'))
        {
            string result;
            if(console.ShowDialog("Save File","Input the name of file!", result))
            {
                track->Save("./Sounds/" + result + ".cgea");
            }
        }
        else if(Keyboard::GetKey('L'))
        {
            string result;
            if(console.ShowDialog("Open File", "Input the name of file!", result))
            {
                delete track;
                track = new Sound("./Sounds/" + result + ".cgea");
            }
        }
        if(Keyboard::GetKey('P'))
        {
            if(track->IsPlaying() && !track->Paused())
            {
                track->Pause();
            }
            else
            {
                track->Play();
            }
        }
        else if(Keyboard::GetKey('O'))
        {
            track->Stop();
        }
        else if(Keyboard::GetKey('Y'))
        {
            //tocar nota atual da faixa
            Sound note(1);
            note.ReplaceNote(0, track->GetNote(cursor.x));
            note.Play(true);
        }
        else if(Keyboard::GetKey('T'))
        {
            //tocar nota atual
            Sound note(1);
            note.ReplaceNote(0, current_note);
            note.Play(true);
        }
        else if(Keyboard::GetKey('N'))
        {
            track->ReplaceNote(cursor.x , Note(0, current_note.duration));
        }
        else if(Keyboard::GetKey(' '))
        {
            track->ReplaceNote(cursor.x , current_note);
        }
        else if(Keyboard::GetKey('-'))
        {
            if(current_note.duration > 0)
                current_note.duration-=10;
        }
        else if(Keyboard::GetKey('+'))
        {
            current_note.duration+=10;
        }
        else if(Keyboard::GetKey(','))
        {
            if(current_note.frequence > 0)
                current_note.frequence-=25;
        }
        else if(Keyboard::GetKey('.'))
        {
            current_note.frequence+=25;
        }

        if(Keyboard::GetKey(VK_UP))
        {
            if(cursor.y > 0)
                cursor.y--;
            current_note.frequence = max_frequence / chanels * (cursor.y + 1);
        }
        else if(Keyboard::GetKey(VK_DOWN))
        {
            if(cursor.y < chanels-1)
                cursor.y++;
            current_note.frequence = max_frequence / chanels * (cursor.y + 1);
        }
        else if(Keyboard::GetKey(VK_LEFT))
        {
            if(cursor.x > 0)
                cursor.x--;
        }
        else if(Keyboard::GetKey(VK_RIGHT))
        {
            if(cursor.x < track->GetSize())
                cursor.x++;
        }

        console.DrawText("(S)ave (L)oad (C)hanels (D)istance (F)requence (R)esize (P)lay/Pause St(o)p", Vector2(1, 1), Color::White, Color::Transparent);
        console.DrawText("(+)Duration(-) (,)(Up)Frequence(Down)(.) (A)ctual (T)est", Vector2(1, 3), Color::White, Color::Transparent);

        console.DrawText(" Frequence = " + IntToStr(track->GetNote(cursor.x).frequence) + " Duration = " + IntToStr(track->GetNote(cursor.x).duration),
                                 Vector2(1, console.GetSize().y - 2), Color::White, Color::Transparent);
        console.DrawTextRight("Note = " + IntToStr(cursor.x) + " Frequence = " + IntToStr(current_note.frequence) + " Duration = " + IntToStr(current_note.duration),
                                 Vector2(console.GetSize().x -2, console.GetSize().y - 2), Color::White, Color::Transparent);

        /*for(uint8_t i = 0; i < track->GetSize(); ++i)
        {
            if(track->GetNote(i).frequence > max_frequence)
            {
                max_frequence = track->GetNote(i).frequence;
            }
        }*/

        cursor.y = current_note.frequence>1?((current_note.frequence - 1) * chanels) / max_frequence:0;

        for(uint8_t x = 0; x < track->GetSize(); ++x)
        {
            if(track->GetNote(x).frequence > 0)
            {
                uint8_t y = track->GetNote(x).frequence>1?((track->GetNote(x).frequence - 1) * chanels) / max_frequence:0;
                table(Vector2(x, y * 2)).forecolor = y+1;
                table(Vector2(x, y * 2)).character = NOTE_ICON;
                if(track->IsPlaying() && x == track->GetCurrent())
                {
                    table(Vector2(x, y * 2)).backcolor = y+1;
                }
            }
        }
        table(Vector2(cursor.x, cursor.y * 2)).character = CURSOR_ICON;
        table(Vector2(cursor.x, cursor.y * 2)).forecolor = cursor.y + 1;

        console.DrawSprite(table, Vector2(1, 5));

        console.Update();

        if(!console.Focus())
        {
            console.DrawTextCenter(" _       __      _ __  _            ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-5), Color::White, Color::Transparent);
            console.DrawTextCenter("| |     / /___ _(_) /_(_)___  ____ _", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-4), Color::White, Color::Transparent);
            console.DrawTextCenter("| | /| / / __ `/ / __/ / __ \\/ __ `/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-3), Color::White, Color::Transparent);
            console.DrawTextCenter("| |/ |/ / /_/ / / /_/ / / / / /_/ / ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-2), Color::White, Color::Transparent);
            console.DrawTextCenter("|__/|__/\\__,_/_/\\__/_/_/ /_/\\__, /  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-1), Color::White, Color::Transparent);
            console.DrawTextCenter("                           /____/   ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2), Color::White, Color::Transparent);
            console.DrawTextCenter("    ______                     ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+1), Color::White, Color::Transparent);
            console.DrawTextCenter("   / ____/___  _______  _______", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+2), Color::White, Color::Transparent);
            console.DrawTextCenter("  / /_  / __ \\/ ___/ / / / ___/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+3), Color::White, Color::Transparent);
            console.DrawTextCenter(" / __/ / /_/ / /__/ /_/ (__  ) ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+4), Color::White, Color::Transparent);
            console.DrawTextCenter("/_/    \\____/\\___/\\__,_/____/  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+5), Color::White, Color::Transparent);
            console.Update();
            console.WaitFocus();
        }

    }

    return(0);
}
