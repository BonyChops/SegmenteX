//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECT_H
#define PROG_GAME_OBJECT_H

#include "Collision.h"
#include "CollisionManager.h"
#include <functional>
#include "ResourceManager.h"

#include "../lib/json.hpp"

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
        CABLE,
        GOAL,
        ERASER,
        SPIKE,
        CABLE_ATTACHABLE
    };

    Object();

    ~Object() {
       if(!invalid){
           //TODO: Segmentation Fault
           //delete collision;
       }
    }

    virtual void draw(function<P(P)> fp, float scale);
    virtual void draw(function<P(P)> fp, float scale, bool editorView);
    virtual bool isCableAttachable();
    virtual bool isCableExportable();
    virtual bool isCableExported();
    virtual void resetCable();
    virtual void setCablePos(P p);
    virtual bool attachCable(Object *o);
    virtual nlohmann::json dumpJson();
    nlohmann::json posToJson(P p);
    enum Type getType();
    CollisionManager<COLLISIONS_PER_OBJECT> collisions;
    bool invalid = false;
    Animator scaleAni;
protected:
    enum Type type = INVALID;
    bool cableAttachable = false;
    bool cableExported = false;
    bool cableExportable = false;
};

#endif //PROG_GAME_OBJECT_H
