//
// Created by bonychops on 11/12/21.
//


#ifndef PROG_GAME_BLOCK_H
#define PROG_GAME_BLOCK_H

#include "../Define.h"
#include "../Object.h"
#include <functional>


class Block : public Object {
public:

    Block(){
        //Block((P){0, 0});
        invalid = true;
    }


    Block(P p) : Object(){
        type = BLOCK;
        collisions.getCollisions()->push(Collision(Collision::SQUARE, (P) {p.x, p.y}, (P) {p.x + 1, p.y + 1}));
        this->p = p;
    }

    ~Block(){
    }


    void draw(function<P(P)> fp, float scale) override{
        Image rc = RCM::GetImage("../images/objects/block.png");
        //cout << scale << endl;
        P bufP = (fp((P) {
                .x = p.x  ,
                .y = p.y
        }));
        rc.putSprite(bufP, scale / BLOCK_RC_SIZE);
    }


};

#endif //PROG_GAME_BLOCK_H
