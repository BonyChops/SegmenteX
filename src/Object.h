//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECT_H
#define PROG_GAME_OBJECT_H

#include "Collision.h"
#include "CollisionManager.h"
#include <functional>

using namespace std;

class Object {

public:

    enum Type{
        BLOCK,
        INVALID
    };

    virtual ~Object() {
       if(!invalid){
           //TODO: Segmentation Fault
           //delete collision;
       }
    }

    virtual void draw(function<P(P)> fp, float scale) = 0;
    bool isCableAttachable();
    enum Type getType();

    bool invalid = false;
private:
    enum Type type = INVALID;
    bool cableAttachable = false;
};

#endif //PROG_GAME_OBJECT_H
