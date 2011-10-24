#include "Engine.h"
#include <sstream>

int Game();

//using namespace ConsoleGameEngine;

string IntToStr(int number)
{
    char num[10];
    itoa(number, num, 10);
    return num;
}

string show_dialog(Engine &engine, string title)
{
    byte key = 0;
    string str;
    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -3), Black, White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -2), Black, White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -1), Black, White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 ), Black, White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 +1), Black, White);
        engine.buffer->DrawTextCenter(title, Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -2), Black, White);

        if(key == VK_BACK && str.size() != 0)
            str.erase(str.size() -1, 1);
        else if(key == 13)//VK_EXECUTE)
            return str;
        else
        {
            str+= key;
        }
        engine.buffer->DrawTextCenter(str, Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2), Black, White);
        engine.UpdateConsole();
        engine.buffer->Clear(White);

        key = Keyboard::GetNextKey();
    }
    return str;
}

int main()
{
    Engine engine("Sprite editor for Console Game Engine");
    engine.SetWindowSize(Vector2(80, 80));

    byte current_color = 0;
    Vector2 cursor;
    Sprite *document = new Sprite(Vector2(64, 64));
    document->Clear(White);

    int saveid = 0;

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.WaitFocus();

        //le o teclado
        if(Keyboard::GetKey(VK_ADD) ||
                Keyboard::GetKey(VK_OEM_PLUS))
        {
            current_color++;
            if(current_color == 18)
                current_color = 0;
        }
        else if(Keyboard::GetKey(VK_SUBTRACT) ||
                Keyboard::GetKey(VK_OEM_MINUS))
        {
            if(current_color == 0)
                current_color = 17;
            current_color--;
        }
        else if(Keyboard::GetKey('R'))
        {
            //FIX: arrumar bug na leitura do novo tamanho
            engine.SetCursorPosition(Vector2(1, 23));
            //delete document;
            Vector2 temp;

            engine.SetCursorPosition(Vector2(6, 23));

            //document = new Sprite(temp);
        }
        else if(Keyboard::GetKey('W'))
        {
            engine.SetCursorPosition(Vector2(10 + cursor.x, 3 + cursor.y));
            document->data[cursor.x][cursor.y].character = Keyboard::GetNextKey();
        }
        else if(Keyboard::GetKey('B'))
        {
            document->data[cursor.x][cursor.y].backcolor = (Color)current_color;
        }
        else if(Keyboard::GetKey('F'))
        {
            document->data[cursor.x][cursor.y].forecolor = (Color)current_color;
        }
        else if(Keyboard::GetKey('C'))
        {
            document->FillBackcolor((Color)current_color);
        }
        else if(Keyboard::GetKey('S'))
        {
            ++saveid;
            document->Save("./sprites/sprite_" + IntToStr(saveid) + ".cges");
            //document->Save("c:/mod/" + show_dialog(engine, "enter the filename to save") + ".ces");
        }
        else if(Keyboard::GetKey('L'))
        {
            delete document;
            document = new Sprite("./sprites/sprite_" + IntToStr(saveid) + ".cges");//"./" + show_dialog(engine, "enter the filename to load"));
        }
        else if(Keyboard::GetKey('G'))
        {
            Game();
            engine.SetWindowSize(Vector2(80, 50));
        }
        if(Keyboard::GetKey(VK_UP))
        {
            if(cursor.y > 0)
                cursor.y--;
        }
        else if(Keyboard::GetKey(VK_DOWN))
        {
            if(cursor.y < document->GetSize().y-1)
                cursor.y++;
        }
        else if(Keyboard::GetKey(VK_LEFT))
        {
            if(cursor.x > 0)
                cursor.x--;
        }
        else if(Keyboard::GetKey(VK_RIGHT))
        {
            if(cursor.x < document->GetSize().x-1)
                cursor.x++;
        }

        //desenha toda a grade da janela
        for(byte x = 0; x < engine.GetWindowSize().x; ++x)
            for(byte y = 0; y < engine.GetWindowSize().y; ++y)
            {
                if(y == 0 || x == 0 ||
                        y == engine.GetWindowSize().y-1 ||
                        x == engine.GetWindowSize().x-1 ||
                        y == 2 || y == 4 || y == 6 ||
                        y == engine.GetWindowSize().y - 3)
                {
                    engine.buffer->data[x][y].character = '=';
                    engine.buffer->data[x][y].forecolor = LightGrey;
                }//verifica se x esta a uma posição inferior a 4 da borda direita da janela
                else if(x > engine.GetWindowSize().x - 5 && x < engine.GetWindowSize().x)   //mostra a cor selecionada atualmente
                {
                    engine.buffer->data[x][5].backcolor = (Color)current_color;
                }

                //desenha o contorno do documento
                if((x == document->GetSize().x && y <= document->GetSize().y) ||
                        (y == document->GetSize().y && x <= document->GetSize().x))
                {
                    //as constantes são a posição onde o documento sera desenhado
                    engine.buffer->data[1 + x][7 + y].character = '=';
                    engine.buffer->data[1 + x][7 + y].forecolor = LightGrey;
                }
            }
        engine.buffer->data[engine.GetWindowSize().x - 5 ][5].character = '=';

        //desenha a palete de cores
        for(byte c = 0; c < 18; ++c)
            for(byte x = 0; x < 3; ++x)
            {
                engine.buffer->data[x+(8+4*c)][3].backcolor = (Color)c;
                if(c == current_color)
                    engine.buffer->data[x+(8+4*c)][3].character = '°';
            }

        //desenha o documento
        engine.buffer->DrawSprite(*document, Vector2(1, 7));

        //desenha o cursor
        engine.buffer->data[1+cursor.x][7+cursor.y].character = '°';
        engine.buffer->data[1+cursor.x][7+cursor.y].backcolor = (Color)current_color;

        //mostra as dimenções do documento
        engine.buffer->DrawText_right(IntToStr(document->GetSize().x) + " x " + IntToStr(document->GetSize().y), Vector2(78, 1), Black, White);

        //desenha a legenda
        engine.buffer->DrawText("Colors",  Vector2(1, 3), Black, White);
        engine.buffer->DrawText("{L}oad {S}ave {C}lear {R}esize {W}rite", Vector2(1, 1), Black, White);
        engine.buffer->DrawText("Color {F}orecolor {B}ackcolor {-}previus {+}next", Vector2(1, 5), Black, White);
        engine.buffer->DrawText_right("Current color", Vector2(engine.GetWindowSize().x - 6, 5), Black, White);
        engine.buffer->DrawText("Use arrows to move the cursor = current save is " + IntToStr(saveid), Vector2(1, engine.GetWindowSize().y - 2), Black, White);

        //Mostra o FPS
        engine.buffer->DrawText_right("FPS:" + IntToStr(engine.GetCurrentFps()), Vector2(78, engine.GetWindowSize().y -2), engine.GetCurrentFps() > 59?LightGreen:LightRed, White);

        engine.UpdateConsole();
        engine.buffer->Clear(White);
    }
    return 0;
}
