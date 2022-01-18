//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_SCENEMANAGER_H
#define PROG_GAME_SCENEMANAGER_H

#include "FieldScene.h"
#include "WindowManager.h"
#include "Drawer.h"
#include "Point.h"
#include <fstream>
#include <sstream>

typedef Point P;

class SceneManager {
public:
    FieldScene fieldScene;
    FieldScene sampleFieldScene;

    SceneManager(WindowManager *windowManager) : fieldScene(windowManager), sampleFieldScene(windowManager, false) {
        //fieldScene(windowManager);
        this->w = windowManager;
        //fieldScene = new FieldScene(windowManager);
    }

    ~SceneManager() {
        delete w;
    }

    void Draw() {
        if (!sampleStage && KeyboardUtils::getKeyboard('y', Keyboard::KEY)) {
            sampleStage = true;
            sampleFieldScene.player.clear = true;
        }
        if (sampleFieldScene.player.clear) {
            sampleFieldScene.player.clear = false;
            sampleIndex += 1;
            if (sampleIndex == 6) {
                sampleIndex = 0;
                sampleStage = false;
            } else {


                nlohmann::json j = R"(
  {
    "map": []
  }
)"_json;
                string filename;
                stringstream ss;
                ss << sampleIndex;
                cout << "../assets/maps/sample/stg" + ss.str() + ".map.json" << endl;
                std::ifstream read_file("../assets/maps/sample/stg" + ss.str() + ".map.json");
                read_file >> j;
                sampleFieldScene.generateFromJson(j);
            }
        }
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

        sampleStage ? sampleFieldScene.Draw(windowScale) : fieldScene.Draw(windowScale);
        edgeHandler();
    }


private:
    WindowManager *w;
    bool sampleStage = false;
    int sampleIndex = 0;
};

#endif //PROG_GAME_SCENEMANAGER_H
