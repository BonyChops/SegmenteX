//
// Created by bonychops on 11/12/21.
//

#ifndef PROG_GAME_MAP_H
#define PROG_GAME_MAP_H

#include "objects/Block.h"
#include "ObjectManager.h"
#include <functional>

using namespace std;

class Map {
public:
    Map() {
        blockManager = new ObjectManager<Block, 10000>;
        for (int i = 0; i < 19; ++i) {
            blockManager->addObject(Block((P) {(float) i, 0}));
        }
        blockManager->addObject(Block((P) {2, 1}));
        blockManager->addObject(Block((P) {2, 2}));
        blockManager->addObject(Block((P) {2, 3}));
        for (int i = 0; i < 100; ++i) {
            blockManager->addObject(Block((P) {(float)i, (float)-i}));
        }
    }

    ~Map() {
        //TODO: Segmentation Fault
        //delete blockManager;

    }

    void drawAll(function<P(P)> fp, float scale);

    Collision *CheckCollision(Collision c);

    bool CheckCollisionWithBool(Collision c);


private:
    ObjectManager<Block, 10000> *blockManager;
};

#endif //PROG_GAME_MAP_H
