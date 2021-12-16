//
// Created by bonychops on 16/12/21.
//

#ifndef PROG_GAME_GAMEARRAY_H
#define PROG_GAME_GAMEARRAY_H
#include <iostream>
#include <array>
#include "GameArrayIterator.h"

template<class T, int S>
class GameArray {
public:
    GameArray() {
        this->objectArray = std::array<T, S>();
    }

    GameArray(T o) {
        GameArray<T, S>();
    }

    void push(T o) {
        if (index >= S) {
            std::cerr << "[!]MAXIMUM SIZE OF " << typeid(T).name() << "(" << S << ")" << " REACHED!!" << std::endl;
            return;
        }
        objectArray.at(index) = o;
        index += 1;
    }

    int getMax() {
        return index;
    }

    Iterator<T> begin() { return Iterator<T>(&objectArray.at(0)); }
    Iterator<T> end()   { return Iterator<T>(&objectArray.at(index)); }

private:
    std::array<T, S> objectArray;
    int index;

};


#endif //PROG_GAME_GAMEARRAY_H
