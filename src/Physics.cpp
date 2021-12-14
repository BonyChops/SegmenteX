//
// Created by bonychops on 12/12/21.
//

#include "Physics.h"

Physics::Physics() {
    cerr << "NOT ALLOWED WAY TO INIT!" << endl;
}

Physics::Physics(Collision *c, P p, Map *m) {
    this->x.x = p.x;
    this->y.x = p.y;
    this->collision = c;
    this->map = m;
    this->tm = TimeManager();
}

void Physics::getReadyForCalc(struct Params *bufX, struct Params *bufY, int dt, Collision *tmpC, bool isX) {
    *bufX = x;
    *bufY = y;
    isX ? calcParam(bufX, (float) dt) : calcParam(bufY, (float) dt);
    P p = getP(*bufX, *bufY);
    *tmpC = Collision(collision->getType(), collision->p1, collision->p2);
    tmpC->updateP(
            (P) {tmpC->p1.x + (isX ? (bufX->v * dt) : 0), tmpC->p1.y + (!isX ? (bufY->v * dt) : 0)},
            (P) {tmpC->p2.x + (isX ? (bufX->v * dt) : 0), tmpC->p2.y + (!isX ? (bufY->v * dt) : 0)}
    );
}

P Physics::calc() {
    int dt = tm.deltaTime();
    return (P) {
            calcFlow(dt, true).x,
            calcFlow(dt, false).y
    };
}

P Physics::calcFlow(int dt, bool isX) {
    //TODO: Change the way to check (far -> near) to (near -> far)
    struct Params bufX;
    struct Params bufY;
    Collision tmpC;
    getReadyForCalc(&bufX, &bufY, dt, &tmpC, isX);
    Collision *collision = map->CheckCollision(tmpC);
    //If there are no collision problems
    if ( collision->getType() == Collision::INVALID_COLLISION) {
        this->x = bufX;
        this->y = bufY;
        this->collision->updateP(tmpC.p1, tmpC.p2);
        //TODO: Segmentation Fault
        //delete tmpC;
        return getP(bufX, bufY);
    }
    //If Collided
    for (int i = dt; i > 0; i -= COLLISION_CALC_ACCURATE) {
        //TODO: Segmentation Fault
        //delete tmpC;
        getReadyForCalc(&bufX, &bufY, i, &tmpC, isX);
        array<P, COLLISION_POINTS_ACCURATE> arrayP = tmpC.genP<COLLISION_POINTS_ACCURATE>();
        bool ok = true;
        for (int j = 0; j < COLLISION_POINTS_ACCURATE; ++j) {
            if (collision->CheckCollision(arrayP[j])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            this->x = bufX;
            this->y = bufY;
            this->x.v = 0;
            this->y.v = 0;
            this->collision->updateP(tmpC.p1, tmpC.p2);
            //TODO: Segmentation Fault
            //delete tmpC;
            return getP(bufX, bufY);
        }

    }
    if(isX){
        this->x.v = 0;
    }else{
        this->y.v = 0;
    }
    //TODO: Segmentation Fault
    //delete tmpC;
    return getP(x, y);
}

//void Physics::updateCollision(bool isX, P p1, P p2, Collision *collision) {
//    collision->updateP(
//            (P){
//                isX ? p1.x : this.
//            },
//            (P){
//
//            }
//            )
//}

void Physics::calcParam(struct Params *params, float dt) {
    float dvx = params->a * dt;
    params->v = params->v + dvx;
    float dx = params->v * dt;
    params->x = params->x + dx;
}

P Physics::getP() {
    return (P) {x.x, y.x};
}

P Physics::getP(struct Params x, struct Params y) {
    return (P) {x.x, y.x};
}