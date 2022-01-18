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
#include <variant>
#include <fstream>

#include "../lib/json.hpp"

using namespace std;

typedef Object::Type OType;

FieldScene::FieldScene(WindowManager *windowManager) : FieldScene(windowManager, true){}

FieldScene::FieldScene(WindowManager *windowManager, bool editorMode) : map(), editorToggleKey('e', Keyboard::KEY), player(&map),
                                                       editorClicked(GLUT_LEFT_BUTTON, Keyboard::MOUSE),
                                                       headerAni(editorMode ? -150.0 : 0.0, editorMode ? 0.0 : -150.0, 1000, true),
                                                       rightKey(GLUT_KEY_RIGHT, Keyboard::SPECIAL),
                                                       leftKey(GLUT_KEY_LEFT, Keyboard::SPECIAL),
                                                       saveKey('s', Keyboard::KEY, GLUT_ACTIVE_CTRL),
                                                       loadKey('o', Keyboard::KEY, GLUT_ACTIVE_CTRL),
                                                       sKey('s', Keyboard::KEY),
                                                       eraser((P) {0, 0}),
                                                       objects{
                                                               Block((P) {0, 0}),
//                                                               KeyInput((P) {0, 0}, 'h'),
                                                               Spike((P) {0, 0}),
                                                               Goal((P) {0, 0}),
//                                                               Segment((P) {0, 0}),
//                                                               Cable((P) {0, 0})
                                                       },
                                                       targetObjectAni(0.0, 1.0, 100, true) {
    //map = Map();
    //player = Player(&map);
    this->bufSwitcher = !editorMode;
    this->w = windowManager;
    headerAni.mode = A_END_V0;
    if (this->editorMode) {
        this->editorView = true;
    }
    if (!editorView) {
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
    w->clearWithColor(20, 20, 20);
    //Image mountain = RCM::GetImage("../images/mountain.png");
    //mountain.putSprite(w->winP((P) {0, 0}), 0.3 * windowScale);

    glPointSize(2.0);
    glColor4ub(0, 0, 0, 10);

    if(!editorMode && player.dead){
        player.setP((P){0, 5}, true);
        player.dead = false;
    }

    if (editorView) {
        drawGrid();
        editorHandler(windowScale);
    }
    editorToggleHandler();

    map.drawAll(fpl, 32 * windowScale, editorView && editorMode);

    player.draw(fpl, 32 * windowScale, true, editorView && editorMode);
    fieldP = (P) {
            player.p.x * BLOCK_RC_SIZE > WINDOW_W / 2 ? -player.p.x * BLOCK_RC_SIZE + (WINDOW_W / 2) : 0,
            player.p.y * BLOCK_RC_SIZE > WINDOW_H / 2 ? player.p.y * BLOCK_RC_SIZE + (WINDOW_H / 2) : WINDOW_H,
    };

    player.drawResource(fpl, 32 * windowScale);

    drawEditorUI(windowScale);

}

void FieldScene::drawGrid() {
    int screenSizeW = (WINDOW_W / BLOCK_RC_SIZE);
    int screenSizeH = (WINDOW_W / BLOCK_RC_SIZE);

    glColor4ub(100, 100, 100, 25);
    for (int i = player.p.x - screenSizeW; i < player.p.x + screenSizeW; ++i) {
        Drawer::drawLine(fp((P) {(float) i, player.p.y - screenSizeH}),
                         fp((P) {(float) i, player.p.y + screenSizeH}));
    }

    for (int i = player.p.y - screenSizeH; i < player.p.y + screenSizeH; ++i) {
        Drawer::drawLine(fp((P) {player.p.x - screenSizeW, (float) i}),
                         fp((P) {player.p.x + screenSizeW, (float) i}));
    }
}

void FieldScene::generateFromJson(nlohmann::json &j) {
    cout << j["map"].dump() << endl;
    map.setFromJson(j);

    player.setP((P){0, 5}, true);
    //this->map = Map((nlohmann::json)j);
}

void FieldScene::editorHandler(float windowScale) {

    bool mousePressed = false;
    AllObject targetObject = MouseUtils::getKeyboard(GLUT_RIGHT_BUTTON, Keyboard::MOUSE) ? eraser
                                                                                         : objects[targetObjectPos];
    OType objectType = std::visit([](auto &o) { return o.getType(); }, targetObject);



    if (rightKey.check() && !cableEditorMode) {
        if (targetObjectPos >= TARGETS - 1) {
            targetObjectPos = 0;
        } else {
            targetObjectPos += 1;
        }
        targetObjectAni = Animator(0.0, 1.0, 100, true);
    }
    if (leftKey.check() && !cableEditorMode) {
        if (targetObjectPos <= 0) {
            targetObjectPos = TARGETS - 1;
        } else {
            targetObjectPos -= 1;
        }
        targetObjectAni = Animator(0.0, 1.0, 100, true);
    }

    switch (objectType) {
        case OType::BLOCK:
        case OType::SPIKE:
            mousePressed = MouseUtils::getKeyboard(GLUT_LEFT_BUTTON, Keyboard::MOUSE);
            break;
        case OType::CABLE:
            mousePressed = MouseUtils::getKeyboard(GLUT_LEFT_BUTTON, Keyboard::MOUSE);
            //cout << "a" << endl;
            break;
        case OType::ERASER:
            mousePressed = MouseUtils::getKeyboard(GLUT_RIGHT_BUTTON, Keyboard::MOUSE);
            break;
        default:
            mousePressed = editorClicked.check();
            break;
    }
    if (KeyboardUtils::getKeyboard('0', Keyboard::KEY)) {
        moveToFirstPosX = Animator((double) player.p.x, 3.0, 50, true);
        moveToFirstPosY = Animator((double) player.p.y, 3.0, 50, true);
    }
    if (!moveToFirstPosX.played || !moveToFirstPosY.played) {
        player.p = {(float) moveToFirstPosX.play(), (float) moveToFirstPosY.play()};
    }

    if (saveKey.check()) {
        string fileName;
        cout << "Type stage name to save: ";
        std::cin >> fileName;
        nlohmann::json data = map.dumpJson();
        std::ofstream writing_file("../assets/maps/" + fileName + ".map.json");
        writing_file << data.dump(4) << std::endl;
        cout << "Saved! Now you can go back to GUI screen." << endl;
    }

    if (loadKey.check()) {
        string fileName;
        nlohmann::json j = R"(
  {
    "map": []
  }
)"_json;
        cout << "Type stage name to load: ";
        std::cin >> fileName;
        std::ifstream read_file("../assets/maps/" + fileName + ".map.json");
        read_file >> j;

        generateFromJson(j);
        cout << "Loaded! Now you can go back to GUI screen." << endl;
    }

    if (mousePressed || cableEditorMode) {
        P p = MouseUtils::p;
        P tmpP = unFp(p);
        P fieldP = {
                floor(tmpP.x),
                ceil(tmpP.y),
        };
        int objectNearObjI = map.objectManager.CheckObjectWithIndex(fieldP);
        AllObject *objectNearPointer = map.objectManager.CheckObject(objectNearObjI);
        if (!cableEditorMode) {
            if (objectNearPointer == nullptr) {
                cout << "comeon" << endl;
                switch (objectType) {
                    case OType::BLOCK:
                        map.addObject(Block(fieldP));
                        break;
                    case OType::KEY_INPUT:
                        map.addObject(KeyInput(fieldP, 'h'));
                        break;
                    case OType::SEGMENT:
                        map.addObject(Segment(fieldP));
                        break;
                    case OType::GOAL:
                        map.addObject(Goal(fieldP));
                        break;
                    case OType::ERASER:
                        break;
                    case OType::SPIKE:
                        map.addObject(Spike(fieldP));
                        break;

                }
            } else if (objectNearPointer != nullptr && objectType == OType::CABLE && !cableEditorMode) {
                bool cableAttachable = visit([](auto o) {
                    if (!o.isCableExportable()) {
                        return false;
                    }
                    if (o.isCableExported()) {
                        o.resetCable();
                        return false;
                    }
                    return true;
                }, *objectNearPointer);
                if (!cableAttachable) {
                    return;
                }
                cout << "grab" << endl;
                cableFromObject = objectNearPointer;
                cableEditorMode = true;

                visit([tmpP](auto &o) {
                    o.setCablePos(tmpP);
                }, *objectNearPointer);
            } else if (objectNearPointer != nullptr && objectType == OType::ERASER) {
                map.objectManager.deleteObject(objectNearObjI);
            }
        } else {
            cout << "a" << endl;
            visit([tmpP](auto &o) {
                o.setCablePos(tmpP);
            }, *cableFromObject);
            if (!MouseUtils::getKeyboard(GLUT_LEFT_BUTTON, Keyboard::MOUSE)) {
                if (objectNearPointer == nullptr || objectNearPointer) {
                    visit([](auto &o) {
                        o.resetCable();
                    }, *cableFromObject);
                } else {
                    /*bool result = visit([this](auto dist){
                        return visit([dist](auto &src){
                            return src.attachCable((Object)dist);
                        }, *cableFromObject);
                    }, *objectNearPointer); */
                }

                cableEditorMode = false;
            }
        }
    }
}

