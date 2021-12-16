//
// Created by bonychops on 11/12/21.
//


#ifndef PROG_GAME_BLOCK_H
#define PROG_GAME_BLOCK_H

#define BLOCK_RC_SIZE 32

#include "../Object.h"
#include "../ResourceManager.h"
#include <functional>

typedef ResourceManager RCM;

class Block : public Object {
public:
    P p;

    Block(){
        //Block((P){0, 0});
        invalid = true;
    }


    Block(P p) : Object(){
        collision = new Collision(Collision::SQUARE, (P) {p.x, p.y}, (P) {p.x + 1, p.y + 1});
        this->p = p;
    }

    ~Block(){
    }


    void draw(function<P(P)> fp, float scale) {
        Image rc = RCM::GetImage("../images/objects/block.png");
        //cout << scale << endl;
        P bufP = (fp((P) {
                .x = p.x  ,
                .y = p.y
        }));
        rc.putSprite(bufP, scale / BLOCK_RC_SIZE);
    }

    Collision *collision;

};

#endif //PROG_GAME_BLOCK_H
