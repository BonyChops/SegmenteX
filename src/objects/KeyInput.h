//
// Created by bonychops on 16/12/21.
//

#ifndef PROG_GAME_KEYINPUT_H
#define PROG_GAME_KEYINPUT_H

#include "../Define.h"
#include "../Object.h"
#include "../Image.h"
#include "Cable.h"
#include "../KeyboardManager.h"
#include "Cable.h"
#include <string>

typedef KeyboardManager KBM;

class KeyInput : public Object {
public:
    char key;

    KeyInput() {
        invalid = true;
    }

    KeyInput(P p, char key) {
        type = KEY_INPUT;
        this->p = p;
        this->key = key;
    }

    ~KeyInput() {
    }

    void draw(function<P(P)> fp, float scale) override {
        bool power = KBM::getKeyboard(key, Keyboard::KEY);
        Image rc = power ?
                   RCM::GetImage("../images/objects/keyboard/" + string(1, key) + "_pressed.png") :
                   RCM::GetImage("../images/objects/keyboard/" + string(1, key) + ".png");;
        //cout << scale << endl;
        P bufP = (fp((P) {
                .x = p.x,
                .y = p.y
        }));
        rc.putSprite(bufP, scale / BLOCK_RC_SIZE);
        if(cable.getPower() != power){
            cable.changePower(power);
        }
        cable.draw(fp, scale);
    }

    void attachCable(CableAttachableObject *object) {
        P cablePos = {p.x + (float) 0.5, p.y + (float) 0.0};
        cable = Cable(cablePos, object);
    }


private:
    Cable cable;
};


#endif //PROG_GAME_KEYINPUT_H
