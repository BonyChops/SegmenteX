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

    static void drawLine(P p1, P p2) {
        glBegin(GL_POINTS);
        int length = (int) sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
        Animator xLiner(p1.x, p2.x, length);
        Animator yLiner(p1.y, p2.y, length);
        for (int i = 0; i < length; i++) {
            glVertex2i((int) xLiner.play(), (int) yLiner.play());
        }
        glEnd();
    }
};

#endif //PROG_GAME_DRAWER_H
