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
    static bool getKeyboard(int c, Keyboard::Type type){
        auto ite = find_if( KeyboardManager::keyboard.begin(), KeyboardManager::keyboard.end(), [c, type](Keyboard k){return k.getC() == c && k.getType() == type;} );
        if( ite != keyboard.end() ){
            return ite->status;
        }
        return false;
    }

    static void updateKeyboard(int c,Keyboard::Type type, bool status){
        auto ite = find_if( keyboard.begin(), keyboard.end(), [c, type](Keyboard k){return k.getC() == c && k.getType() == type;} );
        if( ite != keyboard.end() ){
            ite->status = status;
            return;
        }
        Keyboard k(c, type, status);
        keyboard.push_back(k);
    }

    static list<Keyboard> keyboard;
};


#endif //PROG_GAME_KEYBOARDMANAGER_H
