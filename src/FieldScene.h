//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_FIELDSCENE_H
#define PROG_GAME_FIELDSCENE_H

#include "WindowManager.h"
#include "Map.h"
#include "Point.h"

typedef Point P;

class FieldScene {
public:
    FieldScene(WindowManager *windowManager);

    ~FieldScene();

    P fp(P p);

    void Draw();

private:
    P fieldP = {0, WINDOW_H - 20};
    WindowManager *w;
    Map *map;

};

#endif //PROG_GAME_FIELDSCENE_H
