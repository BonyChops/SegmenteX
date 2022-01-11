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

    Player(Map *map);

    ~Player();

    Physics ph;
    P p = {0, 5};

    void setP(P p, bool check);

    void draw(function<P(P)> fp, float scale);

    void draw(function<P(P)> fp, float scale, bool skipResource);

    void draw(function<P(P)> fp, float scale, bool skipResource, bool editorView);

    void drawResource(function<P(P)> fp, float scale);

    P findNearestP(P p);



private:
    Map *map;
    Collision collision;
    function<P(P)> fp;
    bool valid = true;
    Collision generateCollision(P p);
};


#endif //PROG_GAME_PLAYER_H
