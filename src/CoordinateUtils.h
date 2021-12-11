//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_COORDINATEUTILS_H
#define PROG_GAME_COORDINATEUTILS_H

#include "Point.h"
typedef Point P;
class CoodinateUtils{
public:
    static bool IsInsideBox(P p, P p1, P p2){
        return IsInside1(p.x, p1.x, p2.x) && IsInside1(p.y, p1.y, p2.y);
    }
    static bool IsInside1(float p, float p1, float p2){
        return p1 < p2 ? (p1 <= p && p <= p2) : (p2 <= p && p <= p1);
    }

};

#endif //PROG_GAME_COORDINATEUTILS_H
