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
    Map() {
        blockManager = new ObjectManager<Block, 10000>;
        keyInputManager = new ObjectManager<KeyInput, 10000>;
        keyInputManager->addObject(KeyInput((P){2, 4}, 'h'));
        segmentManager = new ObjectManager<Segment, 10000>;
        for (int i = 1; i < 10; ++i) {
            segmentManager->addObject(Segment((P){(float)2 + i * 2, (float)4 - (i % 2 == 0 ? 2 : 0)}));
            if(i == 1){
                keyInputManager->ats(0)->attachCable((CableAttachableObject *)segmentManager->ats(i));
            }else{
                segmentManager->ats(i - 1)->attachCable((CableAttachableObject *)segmentManager->ats(i));
            }
        }
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
    ObjectManager<KeyInput, 10000> *keyInputManager;
    ObjectManager<Segment, 10000> *segmentManager;
};

#endif //PROG_GAME_MAP_H
