//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_FIELDSCENE_H
#define PROG_GAME_FIELDSCENE_H

#include "WindowManager.h"
#include "Map.h"
#include "Point.h"
#include "Player.h"
#include "KeyboardManager.h"
#include <array>

typedef Point P;

#define TARGETS 3

class FieldScene {
public:
    FieldScene(WindowManager *windowManager);

    FieldScene(WindowManager *windowManager, bool editorMode);

    ~FieldScene();

    P fp(P p);

    P unFp(P p);

    void Draw(float windowScale);

    void drawGrid();

    void editorHandler(float windowScale);

    void drawEditorUI(float windowScale);

    void editorToggleHandler();

    Map map;


    void generateFromJson(nlohmann::json &j);

    Player player;
private:
    P fieldP = {0, WINDOW_H - 20};
    WindowManager *w;
    Map tmpMap;
    bool editorView = false;
    bool editorMode = true;
    bool bufSwitcher = false;
    KeyboardManager editorToggleKey;
    KeyboardManager editorClicked;
    Animator headerAni;
    int targetObjectPos = 0;
    AllObject objects[TARGETS];
    Animator targetObjectAni;
    KeyboardManager rightKey;
    KeyboardManager leftKey;
    KeyboardManager sKey;
    KeyboardManager saveKey;
    KeyboardManager loadKey;
    Animator moveToFirstPosX;
    Animator moveToFirstPosY;
    bool cableEditorMode = false;
    AllObject *cableFromObject;
    Eraser eraser;

    function<P(P)> fpl = [this](P p) {
        return w->winP((P) {
                .x = fieldP.x + (p.x * BLOCK_RC_SIZE),
                .y = fieldP.y - (p.y * BLOCK_RC_SIZE)
        });
    };

};

#endif //PROG_GAME_FIELDSCENE_H
