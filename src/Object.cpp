//
// Created by bonychops on 16/12/21.
//

#include "Object.h"

bool Object::isCableAttachable() {
    return cableAttachable;
}

enum Object::Type Object::getType() {
    return type;
}