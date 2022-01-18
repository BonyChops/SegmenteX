//
// Created by bonychops on 16/12/21.
//

#include "Object.h"

Object::Object() : scaleAni(0.0, 1.0, 100, true) {

}

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

void Object::setCablePos(P p) {
    return;
}

bool Object::isCableExportable() {
    return cableExportable;
}

bool Object::isCableExported() {
    return cableExported;
}

void Object::resetCable() {
    return;
}

bool Object::attachCable(Object *o) {
    return false;
}

nlohmann::json Object::posToJson(P p) {
    nlohmann::json data = {
            {"x", p.x},
            {"y", p.y}
    };
    return data;
}

nlohmann::json Object::dumpJson() {
    nlohmann::json data = {
            {"type", "INVALID"},
            {"pos", posToJson((P){0, 0})}
    };
    return data;
}