void FieldScene::drawEditorUI(float windowScale) {
    if(!editorMode){
        return;
    }
    AllObject targetObject = MouseUtils::getKeyboard(GLUT_RIGHT_BUTTON, Keyboard::MOUSE) ? eraser
                                                                                         : objects[targetObjectPos];
    float y = (float) headerAni.play();
    Image header = RCM::GetImage("../images/editorBar.png");
    header.putSprite(w->winP((P) {0, y}), (float) windowScale);
    function<P(P)> winPl = [this](P p) {
        return w->winP(p);
    };
    targetObjectAni.play();
    std::visit([winPl, windowScale, this, y](auto &o) {
        o.p = {WINDOW_W / 2 - BLOCK_RC_SIZE / 2, 25 + y};
        o.scaleAni = targetObjectAni;
        o.draw(winPl, windowScale * BLOCK_RC_SIZE * 1, true);
    }, targetObject);

}

void FieldScene::editorToggleHandler() {
    if (bufSwitcher|| ((player.dead || player.clear) && editorMode) ||(  editorMode && editorToggleKey.check() && !cableEditorMode) ){
        if ((editorView && editorMode ) || bufSwitcher) {
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
            P playerP = player.p;
            map = tmpMap;
            player = Player(&map);
            player.setP(playerP, true);
            editorView = true;
        }
        if(bufSwitcher){
            editorMode = false;
            bufSwitcher = false;
        }
    }
}
