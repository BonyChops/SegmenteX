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
#include "MouseUtils.h"

using namespace std;

FieldScene::FieldScene(WindowManager *windowManager) : map(), editorToggleKey('e', Keyboard::KEY), player(&map),
                                                       editorClicked(GLUT_LEFT_BUTTON, Keyboard::MOUSE),
                                                       headerAni(-150.0, 0, 1000, true) {
    this->w = windowManager;
    headerAni.mode = A_END_V0;
    if(this->editorMode){
        this->editorView = true;
    }
    if(!editorView){
        headerAni = Animator(-150.0, 0, 1000, true);
    }
    //this->map = Map();
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

P FieldScene::unFp(P p) {
    P tmpP = w->unwinP(p);
    return (P) {
            ((tmpP.x - fieldP.x) / BLOCK_RC_SIZE),
            ((tmpP.y + fieldP.y) / BLOCK_RC_SIZE)
    };
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
        editorHandler();
    }
    editorToggleHandler();

    map.drawAll(fpl, 32 * windowScale, editorView);

    player.draw(fpl, 32 * windowScale, true, editorView);
    fieldP = (P) {
            player.p.x * BLOCK_RC_SIZE > WINDOW_W / 2 ? -player.p.x * BLOCK_RC_SIZE + (WINDOW_W / 2) : 0,
            player.p.y * BLOCK_RC_SIZE + (WINDOW_H / 2),
    };

    player.drawResource(fpl, 32 * windowScale);

    drawEditorUI(windowScale);

}

void FieldScene::drawGrid() {
    int screenSizeW = (WINDOW_W / BLOCK_RC_SIZE);
    int screenSizeH = (WINDOW_W / BLOCK_RC_SIZE);

    for (int i = player.p.x - screenSizeW; i < player.p.x + screenSizeW; ++i) {
        Drawer::drawLine(fp((P) {(float) i, player.p.y - screenSizeH}),
                         fp((P) {(float) i, player.p.y + screenSizeH}));
    }

    for (int i = player.p.y - screenSizeH; i < player.p.y + screenSizeH; ++i) {
        Drawer::drawLine(fp((P) {player.p.x - screenSizeW, (float) i}),
                         fp((P) {player.p.x + screenSizeW, (float) i}));
    }
}

void FieldScene::editorHandler() {
    bool mousePressed = false;
    typedef Object::Type OType;
    OType objectType = Object::BLOCK;
    switch (objectType) {
        case OType::BLOCK:
            mousePressed = MouseUtils::getKeyboard(GLUT_LEFT_BUTTON, Keyboard::MOUSE);
            break;
        default:
            mousePressed = editorClicked.check();
            break;
    }
    if (mousePressed) {
        P p = MouseUtils::p;
        P tmpP = unFp(p);
        cout << tmpP.y << endl;
        P fieldP = {
                floor(tmpP.x),
                ceil(tmpP.y),
        };
        bool result = map.objectManager.CheckObject(fieldP);
        if (!result) {
            cout << "comeon" << endl;
            switch (objectType) {
                case OType::BLOCK:
                    map.addObject(Block(fieldP));
                    break;
                case OType::KEY_INPUT:
                    map.addObject(KeyInput(fieldP, 'h'));
            }
        }
    }
}

void FieldScene::drawEditorUI(float windowScale) {
    Image header = RCM::GetImage("../images/editorBar.png");
    header.putSprite(w->winP((P) {0, (float) headerAni.play()}), (float) windowScale);
}

void FieldScene::editorToggleHandler() {
    if (editorMode && editorToggleKey.check()) {
        if (editorView) {
            tmpMap = map;
            P playerP = player.p;
            player = Player(&map);
            player.setP(playerP, true);
            headerAni = Animator(0, -150.0, 50, true);
            headerAni.mode = A_BEGIN_V0;
            editorView = false;
        } else {
            headerAni = Animator(-150.0, 0, 500, true);
            headerAni.mode = A_END_V0;
            map = tmpMap;
            editorView = true;
        }
    }
}
