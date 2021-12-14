//
// Created by bonychops on 11/12/21.
//

#ifndef PROG_GAME_IMAGE_H
#define PROG_GAME_IMAGE_H

#include <GL/glpng.h>
#include <GL/glut.h>
#include <math.h>
#include "Point.h"

#include <iostream>
#include <string>

typedef Point P;

using namespace std;

class Image {
public:
    GLuint img;
    pngInfo info;
    string filename;

    Image(){

    }


    Image(string filename) {
        ////cout << filename << endl;
        img = pngBind(filename.c_str(), PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
        this->filename = filename;
        ////cout << "IMG NUM is: " << img << endl;
        if(img == 0){
            cerr << "[!]FAILED TO LOAD RESOURCE: " + filename << endl;
        }
    }

    void putSprite(P p) {
        putSprite(p, 1.0);
    }
    void putSprite(P p, double scale) {
        putSprite(p, scale, 0.0);
    }
    void putSprite(P p, double scale, double angle) {
        putSprite(p, scale, angle, 255);
    }

    void putSprite(P pos, double scale, double angle, int alpha) {
        m_x = pos.x;
        m_y = pos.y;
        double w = (double)info.Width * scale;
        double h = (double)info.Height * scale;

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, img);
        glColor4ub(255, 255, 255, alpha);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        float x, y;
        P p;
        x = 0;
        y = 0;
        p = pCalc((P){(float)x, (float)y});
        glVertex2f(p.x, p.y);

        glTexCoord2i(0, 1);
        x = 0;
        y = h;
        p = pCalc((P){(float)x, (float)y});
        glVertex2f(p.x, p.y);


        glTexCoord2i(1, 1);
        x = w;
        y = h;
        p = pCalc((P){(float)x, (float)y});
        glVertex2f(p.x, p.y);


        glTexCoord2i(1, 0);
        x = w;
        y = 0;
        p = pCalc((P){(float)x, (float)y});
        glVertex2f(p.x, p.y);


        glEnd();

        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

private:
    float m_x;
    float m_y;

    P pCalc(P p){
        return (P){
            .x = p.x + m_x,
            .y = p.y + m_y
        };
    }

    int px(int x) {
        return x + m_x;
    }

    int py(int y) {
        return y + m_y;
    }
};

#endif //PROG_GAME_IMAGE_H
