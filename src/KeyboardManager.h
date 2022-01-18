//
// Created by bonychops on 22/12/21.
//

#ifndef PROG_GAME_KEYBOARDMANAGER_H
#define PROG_GAME_KEYBOARDMANAGER_H

#include "KeyboardUtils.h"

typedef KeyboardUtils KBU;

class KeyboardManager {
public:
    KeyboardManager(char c, Keyboard::Type type);
    KeyboardManager(char c, Keyboard::Type type, int modifier);
    bool check();

protected:
    bool pressed = false;
    char c;
    int modifier;
    Keyboard::Type type;
};


#endif //PROG_GAME_KEYBOARDMANAGER_H
