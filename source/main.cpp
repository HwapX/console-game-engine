#include "Engine.h"
#include <sstream>

using namespace Console_Engine;

string convert_int(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

int main()
{
<<<<<<< .mine
    Engine engine("Console Game Engine"); // Sets title;
=======
    Engine engine("Sprite editor for Console Game Engine");
>>>>>>> .r9
    engine.set_size(Vector2(80, 50));

    byte current_color = 0;
    Vector2 cursor;
    Sprite *document = new Sprite(Vector2(20, 20));
    document->clear(White);
    bool iswriting = false;

    while(!Keyboard::get_key(VK_ESCAPE))
    {
<<<<<<< .mine
        if(Keyboard::get_key(VK_ADD) || Keyboard::get_key(VK_OEM_PLUS))
=======
        engine.wait_focus();

        //le o teclado
        if(Keyboard::get_key(VK_ADD) ||
           Keyboard::get_key(VK_OEM_PLUS))
>>>>>>> .r9
        {
            current_color++;
            if(current_color == 18)
                current_color = 0;
        }
<<<<<<< .mine
        else if(Keyboard::get_key(VK_SUBTRACT) || Keyboard::get_key(VK_OEM_MINUS))
=======
        else if(Keyboard::get_key(VK_SUBTRACT) ||
                Keyboard::get_key(VK_OEM_MINUS))
>>>>>>> .r9
        {
            if(current_color == 0)
                current_color = 17;
            current_color--;
        }
        else if(Keyboard::get_key('R'))
        {
            //FIX: arrumar bug na leitura do novo tamanho
            engine.set_cursor_pos(Vector2(1, 23));
            //delete document;
            Vector2 temp;

            engine.set_cursor_pos(Vector2(6, 23));

            //document = new Sprite(temp);
        }
        else if(Keyboard::get_key('W') || iswriting)
        {
            byte key = Keyboard::get_key();
            iswriting = true;
            engine.set_cursor_pos(Vector2(10 + cursor.X, 3 + cursor.Y));
<<<<<<< .mine
            if(key == (VK_BACK || VK_DELETE)) // Caso o usuario, durante o "writing" queira apagar, backspace ou delete o faz.
                document->data[cursor.X][cursor.Y].character = ' '; // APAGA!
            else if(key == VK_RETURN)
                iswriting = false;
            else
            {
                document->data[cursor.X][cursor.Y].character = key;
                cursor.X++;
                if(cursor.X >= document->size.X)
                {
                    cursor.Y++;
                    cursor.X = 0;
                }
            }
=======
            document->data[cursor.X][cursor.Y].character = Keyboard::get_next_char();
>>>>>>> .r9
        }
        else if(Keyboard::get_key('B'))
        {
            document->data[cursor.X][cursor.Y].backcolor = (Color)current_color;
        }
        else if(Keyboard::get_key('F'))
        {
            document->data[cursor.X][cursor.Y].forecolor = (Color)current_color;
        }
        else if(Keyboard::get_key('C'))
        {
            document->fill_backcolor((Color)current_color);
        }
        else if(Keyboard::get_key('S'))
        {
            engine.buffer->clear();
            engine.update_console();
            document->save("./sprite.cges");
        }
        else if(Keyboard::get_key('L'))
        {
            delete document;
            document = new Sprite("./sprite.cges");
        }
        if(Keyboard::get_key(VK_UP))
        {
            if(cursor.Y > 0)
                cursor.Y--;
        }
        else if(Keyboard::get_key(VK_DOWN))
        {
            if(cursor.Y < document->size.Y-1)
                cursor.Y++;
        }
        else if(Keyboard::get_key(VK_LEFT))
        {
            if(cursor.X > 0)
                cursor.X--;
        }
        else if(Keyboard::get_key(VK_RIGHT))
        {
            if(cursor.X < document->size.X-1)
                cursor.X++;
        }
        else if(Keyboard::get_key(VK_BACK)) // Consiste em usar o BACKSPACE pra apagar letras
        {
            if(cursor.X > 0) // Verifica se o cursor est� no canto da tela do document.
                if(document->data[cursor.X-1][cursor.Y].character != ' ') // Caso exista uma letra � uma posi��o antes do cursor
                {
                    document->data[cursor.X-1][cursor.Y].character = ' ';  // APAGA!
                    cursor.X--;
                }
        }

        //desenha toda a grade da janela
        for(byte x = 0; x < engine.get_size().X; ++x)
            for(byte y = 0; y < engine.get_size().Y; ++y)
            {
                if(y == 0 || x == 0 ||
                        y == engine.get_size().Y-1 ||
                        x == engine.get_size().X-1 ||
                        y == 2 || y == 4 || y == 6 ||
                        y == engine.get_size().Y - 3)
                {
                    engine.buffer->data[x][y].character = '=';
                    engine.buffer->data[x][y].forecolor = LightGrey;
                }//verifica se x esta a uma posi��o inferior a 4 da borda direita da janela
                else if(x > engine.get_size().X - 5 && x < engine.get_size().X)   //mostra a cor selecionada atualmente
                {
                    engine.buffer->data[x][5].backcolor = (Color)current_color;
                }

                //desenha o contorno do documento
                if((x == document->size.X && y <= document->size.Y) ||
                        (y == document->size.Y && x <= document->size.X))
                {
                    //as constantes s�o a posi��o onde o documento sera desenhado
                    engine.buffer->data[1+x][7+y].character = '=';
                    engine.buffer->data[1+x][7+y].forecolor = LightGrey;
                }
            }
        engine.buffer->data[engine.get_size().X - 5 ][5].character = '=';

        //desenha a palete de cores
        for(byte c = 0; c < 18; ++c)
            for(byte x = 0; x < 3; ++x)
            {
                engine.buffer->data[x+(8+4*c)][3].backcolor = (Color)c;
                if(c == current_color)
                    engine.buffer->data[x+(8+4*c)][3].character = '�';
            }

        //desenha o documento
        engine.buffer->draw_sprite(*document, Vector2(1, 7));

        //desenha o cursor
        engine.buffer->data[1+cursor.X][7+cursor.Y].character = '�';
        engine.buffer->data[1+cursor.X][7+cursor.Y].backcolor = (Color)current_color;

        //mostra as dimen��es do documento
        engine.buffer->draw_text_right(convert_int(document->size.X) + " x " + convert_int(document->size.Y), Vector2(78, 1), Black, White);

        //desenha a legenda
        engine.buffer->draw_text("Colors",  Vector2(1, 3), Black, White);
        engine.buffer->draw_text("{L}oad {S}ave {C}lear {R}esize {W}rite", Vector2(1, 1), Black, White);
        engine.buffer->draw_text("Color {F}orecolor {B}ackcolor {-}previus {+}next", Vector2(1, 5), Black, White);
        engine.buffer->draw_text_right("Current color", Vector2(engine.get_size().X - 6, 5), Black, White);
        engine.buffer->draw_text("Use arrows to move the cursor", Vector2(1, engine.get_size().Y - 2), Black, White);

        //Mostra o FPS
        engine.buffer->draw_text_right("FPS:" + convert_int(engine.get_fps()), Vector2(78, engine.get_size().Y -2), engine.get_fps() > 59?LightGreen:LightRed, White);

        engine.update_console();
        engine.buffer->clear(White);
    }
    return 0;
}
