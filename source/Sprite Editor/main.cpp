#include "Console.h"
#include "Utils.h"

#define AUTO_SAVE_INTERVAL 1000 * 60

#define GRID_TOOL 2
#define SELECTTOOL 4
#define HELP 8

#define DOC_HEIGHT 40
#define DOC_WIDTH 40

#define CURSOR_ICON 0x7F
#define COLOR_ICON 0x7F

#define WORKSPACE_CHAR 0xB1

using namespace ConsoleGameEngine;

int main()
{
    Console console("Console Game Engine Sprite Editor");
    console.Resize(Vector2(80, 50));
    console.SetPosition(Vector2(0, 0));

    Vector2 cursor;

    Sprite workspace(Vector2(78, 40));
    Sprite *document = new Sprite(Vector2(DOC_WIDTH, DOC_HEIGHT));
    Vector2 doc_pos((workspace.GetSize().x - document->GetSize().x) / 2, 0);

    Sprite *clipboard = new Sprite(Vector2(0, 0));
    Sprite sprite_undo(document->GetSize());

    color current_color = 0;
    char current_char = 0;

    Vector2 selection, grid_size;
    bool selecttool = false, gridtool = false;
    uint32_t savetick = console.GetTick();

    document->Clear(Colors::White);

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        console.Clear(Colors::White);

        if((console.GetTick() - savetick) > AUTO_SAVE_INTERVAL)
        {
            savetick = console.GetTick();
            document->Save("./Sprites/autosave.cges");
        }

        //leittura do teclado
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
                cursor = Vector2();
                document->Resize(new_size);
            }
        }
        else if(Keyboard::GetKey('W'))
        {
            document->GetPixel(Vector2(cursor.x, cursor.y)).forecolor = current_color;
            document->GetPixel(Vector2(cursor.x, cursor.y)).character = current_char;
            //document->GetPixel(Vector2(cursor.x, cursor.y)).character = Keyboard::GetNextKey();
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
        else if(Keyboard::GetKey('E'))
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
        else if(Keyboard::GetKey('U'))
        {
            Sprite temp(document->GetSize());
            temp.DrawSprite(*document, Vector2(0, 0));
            document->DrawSprite(sprite_undo, Vector2(0, 0));
            sprite_undo.DrawSprite(temp, Vector2(0, 0));
        }
        else if(Keyboard::GetKey('A'))
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
            }
        }
        else if(Keyboard::GetKey(','))
        {
            current_char--;
        }
        else if(Keyboard::GetKey('.'))
        {
            current_char++;
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
        else if(Keyboard::GetKey('8'))
        {
            if(doc_pos.y + document->GetSize().y > 1)
                doc_pos.y--;
        }
        else if(Keyboard::GetKey('2'))
        {
            if(doc_pos.y - document->GetSize().y < workspace.GetSize().y-1)
                doc_pos.y++;
        }
        else if(Keyboard::GetKey('4'))
        {
            if(doc_pos.x + document->GetSize().x > 1)
                doc_pos.x--;
        }
        else if(Keyboard::GetKey('6'))
        {
            if(doc_pos.x - document->GetSize().x < workspace.GetSize().x-1)
                doc_pos.x++;
        }

        workspace.Clear(Colors::White);
        workspace.FillCharacter(WORKSPACE_CHAR);
        workspace.DrawSprite(*document, doc_pos);

        for(uint8_t x = 0; x < document->GetSize().x; ++x)
        {
            for(uint8_t y = 0; y < document->GetSize().y; ++y)
            {
                if(gridtool && (grid_size.x > 0 && grid_size.y > 0))
                {
                    if((((x+1) % grid_size.x == 0) ||
                            ((y+1) % grid_size.y == 0)) && x < document->GetSize().x)
                    {
                        workspace(Vector2(doc_pos.x + x+1, doc_pos.y + y)).character = '°';
                        workspace(Vector2(doc_pos.y + x+1, doc_pos.y + y)).forecolor = Colors::Gray;
                    }
                }
                if(selecttool && x + doc_pos.x < workspace.GetSize().x && y + doc_pos.y < workspace.GetSize().y)
                {
                    if(x == selection.x || y == selection.y ||
                            x == cursor.x || y == cursor.y)
                    {
                        workspace(Vector2(doc_pos.x + x, doc_pos.y + y)).character = '°';
                        workspace(Vector2(doc_pos.x + x, doc_pos.y + y)).forecolor = Colors::Gray;
                    }
                }
            }
        }

        //Show the cursor
        try
        {
            workspace(Vector2(doc_pos.x + cursor.x, doc_pos.y + cursor.y)).character = CURSOR_ICON;
            workspace(Vector2(doc_pos.x + cursor.x, doc_pos.y + cursor.y)).backcolor = current_color;
        }
        catch(...)
        {
            console.ShowError("Invalid cursor position", false);
        }

        console.DrawSprite(workspace, Vector2(1, 7));

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
            }
        }

        console(Vector2(console.GetSize().x - 8, 3)).character = '=';
        console(Vector2(console.GetSize().x - 3, 3)).character = '=';
        console(Vector2(console.GetSize().x - 2, 3)).character = current_char;
        console(Vector2(console.GetSize().x - 2, 3)).forecolor = current_color;

        //draw the color palette
        for(uint8_t c = 0; c < 18; ++c)
        {
            for(uint8_t x = 0; x < 3; ++x)
            {
                console(Vector2(x+(1+4*c), 3)).backcolor = (color)c;
                if(c == current_color)
                    console(Vector2(x+(1+4*c), 3)).character = COLOR_ICON;
            }
        }

        //Show the captions
        console.DrawText("(N)ew (O)pen (S)ave (R)esize (A)nimate (C)opy (X)Cut (V)Paste S(e)lect (U)ndo", Vector2(1, 1), Colors::Black, Colors::White);
        console.DrawTextRight("Char", Vector2(console.GetSize().x - 4, 3), Colors::Black, Colors::White);
        console.DrawText("(-)Previus (+)Next (F)ore (B)ack Rep(l)ace Floo(d) <(W)r(i)te> (G)rid(H)", Vector2(1, 5), Colors::Black, Colors::White);
        console.DrawText("Size " + IntToStr(document->GetSize().x) + " x " + IntToStr(document->GetSize().y) + " = " +
                         "Selection " + IntToStr(selection.x) + " x " + IntToStr(selection.y) + " = " +
                         "Cursor " + IntToStr(cursor.x) + " x " + IntToStr(cursor.y) + " = " +
                         "Clipboard " + IntToStr(clipboard->GetSize().x) + " x " + IntToStr(clipboard->GetSize().y) + " = "
                         , Vector2(1, console.GetSize().y - 2), Colors::Black, Colors::White);

        //Show FPS
        console.DrawTextRight("FPS:" + IntToStr(console.GetCurrentFps()), Vector2(78, console.GetSize().y -2), console.GetCurrentFps() > 59?Colors::Green:Colors::Red, Colors::White);

        console.Update();
        if(!console.Focus())
        {
            console.DrawTextCenter(" _       __      _ __  _            ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-5), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("| |     / /___ _(_) /_(_)___  ____ _", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-4), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("| | /| / / __ `/ / __/ / __ \\/ __ `/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-3), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("| |/ |/ / /_/ / / /_/ / / / / /_/ / ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-2), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("|__/|__/\\__,_/_/\\__/_/_/ /_/\\__, /  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-1), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("                           /____/   ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("    ______                     ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+1), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("   / ____/___  _______  _______", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+2), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("  / /_  / __ \\/ ___/ / / / ___/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+3), Colors::Black, Colors::Transparent);
            console.DrawTextCenter(" / __/ / /_/ / /__/ /_/ (__  ) ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+4), Colors::Black, Colors::Transparent);
            console.DrawTextCenter("/_/    \\____/\\___/\\__,_/____/  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+5), Colors::Black, Colors::Transparent);
            console.Update();
            console.WaitFocus();
        }
    }
    return 0;
}
