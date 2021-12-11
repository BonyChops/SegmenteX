//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_COLLISION_H
#define PROG_GAME_COLLISION_H

#include "Point.h"
#include "CoordinateUtils.h"

typedef Point P;

class Collision {
public:

    enum Type {
        SQUARE
    };

    Collision(enum Type type, P p1, P p2) {
        this->type = type;
        this->p1 = p1;
        this->p2 = p2;
    }

    bool CheckCollision(P p) {
        switch (type) {
            SQUARE:
                return CoodinateUtils::IsInsideBox(p, p1, p2);
        }
    }

private:
    enum Type type = SQUARE;
    P p1 = {0, 0};
    P p2 = {0, 0};
};

#endif //PROG_GAME_COLLISION_H
