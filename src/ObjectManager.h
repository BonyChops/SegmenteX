//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECTMANAGER_H
#define PROG_GAME_OBJECTMANAGER_H

#include "Collision.h"
#include "Object.h"

#include <list>
#include <array>
#include <algorithm>
#include <iostream>
#include "Point.h"
#include <functional>
#include "objects/Block.h"

using namespace std;
typedef Point P;

template<typename T, int S>
class ObjectManager {
public:
    ObjectManager(){

    }

    bool CheckCollision(P p) {
        auto ite = find_if(begin(objects), end(objects), [p](auto o) { return o.collision->CheckCollision(p); });
        return ite != end(objects);
        for (int i = 0; i < objIndex; ++i) {

        }
    }

    void addObject(T object) {
        if (objIndex >= S) {
            cerr << "[!]MAXIMUM SIZE OF " << typeid(T).name() << "(" << S << ")" << " REACHED!!";
            return;
        }
        objects[objIndex] = object;
        objIndex += 1;
    }

    void drawAll(function<P(P)> fp, float scale) {
        for (int i = 0; i < objIndex; ++i) {
          objects.at(i).draw(fp, scale);
        }
        //for_each(begin(objects), end(objects), [fp, scale](T o) { o.draw(fp, scale); });
    }


private:
    array<T, S> objects;
    // Object objects[10000];
    int objIndex = 0;
};

#endif //PROG_GAME_OBJECTMANAGER_H
