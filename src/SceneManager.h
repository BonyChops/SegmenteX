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
    FieldScene fieldScene;

    SceneManager(WindowManager *windowManager) : fieldScene(windowManager) {
        this->w = windowManager;
        //fieldScene = new FieldScene(windowManager);
    }

    ~SceneManager() {
        delete w;
    }

    void Draw() {
        function<void()> edgeHandler;
        float windowScale;
        if (((float) w->m_windowW / (float) WINDOW_W) < ((float) w->m_windowH / (float) WINDOW_H)) {
            edgeHandler = [this]() {
                Drawer::Square((P) {0, 0}, w->winP((P) {WINDOW_W, 0}));
                Drawer::Square(w->winP((P) {0, WINDOW_H}), ((P) {(float) w->m_windowW, (float) w->m_windowH}));
            };
            windowScale = (float) w->m_windowW / (float) WINDOW_W;
        } else {
            edgeHandler = [this]() {
                Drawer::Square((P) {0, 0}, w->winP((P) {0, WINDOW_H}));
                Drawer::Square(w->winP((P) {WINDOW_W, 0}), ((P) {(float) w->m_windowW, (float) w->m_windowH}));
            };
            windowScale = (float) w->m_windowH / (float) WINDOW_H;
        }
        //cout << windowScale << endl;
        fieldScene.Draw(windowScale);
        edgeHandler();
    }


private:
    WindowManager *w;
};

#endif //PROG_GAME_SCENEMANAGER_H
