#ifndef CGE_INPUT_H
#define CGE_INPUT_H

#include <windows.h>
#include <iostream>

namespace ConsoleGameEngine
{

/**
*class to manipulate user input on keyboard
*/
class Keyboard
{
public:
    /**
    *check key informed
    *@param key key to check
    *@return ?
    */
    static bool GetKey(char key);
    /**
    *check key if key informed are down
    *@param key key to check
    *@return return true if are pressed or false otherwise
    */
    static bool GetKeyDown(const char key);
    //revisar as funções abaixo da classe
    static char GetKey();
    static char GetNextKey();

    //static char TranslateKey(const char key);
private:

};

}

#endif // CGE_INPUT_H
