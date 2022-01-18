//
// Created by bonychops on 17/12/21.
//

#ifndef PROG_GAME_SEGMENT_H
#define PROG_GAME_SEGMENT_H

#include "Cable.h"
#include "../Define.h"
#include "../CableAttachableObject.h"

class Segment : public CableAttachableObject {
public:

    Segment() {
        //Block((P){0, 0});
        invalid = true;
    }


    Segment(P p) : CableAttachableObject(){
        type = SEGMENT;
        this->p = p;
        cableAttachable = true;
        cableSocket = (P) {
                p.x + (float) 0.5,
                p.y - (float) 0.5
        };
        cableExportable = true;
        cout << "I am " << this << endl;
        cable = Cable(cableSocket);
    }

    void draw(function<P(P)> fp, float scale){
        draw(fp, scale, false);
    }

    ~Segment() {
    }

    void draw(function<P(P)> fp, float scale, bool editorView) override {
        cable.draw(fp, scale, editorView);
        Image rc = powers[0] ?
                   RCM::GetImage("../images/objects/segment_on.png") :
                   RCM::GetImage("../images/objects/segment.png");
        //cout << this << endl;
        if (powers[0]) {
            cout << "ee" << endl;
        }
        P bufP = (fp((P) {
                .x = p.x,
                .y = p.y
        }));
        rc.putSprite(bufP, scale * (float)scaleAni.play()/ BLOCK_RC_SIZE);
    }

    void changePower(bool power) override {
        CableAttachableObject::changePower(power);
        cable.changePower(power);
    }

    void attachCable(CableAttachableObject *object) {
        P cablePos = (P){p.x + ( float)0.5, p.y - (float)0.5};
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

    Cable cable;
private:
    CableAttachableObject tmpObj;
};

#endif //PROG_GAME_SEGMENT_H
