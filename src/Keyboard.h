//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_KEYBOARD_H
#define PROG_GAME_KEYBOARD_H

#include <any>

using namespace std;

class Keyboard{
public:
    bool status = false;
    enum Type{
        KEY,
        SPECIAL,
        MOUSE
    };

    int modifier;
    Keyboard(int c, enum Type type, bool status, int modifier){
        this->c = c;
        this->status = status;
        this->type = type;
        this->modifier = modifier;
    }

    int getC(){
        return this->c;
    }

    enum Type getType(){
        return this->type;
    }

    void setC(char c){
        this->c = c;
    }

private:
    char c;
    enum Type type;
};

#endif //PROG_GAME_KEYBOARD_H
