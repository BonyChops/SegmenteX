//
// Created by bonychops on 12/12/21.
//

#ifndef PROG_GAME_PHYSICS_H
#define PROG_GAME_PHYSICS_H

#include "Define.h"
#include "Collision.h"
#include "TimeManager.h"
#include "Map.h"


class Physics {
public:
    struct Params {
        float a;
        float v;
        float x;
    };
    struct Params x = {0, 0, 0};
    struct Params y = {0, 0, 0};
    Collision *collision;

    Physics();

    Physics(Collision *c);

    Physics(Collision *c, P p, Map *m);

    P getP();

    P getP(struct Params x, struct Params y);

    P calc();

private:
    void updateCollision(bool isX, P p1, P p2, Collision *collision);
    P calcFlow(int dt, bool ixX);
    void calcParam(struct Params *params, float dt);
    void getReadyForCalc(struct Params *bufX, struct Params *bufY, int dt, Collision *tmpC, bool isX);
    TimeManager tm;
    Map *map;
};


#endif //PROG_GAME_PHYSICS_H
