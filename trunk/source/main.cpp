#include "Engine.h"
#include <sstream>

int Game();

using namespace ConsoleGameEngine;

string convert_int(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

string show_dialog(Engine &engine, string title)
{
    byte key = 0;
    string str;
    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 -3), Black, White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 -2), Black, White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 -1), Black, White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 ), Black, White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 +1), Black, White);
        engine.buffer->DrawTextCenter(title, Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2 -2), Black, White);

        if(key == VK_BACK && str.size() != 0)
            str.erase(str.size() -1, 1);
        else if(key == 13)//VK_EXECUTE)
            return str;
        else
        {
            str+= key;
        }
        engine.buffer->DrawTextCenter(str, Vector2(engine.GetWindowSize().X / 2, engine.GetWindowSize().Y / 2), Black, White);
        engine.UpdateConsole();
        engine.buffer->Clear(White);

        key = Keyboard::GetNextKey();
    }
    return str;
}

int main()
{
    Engine engine("Sprite editor for Console Game Engine");
    engine.SetWindowSize(Vector2(80, 40));

    byte current_color = 0;
    Vector2 cursor;
    Sprite *document = new Sprite(Vector2(8, 8));//(66, 64));
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
            engine.SetCursorPosition(Vector2(10 + cursor.X, 3 + cursor.Y));
            document->data[cursor.X][cursor.Y].character = Keyboard::GetNextKey();
        }
        else if(Keyboard::GetKey('B'))
        {
            document->data[cursor.X][cursor.Y].backcolor = (Color)current_color;
        }
        else if(Keyboard::GetKey('F'))
        {
            document->data[cursor.X][cursor.Y].forecolor = (Color)current_color;
        }
        else if(Keyboard::GetKey('C'))
        {
            document->FillBackcolor((Color)current_color);
        }
        else if(Keyboard::GetKey('S'))
        {
            ++saveid;
            document->Save("./sprite_" + convert_int(saveid) + ".cges");
            //document->Save("c:/mod/" + show_dialog(engine, "enter the filename to save") + ".ces");
        }
        else if(Keyboard::GetKey('L'))
        {
            delete document;
            document = new Sprite("./sprite_" + convert_int(saveid) + ".cges");//"./" + show_dialog(engine, "enter the filename to load"));
        }
        else if(Keyboard::GetKey('G'))
        {
            Game();
            engine.SetWindowSize(Vector2(80, 50));
        }
        if(Keyboard::GetKey(VK_UP))
        {
            if(cursor.Y > 0)
                cursor.Y--;
        }
        else if(Keyboard::GetKey(VK_DOWN))
        {
            if(cursor.Y < document->GetSize().Y-1)
                cursor.Y++;
        }
        else if(Keyboard::GetKey(VK_LEFT))
        {
            if(cursor.X > 0)
                cursor.X--;
        }
        else if(Keyboard::GetKey(VK_RIGHT))
        {
            if(cursor.X < document->GetSize().X-1)
                cursor.X++;
        }

        //desenha toda a grade da janela
        for(byte x = 0; x < engine.GetWindowSize().X; ++x)
            for(byte y = 0; y < engine.GetWindowSize().Y; ++y)
            {
                if(y == 0 || x == 0 ||
                        y == engine.GetWindowSize().Y-1 ||
                        x == engine.GetWindowSize().X-1 ||
                        y == 2 || y == 4 || y == 6 ||
                        y == engine.GetWindowSize().Y - 3)
                {
                    engine.buffer->data[x][y].character = '=';
                    engine.buffer->data[x][y].forecolor = LightGrey;
                }//verifica se x esta a uma posição inferior a 4 da borda direita da janela
                else if(x > engine.GetWindowSize().X - 5 && x < engine.GetWindowSize().X)   //mostra a cor selecionada atualmente
                {
                    engine.buffer->data[x][5].backcolor = (Color)current_color;
                }

                //desenha o contorno do documento
                if((x == document->GetSize().X && y <= document->GetSize().Y) ||
                        (y == document->GetSize().Y && x <= document->GetSize().X))
                {
                    //as constantes são a posição onde o documento sera desenhado
                    engine.buffer->data[1 + x][7 + y].character = '=';
                    engine.buffer->data[1 + x][7 + y].forecolor = LightGrey;
                }
            }
        engine.buffer->data[engine.GetWindowSize().X - 5 ][5].character = '=';

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
        engine.buffer->data[1+cursor.X][7+cursor.Y].character = '°';
        engine.buffer->data[1+cursor.X][7+cursor.Y].backcolor = (Color)current_color;

        //mostra as dimenções do documento
        engine.buffer->DrawText_right(convert_int(document->GetSize().X) + " x " + convert_int(document->GetSize().Y), Vector2(78, 1), Black, White);

        //desenha a legenda
        engine.buffer->DrawText("Colors",  Vector2(1, 3), Black, White);
        engine.buffer->DrawText("{L}oad {S}ave {C}lear {R}esize {W}rite", Vector2(1, 1), Black, White);
        engine.buffer->DrawText("Color {F}orecolor {B}ackcolor {-}previus {+}next", Vector2(1, 5), Black, White);
        engine.buffer->DrawText_right("Current color", Vector2(engine.GetWindowSize().X - 6, 5), Black, White);
        engine.buffer->DrawText("Use arrows to move the cursor = current save is " + convert_int(saveid), Vector2(1, engine.GetWindowSize().Y - 2), Black, White);

        //Mostra o FPS
        engine.buffer->DrawText_right("FPS:" + convert_int(engine.GetCurrentFps()), Vector2(78, engine.GetWindowSize().Y -2), engine.GetCurrentFps() > 59?LightGreen:LightRed, White);

        engine.UpdateConsole();
        engine.buffer->Clear(White);
    }
    return 0;
}
