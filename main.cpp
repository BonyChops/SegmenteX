#include <iostream>
#include<GL/gl.h>

#include "src/Define.h"

#include "src/WindowManager.h"
#include "src/KeyboardUtils.h"
#include "src/SceneManager.h"
#include "src/MouseUtils.h"
#include "src/Point.h"

typedef Point P;

WindowManager *windowManager;
SceneManager *sceneManager;

using namespace std;

void Display(void);

void Loop(int value);

void Keyboard(unsigned char, int, int);

void KeyboardUp(unsigned char, int, int);

void Special(int, int, int);

void SpecialUp(int, int, int);

void Mouse(int, int, int, int);

void Motion(int, int);


int main(int argc, char **argv) {
    windowManager = new WindowManager(argc, argv);
    windowManager->setWindowTitle("Clock");
    WindowManager::setBufWindowManager(windowManager);
    windowManager->setWindowSize(WINDOW_W, WINDOW_H);
    windowManager->InitDisplay(argc, argv);
    glutDisplayFunc(Display);
    glutTimerFunc(FRAME, Loop, 0);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(Special);
    glutSpecialUpFunc(SpecialUp);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutIgnoreKeyRepeat(GL_TRUE);
    glutSpecialFunc(Special);
    sceneManager = new SceneManager(windowManager);
    windowManager->Start();
    return 0;
}

void Display() {
    glFlush();
    glutSwapBuffers();
    glutTimerFunc(FRAME, Loop, 0);
}

void Keyboard(unsigned char c, int x, int y) {
    KeyboardUtils::updateKeyboard((int) c, Keyboard::KEY, true);
}

void KeyboardUp(unsigned char c, int x, int y) {
    KeyboardUtils::updateKeyboard((int) c, Keyboard::KEY, false);
}

void Special(int c, int x, int y) {
    KeyboardUtils::updateKeyboard(c, Keyboard::SPECIAL, true);
}

void SpecialUp(int c, int x, int y) {
    KeyboardUtils::updateKeyboard(c, Keyboard::SPECIAL, false);
}

void Mouse(int b, int s, int x, int y){
    MouseUtils::updateKeyboard(b, Keyboard::MOUSE, s == GLUT_DOWN);
    MouseUtils::p = ((P){(float)x, (float)y});
}

void Motion(int x, int y){
    MouseUtils::p = ((P){(float)x, (float)y});
}

void Loop(int value) {
    typedef KeyboardUtils K;
//    windowManager->clearWithColor(!K::getKeyboard('r', Keyboard::KEY) ? 0 : 255, !K::getKeyboard(GLUT_KEY_UP, Keyboard::SPECIAL) ? 0 : 255,
//                                  !K::getKeyboard('b', Keyboard::KEY) ? 0 : 255);
    sceneManager->Draw();
    glFlush();
    glutSwapBuffers();
    glutTimerFunc(FRAME, Loop, 0);
}