//
// Created by bonychops on 16/12/21.
//

#include "Object.h"

bool Object::isCableAttachable() {
    return false;
}

void Object::draw(function<P(P)> fp, float scale) {
    //draw(fp, scale, false);
    return;
}

void Object::draw(function<P(P)> fp, float scale, bool editorView) {
    draw(fp, scale);
}

enum Object::Type Object::getType() {
    return type;
}