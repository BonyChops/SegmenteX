//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_KEYBOARDUTILS_H
#define PROG_GAME_KEYBOARDUTILS_H

#include <list>
#include <algorithm>
#include "Keyboard.h"

#include <iostream>

using namespace std;

class KeyboardUtils {
public:
    static bool getKeyboard(int c, Keyboard::Type type) {
        return getKeyboard(c, type, 0);
    }

    static bool getKeyboard(int c, Keyboard::Type type, int modifier) {
        auto ite = find_if(KeyboardUtils::keyboard.begin(), KeyboardUtils::keyboard.end(),
                           [c, type](Keyboard k) { return k.getC() == c && k.getType() == type; });
        if (ite != keyboard.end()) {
            return modifier == ite->modifier && ite->status;
        }
        return false;
    }

    static void updateKeyboard(int c, Keyboard::Type type, bool status, int modifier) {
        auto ite = find_if(keyboard.begin(), keyboard.end(),
                           [c, type](Keyboard k) { return k.getC() == c && k.getType() == type; });
        if (ite != keyboard.end()) {
            ite->status = status;
            ite->modifier = modifier;
            return;
        }
        Keyboard k(c, type, status, modifier);
        keyboard.push_back(k);
    }

    static list<Keyboard> keyboard;
};


#endif //PROG_GAME_KEYBOARDUTILS_H
