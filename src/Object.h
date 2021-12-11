//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECT_H
#define PROG_GAME_OBJECT_H

#include "Collision.h"
#include <functional>

using namespace std;

class Object {

public:

    virtual ~Object() {
        //delete collision;
    }

    virtual void draw(function<P(P)> fp, float scale) = 0;

    Collision *collision;
};

#endif //PROG_GAME_OBJECT_H
