//
// Created by bonychops on 12/12/21.
//

#include "Map.h"

void Map::drawAll(function<P(P)> fp, float scale) {
    //cout << scale << endl;
    P test = fp((P) {0, 0});
    blockManager->drawAll(fp, scale);
}

Collision *Map::CheckCollision(Collision c) {
    Collision *result = blockManager->CheckCollision(c);
    if (result->getType() != Collision::INVALID_COLLISION) {
        return result;
    }
    return new Collision(Collision::INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
}

bool Map::CheckCollisionWithBool(Collision c) {
    return blockManager->CheckCollisionWithBool(c);
}