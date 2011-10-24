#ifndef CGE_INPUT_H
#define CGE_INPUT_H

#include <windows.h>

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
        static bool GetKey(int key);
        /**
        *check key if key informed are down
        *@param key key to check
        *@return return true if are pressed or false otherwise
        */
        static bool GetKey_down(int key);
        //revisar as funções abaixo da classe
        static byte GetKey();
        static byte GetNextKey();
};

#endif // CGE_INPUT_H
