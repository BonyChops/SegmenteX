//
// Created by bonychops on 11/12/21.
//

#ifndef PROG_GAME_MAP_H
#define PROG_GAME_MAP_H

#include "objects/Block.h"
#include "objects/KeyInput.h"
#include "objects/Segment.h"
#include "ObjectManager.h"
#include "CableAttachableObject.h"
#include <functional>

using namespace std;

class Map {
public:
    Map();

    ~Map() {
        //TODO: Segmentation Fault
        //delete blockManager;

    }

    void drawAll(function<P(P)> fp, float scale);

    Collision *CheckCollision(Collision c);

    bool CheckCollisionWithBool(Collision c);


private:
//    ObjectManager<Block, 10000> *blockManager;
//    ObjectManager<KeyInput, 10000> *keyInputManager;
//    ObjectManager<Segment, 10000> *segmentManager;
    ObjectManager<10000> objectManager;
};

#endif //PROG_GAME_MAP_H
