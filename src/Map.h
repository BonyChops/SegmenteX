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
    Map(){
        blockManager = new ObjectManager<Block, 10000>;
        blockManager->addObject(Block((P){0, 0}));
    }
    ~Map(){
        delete blockManager;
    }

    void drawAll(function<P(P)> fp, float scale);


private:
    ObjectManager<Block, 10000> *blockManager;
};

#endif //PROG_GAME_MAP_H
