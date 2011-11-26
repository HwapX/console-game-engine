#include "Console.h"
#include "Utils.h"

#define AUTO_SAVE_INTERVAL 60000

#define TOOL_GRID 2
#define TOOL_SELECT 4
#define TOOL_HELP 8

#define DOC_HEIGHT 40
#define DOC_WIDTH 40

#define CURSOR_ICON 0x7F
#define COLOR_ICON 0x7F
#define SELECTION_ICON 0xB0

#define MIN_FPS 20
#define MAX_FPS 30

#define WORKSPACE_CHAR 0xB1

using namespace ConsoleGameEngine;

int main(int argc, char* argv[])
{
    Console console("Console Game Engine Sprite Editor");
    console.Resize(Vector2(80, 50));
    console.SetPosition(Vector2(0, 0));

    Sprite frame("./frame.cges");

    Vector2 cursor;

    Sprite workspace(Vector2(78, 40));
    Sprite *document = new Sprite(Vector2(DOC_WIDTH, DOC_HEIGHT));
    Vector2 doc_pos((workspace.GetSize().x - document->GetSize().x) / 2, 0);

    Sprite *clipboard = new Sprite(Vector2(0, 0));
    Sprite sprite_undo(*document);

    color current_color = 0;
    char current_char = 0;

    Vector2 selection, grid_size;
    //uint8_t tools = 0;
    bool selecttool = false, gridtool = false;
    uint32_t savetick = console.GetTick();

    document->Clear(Color::White);

    while(!Keyboard::GetKey(VK_ESCAPE))
    {
        if((console.GetTick() - savetick) > AUTO_SAVE_INTERVAL)
        {
            savetick = console.GetTick();
            document->Save("./Sprites/autosave.cges");
        }

        //leittura do teclado
        if(Keyboard::GetKey('H'))
        {
            Sprite help("help.cges");
            help.DrawText("HELP MENU", Vector2(1, 1), Color::Black, Color::Transparent);

            help.DrawText("N = New file", Vector2(2, 4), Color::Black, Color::Transparent);
            help.DrawText("O = Open file", Vector2(2, 5), Color::Black, Color::Transparent);
            help.DrawText("S = Save file", Vector2(2, 6), Color::Black, Color::Transparent);
            help.DrawText("R = Resize", Vector2(2, 7), Color::Black, Color::Transparent);
            help.DrawText("A = Animate", Vector2(2, 8), Color::Black, Color::Transparent);
            help.DrawText("E = Select tool", Vector2(2, 9), Color::Black, Color::Transparent);
            help.DrawText("G = Grid tool", Vector2(2, 10), Color::Black, Color::Transparent);
            help.DrawText("J = Config Grid", Vector2(2, 11), Color::Black, Color::Transparent);
            help.DrawText("C = Copy", Vector2(2, 12), Color::Black, Color::Transparent);
            help.DrawText("X = Cut", Vector2(2, 13), Color::Black, Color::Transparent);
            help.DrawText("V = Paste", Vector2(2, 14), Color::Black, Color::Transparent);
            help.DrawText("U = Undo", Vector2(2, 15), Color::Black, Color::Transparent);
            help.DrawText("- = Previus Color", Vector2(2, 16), Color::Black, Color::Transparent);
            help.DrawText("+ = Next Color", Vector2(2, 17), Color::Black, Color::Transparent);
            help.DrawText("F = Foreground Color", Vector2(2, 18), Color::Black, Color::Transparent);
            help.DrawText("B = Background Color", Vector2(2, 19), Color::Black, Color::Transparent);
            help.DrawText("L = Replace Color", Vector2(2, 20), Color::Black, Color::Transparent);
            help.DrawText("D = Flood background", Vector2(2, 21), Color::Black, Color::Transparent);
            help.DrawText("Q = Flood foreground", Vector2(2, 22), Color::Black, Color::Transparent);
            help.DrawText("M = Flood character", Vector2(2, 23), Color::Black, Color::Transparent);
            help.DrawText("W = Write character", Vector2(2, 24), Color::Black, Color::Transparent);

            help.DrawText(". = Next character", Vector2(26, 4), Color::Black, Color::Transparent);
            help.DrawText(", = Previus character", Vector2(26, 5), Color::Black, Color::Transparent);
            help.DrawText("I = Input char code", Vector2(26, 6), Color::Black, Color::Transparent);
            help.DrawText("8 = Move document up", Vector2(26, 7), Color::Black, Color::Transparent);
            help.DrawText("2 = Move document down", Vector2(26, 8), Color::Black, Color::Transparent);
            help.DrawText("4 = Move document left", Vector2(26, 9), Color::Black, Color::Transparent);
            help.DrawText("6 = Move document right", Vector2(26, 10), Color::Black, Color::Transparent);
//            help.DrawText("J = Config Grid", Vector2(26, 11), Color::Black, Color::Transparent);
//            help.DrawText("C = Copy", Vector2(26, 12), Color::Black, Color::Transparent);
//            help.DrawText("X = Cut", Vector2(26, 13), Color::Black, Color::Transparent);
//            help.DrawText("V = Paste", Vector2(26, 14), Color::Black, Color::Transparent);
//            help.DrawText("U = Undo", Vector2(26, 15), Color::Black, Color::Transparent);
//            help.DrawText("- = Previus Color", Vector2(26, 16), Color::Black, Color::Transparent);
//            help.DrawText("+ = Next Color", Vector2(26, 17), Color::Black, Color::Transparent);
//            help.DrawText("F = Font Color", Vector2(26, 18), Color::Black, Color::Transparent);
//            help.DrawText("B = Background Color", Vector2(26, 19), Color::Black, Color::Transparent);
//            help.DrawText("L = Replace Color", Vector2(26, 20), Color::Black, Color::Transparent);
//            help.DrawText("D = Flood background", Vector2(26, 21), Color::Black, Color::Transparent);
//            help.DrawText("? = Flood font", Vector2(26, 22), Color::Black, Color::Transparent);
//            help.DrawText("? = Flood character", Vector2(26, 23), Color::Black, Color::Transparent);
//            help.DrawText("W = Write character", Vector2(26, 24), Color::Black, Color::Transparent);
            console.DrawSpriteCenter(help, Vector2(console.GetSize().x / 2, 5));
            console.Update();
            Keyboard::WaitKey('H');

        }
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

            if(console.InputDialog("Resize document", "Input new size (width X height)", result))
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
            sprite_undo = *document;
            document->DrawSprite(*clipboard, cursor);
        }
        else if(Keyboard::GetKey('D'))
        {
            sprite_undo = *document;
            document->FloodBackcolor(cursor, document->GetPixel(Vector2(cursor.x, cursor.y)).backcolor, current_color);
        }
        else if(Keyboard::GetKey('U'))
        {
            Sprite temp(*document);
            *document = sprite_undo;
            sprite_undo = temp;
        }
        else if(Keyboard::GetKey('A'))
        {
            string result;
            Vector2 tilesize;
            uint16_t start = 0, count = 0;
            uint16_t interval = 0;

            if(console.InputDialog("Preview Animation", "input tile size (width X height)", result))
            {
                sscanf(result.c_str(), "%hd X %hd", &tilesize.x, &tilesize.y);
                if(console.InputDialog("Preview Animation", "input frames (start X count)", result))
                {
                    sscanf(result.c_str(), "%hd X %hd", &start, &count);
                    if(console.InputDialog("Preview Animation", "input interval (interval)", result))
                    {
                        sscanf(result.c_str(), "%hd", &interval);
                        Animation preview(*document, tilesize, start, count, interval);
                        while(!Keyboard::GetKey(VK_RETURN))
                        {
                            console.Clear(Color::White);
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

            if(console.InputDialog("Grid size", "Input grid size (width X height)", result))
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
            if(console.InputDialog("Save File","Input the name of file!", result))
            {
                document->Save("./sprites/" + result + ".cges");
            }
        }
        else if(Keyboard::GetKey('O'))
        {
            string result;
            if(console.InputDialog("Open File", "Input the name of file!", result))
            {
                sprite_undo = *document;
                delete document;
                try
                {
                    document = new Sprite("./sprites/" + result + ".cges");
                }
                catch(...){
                    console.MsgDialog("Error", "Cant open the file");
                    document = new Sprite(sprite_undo);
                }
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

        console.DrawSprite(frame, Vector2(0, 0));
        workspace.Clear(Color::White);
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
                        workspace(Vector2(doc_pos.x + x+1, doc_pos.y + y)).character = SELECTION_ICON;
                        workspace(Vector2(doc_pos.y + x+1, doc_pos.y + y)).forecolor = Color::Gray;
                    }
                }
                if(selecttool && x + doc_pos.x < workspace.GetSize().x && y + doc_pos.y < workspace.GetSize().y)
                {
                    if(x == selection.x || y == selection.y ||
                            x == cursor.x || y == cursor.y)
                    {
                        workspace(Vector2(doc_pos.x + x, doc_pos.y + y)).character = SELECTION_ICON;
                        workspace(Vector2(doc_pos.x + x, doc_pos.y + y)).forecolor = Color::Gray;
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
            //console.ShowError("Invalid cursor position", false);
        }

        console.DrawSprite(workspace, Vector2(1, 7));

        console(Vector2(console.GetSize().x - 2, 3)).character = current_char;
        console(Vector2(console.GetSize().x - 2, 3)).forecolor = Color::Black;
        console.DrawTextRight(IntToStr(current_char), Vector2(console.GetSize().x - 2, 5), Color::Black, Color::Transparent);

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
        console.DrawText("(N)ew (O)pen (S)ave (R)esize S(e)lect (C)opy (X)Cut (V)Paste (U)ndo (H)elp", Vector2(1, 1), Color::Black, Color::White);
        console.DrawTextRight("Char", Vector2(console.GetSize().x - 4, 3), Color::Black, Color::White);
        console.DrawText("(-)Previus (+)Next (F)ore (B)ack Rep(l)ace Floo(d)", Vector2(1, 5), Color::Black, Color::White);
        console.DrawText("Size " + IntToStr(document->GetSize().x) + " x " + IntToStr(document->GetSize().y) + " = " +
                         "Selection " + IntToStr(selection.x) + " x " + IntToStr(selection.y) + " = " +
                         "Cursor " + IntToStr(cursor.x) + " x " + IntToStr(cursor.y) + " = " +
                         "Clipboard " + IntToStr(clipboard->GetSize().x) + " x " + IntToStr(clipboard->GetSize().y) + " = "
                         , Vector2(1, console.GetSize().y - 2), Color::Black, Color::White);

        //Show FPS
        console.DrawTextRight("FPS:" + IntToStr(console.GetCurrentFps()), Vector2(78, console.GetSize().y -2), console.GetCurrentFps() >= MIN_FPS?Color::Green:Color::Red, Color::White);

        console.Update();
        if(!console.Focus())
        {
            console.DrawTextCenter(" _       __      _ __  _            ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-5), Color::Black, Color::Transparent);
            console.DrawTextCenter("| |     / /___ _(_) /_(_)___  ____ _", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-4), Color::Black, Color::Transparent);
            console.DrawTextCenter("| | /| / / __ `/ / __/ / __ \\/ __ `/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-3), Color::Black, Color::Transparent);
            console.DrawTextCenter("| |/ |/ / /_/ / / /_/ / / / / /_/ / ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-2), Color::Black, Color::Transparent);
            console.DrawTextCenter("|__/|__/\\__,_/_/\\__/_/_/ /_/\\__, /  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2-1), Color::Black, Color::Transparent);
            console.DrawTextCenter("                           /____/   ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2), Color::Black, Color::Transparent);
            console.DrawTextCenter("    ______                     ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+1), Color::Black, Color::Transparent);
            console.DrawTextCenter("   / ____/___  _______  _______", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+2), Color::Black, Color::Transparent);
            console.DrawTextCenter("  / /_  / __ \\/ ___/ / / / ___/", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+3), Color::Black, Color::Transparent);
            console.DrawTextCenter(" / __/ / /_/ / /__/ /_/ (__  ) ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+4), Color::Black, Color::Transparent);
            console.DrawTextCenter("/_/    \\____/\\___/\\__,_/____/  ", Vector2(console.GetSize().x / 2, console.GetSize().y / 2+5), Color::Black, Color::Transparent);
            console.Update();
            console.WaitFocus();
        }
    }
    return 0;
}
