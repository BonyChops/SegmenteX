//
// Created by bonychops on 16/12/21.
//

#include "Object.h"

bool Object::isCableAttachable() {
    return false;
}

void Object::draw(function<P(P)> fp, float scale) {
    return;
}

enum Object::Type Object::getType() {
    return type;
}