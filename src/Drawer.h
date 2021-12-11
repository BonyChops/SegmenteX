//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_DRAWER_H
#define PROG_GAME_DRAWER_H

#include <GL/gl.h>
#include "Point.h"
typedef Point P;
class Drawer{
public:
    static void Square(P p1, P p2){
        glBegin(GL_QUADS);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p1.x, p2.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p2.x, p1.y);
        glEnd();
    }
};

#endif //PROG_GAME_DRAWER_H
