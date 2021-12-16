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

FieldScene::FieldScene(WindowManager *windowManager) {
    this->w = windowManager;
    this->map = new Map;
    this->player = new Player(*this->map);
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
    glColor3ub(255, 255, 255);

    function<P(P)> fpl = [this](P p) {
        return w->winP((P) {
                .x = fieldP.x + (p.x * BLOCK_RC_SIZE),
                .y = fieldP.y - (p.y * BLOCK_RC_SIZE)
        });
    };
    map->drawAll(fpl, 32 * windowScale);
    player->draw(fpl, 32 * windowScale, true);
    fieldP = (P){
            player->p.x *  BLOCK_RC_SIZE > WINDOW_W / 2 ? -player->p.x * BLOCK_RC_SIZE + (WINDOW_W / 2) : 0,
            player->p.y * BLOCK_RC_SIZE + (WINDOW_H / 2),
    };

    player->drawResource(fpl, 32 * windowScale);
}