//
// Created by bonychops on 22/12/21.
//

#include "KeyboardManager.h"
#include <iostream>

KeyboardManager::KeyboardManager(char c, Keyboard::Type type) : KeyboardManager(c, type, 0){}

KeyboardManager::KeyboardManager(char c, Keyboard::Type type, int modifier) {
    this->c = c;
    this->type = type;
    this->modifier = modifier;
    std::cout << "Key: " <<c << endl;
}

bool KeyboardManager::check() {
    bool keyStatus = KBU::getKeyboard(this->c, this->type, modifier);
    bool result = (this->pressed && !keyStatus);
    this->pressed = keyStatus;
    if(result){
        std::cout << "pressed" << endl;
    }
    return result;
}