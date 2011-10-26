#include "Engine.h"
#include <sstream>
#include <assert.h>

int Game();

using namespace ConsoleGameEngine;

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
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -3), Colors::Black, Colors::White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -2), Colors::Black, Colors::White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -1), Colors::Black, Colors::White);
        engine.buffer->DrawTextCenter("=                                        =", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 ), Colors::Black, Colors::White);
        engine.buffer->DrawTextCenter("==========================================", Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 +1), Colors::Black, Colors::White);
        engine.buffer->DrawTextCenter(title, Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2 -2), Colors::Black, Colors::White);

        if(key == VK_BACK && str.size() != 0)
            str.erase(str.size() -1, 1);
        else if(key == 13)//VK_EXECUTE)
            return str;
        else
        {
            str+= key;
        }
        engine.buffer->DrawTextCenter(str, Vector2(engine.GetWindowSize().x / 2, engine.GetWindowSize().y / 2), Colors::Black, Colors::White);
        engine.UpdateConsole();
        engine.buffer->Clear(Colors::White);

        key = Keyboard::GetNextKey();
    }
    return str;
}

int main()
{
    Engine engine("Console Game Engine Sprite Editor");
    engine.SetWindowSize(Vector2(80, 80));
    engine.SetWindowPosition(Vector2(0, 0));

    color current_color = 0;
    Vector2 cursor;
    Sprite *document = new Sprite(Vector2(64, 64));
    Sprite tool_frame(Vector2(document->GetSize().x +2, document->GetSize().y +1));
    Sprite *clipboard = new Sprite(Vector2(0, 0));
    Sprite sprite_undo = Sprite(document->GetSize());
    Vector2 selection;
    bool selecttool = false;
    document->Clear(Colors::White);

    int saveid = 2;

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        engine.WaitFocus();

        //le o teclado
        if(Keyboard::GetKey(VK_ADD) ||
                Keyboard::GetKey(VK_OEM_PLUS))
        {
            current_color++;
            if(current_color == 17)
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
            //resize
        }
        else if(Keyboard::GetKey('W'))
        {
            engine.SetCursorPosition(Vector2(10 + cursor.x, 3 + cursor.y));
            document->data[cursor.x][cursor.y].character = Keyboard::GetNextKey();
        }
        else if(Keyboard::GetKey('B'))
        {
            document->data[cursor.x][cursor.y].backcolor = current_color;
        }
        else if(Keyboard::GetKey('F'))
        {
            document->data[cursor.x][cursor.y].forecolor = current_color;
        }
        else if(Keyboard::GetKey('L'))
        {
            document->ReplaceBackcolor(document->data[cursor.x][cursor.y].backcolor, current_color);
        }
        else if(Keyboard::GetKey('N'))
        {
            document->FillBackcolor((color)current_color);
        }
        else if(Keyboard::GetKey('A'))
        {
            selecttool = !selecttool;
            if(selecttool)
                selection = cursor;
            else
                selection = Vector2(0, 0);
            //select tool
        }
        else if(Keyboard::GetKey('C'))
        {
            if(selecttool)
            {
                Rect area;
                if(selection.x < cursor.x)
                {
                    area.x = selection.x;
                    area.width = cursor.x - selection.x + 1;
                }else
                {
                    area.x = cursor.x;
                    area.width = selection.x - cursor.x + 1;
                }

                if(selection.y < cursor.y)
                {
                    area.y = selection.y;
                    area.height = cursor.y - selection.y + 1;
                }else
                {
                    area.y = cursor.y;
                    area.height = selection.y - cursor.y + 1;
                }

                delete clipboard;
                clipboard = new Sprite(Vector2(area.width, area.height));

                clipboard->DrawSprite(*document, Vector2(0, 0), area);
            }
        }else if(Keyboard::GetKey('V'))
        {
            sprite_undo.DrawSprite(*document, Vector2(0, 0));
            document->DrawSprite(*clipboard, cursor);
        }
        else if(Keyboard::GetKey('Z'))
        {
            document->DrawSprite(sprite_undo, Vector2(0, 0));
        }
        else if(Keyboard::GetKey('S'))
        {
            ++saveid;
            document->Save("./sprites/sprite_" + IntToStr(saveid) + ".cges");
            //document->Save("c:/mod/" + show_dialog(engine, "enter the filename to save") + ".ces");
        }
        else if(Keyboard::GetKey('O'))
        {
            sprite_undo.DrawSprite(*document, Vector2(0, 0));
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

        //draw the document


        tool_frame.Clear(Colors::Transparent);

        for(byte x = 0; x < tool_frame.GetSize().x; ++x)
        {
            for(byte y = 0; y < tool_frame.GetSize().y; ++y)
            {
                if(selecttool)
                    if(x == selection.x+1 || y == selection.y ||
                       x == cursor.x+1 || y == cursor.y)
                    {
                        tool_frame.data[x][y].character = '°';
                        tool_frame.data[x][y].forecolor = Colors::Gray;
                    }

                if(x == 0 || x == tool_frame.GetSize().x - 1 || y == tool_frame.GetSize().y - 1)
                {
                    tool_frame.data[x][y].character = '=';
                }
            }
        }

        //Show the cursor
        tool_frame.data[cursor.x+1][cursor.y].character = '°';
        tool_frame.data[cursor.x+1][cursor.y].backcolor = current_color;

        engine.buffer->DrawSpriteCenter(*document, Vector2(engine.buffer->GetSize().x / 2, 7));
        engine.buffer->DrawSpriteCenter(tool_frame, Vector2(engine.GetWindowSize().x / 2, 7));


        //draw editor grid
        for(byte x = 0; x < engine.GetWindowSize().x; ++x)
        {
            for(byte y = 0; y < engine.GetWindowSize().y; ++y)
            {
                if(y == 0 || x == 0 ||
                        y == engine.GetWindowSize().y-1 ||
                        x == engine.GetWindowSize().x-1 ||
                        y == 2 || y == 4 || y == 6 ||
                        y == engine.GetWindowSize().y - 3)
                {
                    engine.buffer->data[x][y].character = '=';
                    engine.buffer->data[x][y].forecolor = Colors::Gray;
                }
                else if(x > engine.GetWindowSize().x - 6 && x < engine.GetWindowSize().x -1)   //show selected color
                {
                    engine.buffer->data[x][3].backcolor = current_color;
                }
            }
        }
        engine.buffer->data[engine.GetWindowSize().x - 6][3].character = '=';
        engine.buffer->data[engine.GetWindowSize().x - 12][3].character = '=';

        //draw the color palette
        for(byte c = 0; c < 17; ++c)
            for(byte x = 0; x < 3; ++x)
            {
                engine.buffer->data[x+(1+4*c)][3].backcolor = (color)c;
                if(c == current_color)
                    engine.buffer->data[x+(1+4*c)][3].character = '°';
            }

        //Show the captions
        engine.buffer->DrawText("(N)ew (O)pen (S)ave (R)esize (W)rite (C)opy (X)Cut (V)Paste (A)Select (Z)Undo", Vector2(1, 1), Colors::Black, Colors::White);
        engine.buffer->DrawTextRight("Color", Vector2(engine.GetWindowSize().x - 7, 3), Colors::Black, Colors::White);
        engine.buffer->DrawText("Colors (F)ont (B)ackground Rep(l)ace (-)Previus (+)Next", Vector2(1, 5), Colors::Black, Colors::White);
        //engine.buffer->DrawText("Use arrows to move the cursor = current save is " + IntToStr(saveid), Vector2(1, engine.GetWindowSize().y - 2), Colors::Black, Colors::White);
        engine.buffer->DrawText(IntToStr(document->GetSize().x) + " x " + IntToStr(document->GetSize().y) + " = " +
                                IntToStr(selection.x) + " x " + IntToStr(selection.y) + " = " +
                                IntToStr(cursor.x) + " x " + IntToStr(cursor.y) + " = " +
                                IntToStr(clipboard->GetSize().x) + " x " + IntToStr(clipboard->GetSize().y) + " = "
                                , Vector2(1, engine.GetWindowSize().y - 2), Colors::Black, Colors::White);

        //Show FPS
        engine.buffer->DrawTextRight("FPS:" + IntToStr(engine.GetCurrentFps()), Vector2(78, engine.GetWindowSize().y -2), engine.GetCurrentFps() > 59?Colors::Green:Colors::Red, Colors::White);

        engine.UpdateConsole();
        engine.buffer->Clear(Colors::White);
    }
    return 0;
}
