//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_SCENEMANAGER_H
#define PROG_GAME_SCENEMANAGER_H

#include "FieldScene.h"
#include "WindowManager.h"
#include "Drawer.h"
#include "Point.h"

typedef Point P;

class SceneManager {
public:
    FieldScene *fieldScene;

    SceneManager(WindowManager *windowManager) {
        this->w = windowManager;
        fieldScene = new FieldScene(windowManager);
    }
    ~SceneManager(){
        delete w;
    }

    void Draw() {
        fieldScene->Draw();
        if (((float)w->m_windowW / (float)WINDOW_W) < ((float)w->m_windowH/(float)WINDOW_H)) {
            Drawer::Square((P) {0, 0}, w->winP((P){WINDOW_W, 0}));
            Drawer::Square(w->winP((P) {0, WINDOW_H}), ((P){(float)w->m_windowW, (float)w->m_windowH}));
        }else{
            Drawer::Square((P) {0, 0}, w->winP((P){0, WINDOW_H}));
            Drawer::Square(w->winP((P) {WINDOW_W, 0}), ((P){(float)w->m_windowW, (float)w->m_windowH}));
        }
    }


private:
    WindowManager *w;
};

#endif //PROG_GAME_SCENEMANAGER_H
