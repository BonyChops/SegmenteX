//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_WINDOWMANAGER_H
#define PROG_GAME_WINDOWMANAGER_H

#include <GL/glpng.h>
#include <GL/glut.h>
#include <math.h>

#include "Animator.h"
#include "Define.h"
#include "Point.h"

#define NORMAL 0
#define CENTER 1
using namespace std;
typedef Point P;

class WindowManager {
public:
    WindowManager(int argc, char **argv) {
        //InitDisplay(argc, argv);
    }
    ~WindowManager(){
        delete bufWindowManager;
    }

    static void ReshapeHandler(int w, int h);

    static WindowManager *bufWindowManager;
    //static int bufWindowManager;
    static int sint;

    static void setBufWindowManager(WindowManager *windowManager);

    static WindowManager *getBufWindowManager();

    int drawMode = 0;

    void InitDisplay(int argc, char **argv);

    void setWindowTitle(const char *windowTitle);

    void setWindowSize(int w, int h);

    void Start();

    int px(int x);

    int py(int y);

    int toReadPosX(int x);

    int toReadPosY(int y);

    int m_windowW;
    int m_windowH;

    void clearWithColor(int r, int g, int b) {
        glBegin(GL_QUADS);
        glColor3ub(r, g, b);
        glVertex2i(0, 0);
        glVertex2i(m_windowW, 0);
        glVertex2i(m_windowW, m_windowH);
        glVertex2i(0, m_windowH);
        glEnd();
    }

    void drawLine(double x1, double y1, double x2, double y2) {
        int length = (int) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        Animator xLiner(x1, x2, length);
        Animator yLiner(y1, y2, length);
        for (int i = 0; i < length; i++) {
            glVertex2i((int) xLiner.play(), (int) yLiner.play());
        }
    }

    P winP(P p) {
        float w, h;
        if (((float)m_windowW / (float)WINDOW_W) < ((float)m_windowH/(float)WINDOW_H)) {
            h = m_windowW * WINDOW_H / WINDOW_W;
            w = m_windowW;
        } else {
            h = m_windowH;
            w = m_windowH * WINDOW_W / WINDOW_H;
        }
        return (P) {
                .x = p.x * w / WINDOW_W + ((m_windowW - w) / 2),
                .y = p.y * h / WINDOW_H + ((m_windowH - h) / 2)
        };
    }

private:
    int pos(char mode, int p);

    int toReadPos(char mode, int p);

    const char *m_windowTitle;
    bool m_windowInitialized = false;

};

#endif //PROG_GAME_WINDOWMANAGER_H
