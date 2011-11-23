#include "Console.h"
#include "Utils.h"

#define AUTO_SAVE_INTERVAL 1000 * 60

using namespace ConsoleGameEngine;

int main()
{
    Console console("Console Game Engine Sprite Editor");
    console.Resize(Vector2(80, 82));
    console.SetPosition(Vector2(0, 0));

    color current_color = 0;
    Vector2 cursor;
    Sprite *document = new Sprite(Vector2(72, 72));
    Sprite tool_frame(Vector2(document->GetSize().x +2, document->GetSize().y +1));
    Sprite *clipboard = new Sprite(Vector2(0, 0));
    Sprite sprite_undo = Sprite(document->GetSize());
    Vector2 selection, grid_size;
    bool selecttool = false, gridtool = false;
    uint32_t savetick = console.GetTick();

    document->Clear(Colors::White);

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        if(!console.Focus())
        {
            while(!console.Focus())
            {
                //console.Clear(Colors::White);
                console.DrawTextCenter("Waiting focus!", Vector2(console.GetSize().x / 2, console.GetSize().y / 2), Colors::Black, Colors::White);
                console.Update();
            }
        }
        tool_frame.Clear(Colors::Transparent);
        console.Clear(Colors::White);

        if((console.GetTick() - savetick) > AUTO_SAVE_INTERVAL)
        {
            savetick = console.GetTick();
            document->Save("./Sprites/autosave.cges");
        }

        //le o teclado
        if(Keyboard::GetKey('+'))
        {
            current_color++;
            if(current_color == 17)
                current_color = 0;
        }
        else if(Keyboard::GetKey('-'))
        {
            if(current_color == 0)
                current_color = 17;
            current_color--;
        }
        else if(Keyboard::GetKey('R'))
        {
            string result;
            Vector2 new_size;

            if(console.ShowDialog("Resize document", "Input new size (width X height)", result))
            {
                sscanf(result.c_str(), "%hd X %hd", &new_size.x, &new_size.y);
                document->Resize(new_size);
                tool_frame.Resize(Vector2(document->GetSize().x +2, document->GetSize().y +1));
            }
        }
        else if(Keyboard::GetKey('W'))
        {
            console.SetCursorPosition(Vector2(10 + cursor.x, 3 + cursor.y));
            document->GetPixel(Vector2(cursor.x, cursor.y)).character = Keyboard::GetNextKey();
        }
        else if(Keyboard::GetKey('B'))
        {
            document->GetPixel(Vector2(cursor.x, cursor.y)).backcolor = current_color;
        }
        else if(Keyboard::GetKey('F'))
        {
            document->GetPixel(Vector2(cursor.x, cursor.y)).forecolor = current_color;
        }
        else if(Keyboard::GetKey('L'))
        {
            document->ReplaceBackcolor(document->GetPixel(Vector2(cursor.x, cursor.y)).backcolor, current_color);
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
                }
                else
                {
                    area.x = cursor.x;
                    area.width = selection.x - cursor.x + 1;
                }

                if(selection.y < cursor.y)
                {
                    area.y = selection.y;
                    area.height = cursor.y - selection.y + 1;
                }
                else
                {
                    area.y = cursor.y;
                    area.height = selection.y - cursor.y + 1;
                }

                delete clipboard;
                clipboard = new Sprite(Vector2(area.width, area.height));

                clipboard->DrawSprite(*document, Vector2(0, 0), area);
            }
        }
        else if(Keyboard::GetKey('V'))
        {
            sprite_undo.DrawSprite(*document, Vector2(0, 0));
            document->DrawSprite(*clipboard, cursor);
        }
        else if(Keyboard::GetKey('D'))
        {
            sprite_undo.DrawSprite(*document, Vector2(0, 0));
            document->FloodBackcolor(cursor, document->GetPixel(Vector2(cursor.x, cursor.y)).backcolor, current_color);
        }
        else if(Keyboard::GetKey('Z'))
        {
            Sprite temp(document->GetSize());
            temp.DrawSprite(*document, Vector2(0, 0));
            document->DrawSprite(sprite_undo, Vector2(0, 0));
            sprite_undo.DrawSprite(temp, Vector2(0, 0));
        }
        else if(Keyboard::GetKey('P'))
        {
            string result;
            Vector2 tilesize;
            uint16_t start = 0, count = 0;
            uint16_t interval = 0;

            if(console.ShowDialog("Preview Animation", "input tile size (width X height)", result))
            {
                sscanf(result.c_str(), "%hd X %hd", &tilesize.x, &tilesize.y);
                if(console.ShowDialog("Preview Animation", "input frames (start X count)", result))
                {
                    sscanf(result.c_str(), "%hd X %hd", &start, &count);
                    if(console.ShowDialog("Preview Animation", "input interval (interval)", result))
                    {
                        sscanf(result.c_str(), "%hd", &interval);
                        Animation preview(*document, tilesize, start, count, interval);
                        while(!Keyboard::GetKey(VK_RETURN))
                        {
                            console.Clear(Colors::White);
                            console.DrawSpriteCenter(preview.CurrentFrame(), Vector2(console.GetSize().x / 2, 0));
                            console.Update();
                        }
                    }
                }

            }
        }
        else if(Keyboard::GetKey('J'))
        {
            string result;

            if(console.ShowDialog("Grid size", "Input grid size (width X height)", result))
            {
                sscanf(result.c_str(), "%hd X %hd", &grid_size.x, &grid_size.y);
            }
        }
        else if(Keyboard::GetKey('G'))
        {
            gridtool = !gridtool;
        }
        else if(Keyboard::GetKey('S'))
        {
            string result;
            if(console.ShowDialog("Save File","Input the name of file!", result))
            {
                document->Save("./sprites/" + result + ".cges");
            }
        }
        else if(Keyboard::GetKey('O'))
        {
            string result;
            if(console.ShowDialog("Open File", "Input the name of file!", result))
            {
                sprite_undo.DrawSprite(*document, Vector2(0, 0));
                delete document;
                document = new Sprite("./sprites/" + result + ".cges");
                tool_frame.Resize(Vector2(document->GetSize().x +2, document->GetSize().y +1));
            }
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

        for(uint8_t x = 0; x < tool_frame.GetSize().x; ++x)
        {
            for(uint8_t y = 0; y < tool_frame.GetSize().y; ++y)
            {
                if(gridtool && (grid_size.x > 0 && grid_size.y > 0))
                {
                    if((((x+1) % grid_size.x == 0) ||
                            ((y+1) % grid_size.y == 0)) && x < document->GetSize().x)
                    {
                        tool_frame(Vector2(x+1, y)).character = '°';
                        tool_frame(Vector2(x+1, y)).forecolor = Colors::Gray;
                    }
                }
                if(selecttool)
                    if(x == selection.x+1 || y == selection.y ||
                            x == cursor.x+1 || y == cursor.y)
                    {
                        tool_frame(Vector2(x, y)).character = '°';
                        tool_frame(Vector2(x, y)).forecolor = Colors::Gray;
                    }

                if(x == 0 || x == tool_frame.GetSize().x - 1 || y == tool_frame.GetSize().y - 1)
                {
                    tool_frame(Vector2(x, y)).character = '=';
                }
            }
        }

        //Show the cursor
        tool_frame(Vector2(cursor.x+1, cursor.y)).character = 0x7F;
        tool_frame(Vector2(cursor.x+1, cursor.y)).backcolor = current_color;

        console.DrawSpriteCenter(*document, Vector2(console.GetSize().x / 2, 7));
        console.DrawSpriteCenter(tool_frame, Vector2(console.GetSize().x / 2, 7));

        //draw editor grid
        for(uint8_t x = 0; x < console.GetSize().x; ++x)
        {
            for(uint8_t y = 0; y < console.GetSize().y; ++y)
            {
                if(y == 0 || x == 0 ||
                        y == console.GetSize().y-1 ||
                        x == console.GetSize().x-1 ||
                        y == 2 || y == 4 || y == 6 ||
                        y == console.GetSize().y - 3)
                {
                    console(Vector2(x, y)).character = '=';
                    console(Vector2(x, y)).forecolor = Colors::Gray;
                }
                else if(x > console.GetSize().x - 6 && x < console.GetSize().x -1)   //show selected color
                {
                    console(Vector2(x, 3)).backcolor = current_color;
                }
            }
        }

        console(Vector2(console.GetSize().x - 6, 3)).character = '=';
        console(Vector2(console.GetSize().x - 12, 3)).character = '=';

        //draw the color palette
        for(uint8_t c = 0; c < 17; ++c)
            for(uint8_t x = 0; x < 3; ++x)
            {
                console(Vector2(x+(1+4*c), 3)).backcolor = (color)c;
                if(c == current_color)
                    console(Vector2(x+(1+4*c), 3)).character = '°';
            }

        //Show the captions
        console.DrawText("(N)ew (O)pen (S)ave (R)esize (W)rite (C)opy (X)Cut (V)Paste (A)Select (Z)Undo", Vector2(1, 1), Colors::Black, Colors::White);
        console.DrawTextRight("Color", Vector2(console.GetSize().x - 7, 3), Colors::Black, Colors::White);
        console.DrawText("Colors (F)ont (B)ackground (L)Replace (-)Previus (+)Next (D)Flood", Vector2(1, 5), Colors::Black, Colors::White);
        console.DrawText("Size " + IntToStr(document->GetSize().x) + " x " + IntToStr(document->GetSize().y) + " = " +
                                "Selection " + IntToStr(selection.x) + " x " + IntToStr(selection.y) + " = " +
                                "Cursor " + IntToStr(cursor.x) + " x " + IntToStr(cursor.y) + " = " +
                                "Clipboard " + IntToStr(clipboard->GetSize().x) + " x " + IntToStr(clipboard->GetSize().y) + " = "
                                , Vector2(1, console.GetSize().y - 2), Colors::Black, Colors::White);

        //Show FPS
        console.DrawTextRight("FPS:" + IntToStr(console.GetCurrentFps()), Vector2(78, console.GetSize().y -2), console.GetCurrentFps() > 59?Colors::Green:Colors::Red, Colors::White);

        console.Update();
        console.WaitFocus();
    }
    return 0;
}
