//
// Created by bonychops on 16/01/22.
//

#ifndef PROG_GAME_ERASER_H
#define PROG_GAME_ERASER_H
#include "../Define.h"
#include "../Object.h"
#include "../Animator.h"
#include <functional>

class Eraser : public Object{
public:

    Eraser(){
        //Block((P){0, 0});
        invalid = true;
    }

    Eraser(P p) : Object() {
        type = ERASER;
        collisions.getCollisions()->push(Collision(Collision::SQUARE, (P) {p.x, p.y}, (P) {p.x + 1, p.y + 1}));
        this->p = p;
    }

    ~Eraser(){
    }

    void draw(function<P(P)> fp, float scale, bool editorView){
        draw(fp, scale);
    }

    void draw(function<P(P)> fp, float scale) override{
        Image rc = RCM::GetImage("../images/objects/eraser.png");
        //cout << scale << endl;
        P bufP = (fp((P) {
            .x = p.x  ,
            .y = p.y
        }));
        rc.putSprite(bufP, scale * ( (float)scaleAni.play()) / BLOCK_RC_SIZE);
    }

    nlohmann::json dumpJson() override {
        nlohmann::json data = {
                {"type", "ERASER"},
                {"pos", posToJson(this->p)}
        };
        return data;
    }

private:


};


#endif //PROG_GAME_ERASER_H
