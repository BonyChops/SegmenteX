//
// Created by bonychops on 12/12/21.
//

#include "Map.h"

void Map::drawAll(function<P(P)> fp, float scale) {
    P test = fp((P){0, 0});
    blockManager->drawAll(fp, scale);
}