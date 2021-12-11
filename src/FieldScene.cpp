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
}

FieldScene::~FieldScene() {
    delete w;
    delete map;
}

P FieldScene::fp(P p) {
    return w->winP((P) {
            .x = p.x + fieldP.x,
            .y = p.y + fieldP.y
    });
}

void FieldScene::Draw() {
    glColor3ub(255, 255, 255);
    Drawer::Square(
            fp((P) {0, 0}), fp((P) {500, 100})
    );
    function<P(P)> fpl = [this](P p) {
        return w->winP((P) {
                .x = p.x + fieldP.x,
                .y = p.y + fieldP.y
        });
    };
    map->drawAll(fpl, 32);

}