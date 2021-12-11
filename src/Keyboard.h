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

    Keyboard(int c, bool status){
        this->c = c;
        this->status = status;
    }

    int getC(){
        return this->c;
    }

    void setC(char c){
        this->c = c;
    }

private:
    char c;
};

#endif //PROG_GAME_KEYBOARD_H
