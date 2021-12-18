//
// Created by bonychops on 17/12/21.
//

#ifndef PROG_GAME_INVALIDOBJECT_H
#define PROG_GAME_INVALIDOBJECT_H

#include "../Object.h"
#include "../CableAttachableObject.h"

class InvalidObject : public CableAttachableObject {
public:
    InvalidObject() {
        invalid = true;
        type = INVALID;
        cableAttachable = true;
    }

    void draw(function<P(P)> fp, float scale) override {}

    void changePower(bool power) {}

    P getCableSocket() { return (P) {0, 0}; }
};

#endif //PROG_GAME_INVALIDOBJECT_H
