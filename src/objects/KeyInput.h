//
// Created by bonychops on 16/12/21.
//

#ifndef PROG_GAME_KEYINPUT_H
#define PROG_GAME_KEYINPUT_H

#include "../Define.h"
#include "../Object.h"
#include "../Image.h"
#include "Cable.h"
#include "../KeyboardUtils.h"
#include "Cable.h"
#include <string>

typedef KeyboardUtils KBM;

class KeyInput : public Object {
public:
    char key;

    KeyInput() {
        invalid = true;
    }

    KeyInput(P p, char key){
        cableExportable = true;
        type = KEY_INPUT;
        this->p = p;
        this->key = key;
        cableSocket = (P) {
                p.x + (float) 0.5,
                p.y - (float) 0.5
        };
        cable = Cable(cableSocket);
    }

    ~KeyInput() {
    }

    void draw(function<P(P)> fp, float scale, bool editorView) override {
        cable.draw(fp, scale, editorView);
        bool power = KBM::getKeyboard(key, Keyboard::KEY);
        Image rc = power ?
                   RCM::GetImage("../images/objects/keyboard/" + string(1, key) + "_pressed.png") :
                   RCM::GetImage("../images/objects/keyboard/" + string(1, key) + ".png");;
        //cout << scale << endl;
        P bufP = (fp((P) {
                .x = p.x,
                .y = p.y
        }));
        rc.putSprite(bufP, scale * (float)scaleAni.play() / BLOCK_RC_SIZE);
        if(cable.getPower() != power){
            cable.changePower(power);
        }
    }

    void draw(function<P(P)> fp, float scale){
        draw(fp, scale, false);
    }

    void attachCable(CableAttachableObject *object) {
        P cablePos = {p.x + (float) 0.5, p.y + (float) 0.0};
        cable = Cable(cablePos, object);
    }

    void setCablePos(P p) override{
        tmpObj = CableAttachableObject();
        tmpObj.p = p;
        tmpObj.cableSocket = p;
        cout << tmpObj.getType() << endl;
        cable = Cable(cableSocket, &tmpObj);
    }

    void resetCable() override{
        cable = Cable();
    }


    P cableSocket;
private:
    Cable cable;
    CableAttachableObject tmpObj;

};


#endif //PROG_GAME_KEYINPUT_H
