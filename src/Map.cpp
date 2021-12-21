//
// Created by bonychops on 12/12/21.
//

#include "Map.h"

Map::Map() {
    /*
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
    */
    objectManager = ObjectManager<10000>();
    for (int i = 0; i < 10; ++i) {
        objectManager.addObject(Block((P){(float)i, (float)i}));
    }
}

void Map::drawAll(function<P(P)> fp, float scale) {
    //cout << scale << endl;
    P test = fp((P) {0, 0});
//    blockManager->drawAll(fp, scale);
//    keyInputManager->drawAll(fp, scale);
//    segmentManager->drawAll(fp, scale);
    objectManager.drawAll(fp, scale);
    //Block block = Block((P){0, 0});
    //block.draw(fp, scale);
}

Collision *Map::CheckCollision(Collision c) {
    //Collision *result = blockManager->CheckCollision(c);
    Collision *result = objectManager.CheckCollision(c);
    if (result->getType() != Collision::INVALID_COLLISION) {
        return result;
    }
    return new Collision(Collision::INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
}

bool Map::CheckCollisionWithBool(Collision c) {
    return objectManager.CheckCollisionWithBool(c);
}