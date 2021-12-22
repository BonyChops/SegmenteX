//
// Created by bonychops on 12/12/21.
//

#include "Define.h"
#include "SceneManager.h"
#include <GL/gl.h>
#include <functional>
#include "Point.h"
#include "Drawer.h"
#include "WindowManager.h"
#include "Map.h"
#include "FieldScene.h"

using namespace std;

FieldScene::FieldScene(WindowManager *windowManager) : map() {
    this->w = windowManager;
    //this->map = Map();
    this->player = new Player(&this->map);
}

FieldScene::~FieldScene() {
    //TODO: Segmentation Fault
    //delete w;
    //delete map;
    //delete player;
}

P FieldScene::fp(P p) {
    return w->winP((P) {
            .x = fieldP.x + p.x * BLOCK_RC_SIZE,
            .y = fieldP.y - p.y * BLOCK_RC_SIZE
    });
}

void FieldScene::Draw(float windowScale) {
    w->clearWithColor(0, 100, 200);



    function<P(P)> fpl = [this](P p) {
        return w->winP((P) {
                .x = fieldP.x + (p.x * BLOCK_RC_SIZE),
                .y = fieldP.y - (p.y * BLOCK_RC_SIZE)
        });
    };

    Image mountain = RCM::GetImage("../images/mountain.png");
    mountain.putSprite(w->winP((P) {0, 0}), 0.3 * windowScale);

    glPointSize(2.0);
    glColor4ub(0, 0, 0, 10);
    if (editorView) {
        drawGrid();
    }

    map.drawAll(fpl, 32 * windowScale, editorView);

    player->draw(fpl, 32 * windowScale, true, editorView);
    fieldP = (P) {
            player->p.x * BLOCK_RC_SIZE > WINDOW_W / 2 ? -player->p.x * BLOCK_RC_SIZE + (WINDOW_W / 2) : 0,
            player->p.y * BLOCK_RC_SIZE + (WINDOW_H / 2),
    };

    player->drawResource(fpl, 32 * windowScale);
}

void FieldScene::drawGrid() {
    int screenSizeW = (WINDOW_W / BLOCK_RC_SIZE);
    int screenSizeH = (WINDOW_W / BLOCK_RC_SIZE);

    for (int i = player->p.x - screenSizeW; i < player->p.x + screenSizeW; ++i) {
        Drawer::drawLine(fp((P) {(float) i, player->p.y - screenSizeH}),
                         fp((P) {(float) i, player->p.y + screenSizeH}));
    }

    for (int i = player->p.y - screenSizeH; i < player->p.y + screenSizeH; ++i) {
        Drawer::drawLine(fp((P) {player->p.x - screenSizeW, (float) i}),
                         fp((P) {player->p.x + screenSizeW, (float) i}));
    }
}