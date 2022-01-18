//
// Created by bonychops on 17/12/21.
//

#ifndef PROG_GAME_CABLE_H
#define PROG_GAME_CABLE_H


#include "../Define.h"
#include "../Object.h"
#include "../Drawer.h"

#include "../CableAttachableObject.h"

#include <functional>


class Cable : public Object{
public:
    Cable(){
        invalid = true;
        type = CABLE;
    }

    Cable(P p){
        this->p = p;
        invalid = true;
        type = CABLE;
    }


    Cable(P p, CableAttachableObject* target){
        cerr << "Hi!" << endl;
        this->target = target;
        type = CABLE;
        this->p = p;
        cout << target->getType() << endl;
    }

    void draw(function<P(P)> fp, float scale, bool editorView) override{
        if(invalid || target->getType() == Object::INVALID){
            if(editorView) {
                Image rc = RCM::GetImage("../images/objects/cable.png");
                //cout << scale << endl;
                P bufP = (fp((P) {
                        .x = p.x,
                        .y = p.y
                }));
                rc.putSprite(bufP, scale * ((float) scaleAni.play()) / BLOCK_RC_SIZE);
            }
            return;
        }
        //cout << scale << endl;
        P test = target->getCableSocket();
        power ? glColor3ub(255, 255, 0) :glColor3ub(100, 100, 100);
        glPointSize(scale * 0.2);
        Drawer::drawLine(fp(p), fp(target->getCableSocket()));
    }

    void draw(function<P(P)> fp, float scale) override{
        draw(fp, scale, false);
    }

    void changePower(bool power){
        if(invalid || target == nullptr|| target->getType() == INVALID){
            return;
        }
        cout << target->getType() << endl;
        target->changePower(power);
        this->power = power;
    }

    bool getPower(){
        return power;
    }



private:
    CableAttachableObject* target;
    bool power = false;
};


#endif //PROG_GAME_CABLE_H
