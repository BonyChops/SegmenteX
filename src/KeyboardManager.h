//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_KEYBOARDMANAGER_H
#define PROG_GAME_KEYBOARDMANAGER_H

#include <list>
#include <algorithm>
#include "Keyboard.h"

using namespace std;

class KeyboardManager{
public:
    static bool getKeyboard(int c){
        auto ite = find_if( KeyboardManager::keyboard.begin(), KeyboardManager::keyboard.end(), [c](Keyboard k){return k.getC() == c;} );
        if( ite != keyboard.end() ){
            return ite->status;
        }
        return false;
    }

    static void updateKeyboard(int c, bool status){
        auto ite = find_if( keyboard.begin(), keyboard.end(), [c](Keyboard k){return k.getC() == c;} );
        if( ite != keyboard.end() ){
            ite->status = status;
            return;
        }
        Keyboard k(c, status);
        keyboard.push_back(k);
    }

    static list<Keyboard> keyboard;
};
list<Keyboard> KeyboardManager::keyboard;


#endif //PROG_GAME_KEYBOARDMANAGER_H
