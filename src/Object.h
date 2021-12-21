//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECT_H
#define PROG_GAME_OBJECT_H

#include "Collision.h"
#include "CollisionManager.h"
#include <functional>
#include "ResourceManager.h"

typedef ResourceManager RCM;

using namespace std;

class Object {

public:
    P p;
    enum Type{
        INVALID,
        BLOCK,
        KEY_INPUT,
        SEGMENT,
        CABLE
    };

    ~Object() {
       if(!invalid){
           //TODO: Segmentation Fault
           //delete collision;
       }
    }

    virtual void draw(function<P(P)> fp, float scale);
    virtual bool isCableAttachable();
    enum Type getType();
    CollisionManager<COLLISIONS_PER_OBJECT> collisions;
    bool invalid = false;
protected:
    enum Type type = INVALID;
    bool cableAttachable = false;
};

#endif //PROG_GAME_OBJECT_H
