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

typedef Point P;

class FieldScene {
public:
    FieldScene(WindowManager *windowManager);

    ~FieldScene();

    P fp(P p);

    P unFp(P p);

    void Draw(float windowScale);

    void drawGrid();

    void editorHandler();

    void drawEditorUI(float windowScale);

    void editorToggleHandler();

private:
    P fieldP = {0, WINDOW_H - 20};
    WindowManager *w;
    Map map;
    Map tmpMap;
    Player player;
    bool editorView = false;
    bool editorMode = true;
    KeyboardManager editorToggleKey;
    KeyboardManager editorClicked;
    Animator headerAni;
};

#endif //PROG_GAME_FIELDSCENE_H
