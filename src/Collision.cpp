//
// Created by bonychops on 16/12/21.
//

#include "Collision.h"

Collision::Collision() {
    Collision(INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
}

Collision::Collision(enum Type type, P p1, P p2) {
    this->type = type;
    this->p1 = p1;
    this->p2 = p2;
}

bool Collision::CheckCollision(P p) {
    return CoodinateUtils::IsInsideBox(p, p1, p2);
}

enum Collision::Type Collision::getType() {
    return type;
}

void Collision::updateP(P p1, P p2) {
    this->p1 = p1;
    this->p2 = p2;
}
