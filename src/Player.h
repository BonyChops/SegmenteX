//
// Created by bonychops on 12/12/21.
//

#ifndef PROG_GAME_PLAYER_H
#define PROG_GAME_PLAYER_H

#include "Map.h"
#include "Physics.h"

class Player {
public:
    Player();
    Player(Map map);
    ~Player();

    Physics *ph;
    P p;

    void draw(function<P(P)> fp, float scale);
    void draw(function<P(P)> fp, float scale, bool skipResource);
    void drawResource(function<P(P)> fp, float scale);

private:
    Map map;
    Collision *collision;
    function<P(P)> fp;
    bool valid = true;
};


#endif //PROG_GAME_PLAYER_H
