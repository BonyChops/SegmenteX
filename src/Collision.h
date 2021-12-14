//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_COLLISION_H
#define PROG_GAME_COLLISION_H

#include <functional>
#include <array>
#include <iostream>
#include "Point.h"
#include "CoordinateUtils.h"
#include "Animator.h"

typedef Point P;

using namespace std;

class Collision {
public:

    enum Type {
        SQUARE,
        INVALID_COLLISION
    };
    P p1 = {0, 0};
    P p2 = {0, 0};

    Collision() {
        Collision(INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
    }

    Collision(enum Type type, P p1, P p2) {
        this->type = type;
        this->p1 = p1;
        this->p2 = p2;
    }

    bool CheckCollision(P p) {
        return CoodinateUtils::IsInsideBox(p, p1, p2);
    }

//    template<int A>
//    array<P, A> genP() {
//        array<P, A> tmp;
//        for (int i = 0; i < A; ++i) {
//            cout << p1.y << endl;
//            P p1 = this->p1, p2 = this->p2;
//            tmp[i] = (P) {
//                    ((p2.x - p1.x) * i / (A - 1)) + p1.x,
//                    ((p2.y - p1.y) * i / (A - 1)) + p1.y
//            };
//            cout << p1.y << endl;
//        }
//        return tmp;
//    }
    template<int A>
    array<P, A> genP() {
        array<P, A> tmp{0};
        /*tmp[0] = (P){p1.x, p1.y};
        tmp[1] = (P){p1.x, p2.y};
        tmp[2] = (P){p2.x, p2.y};
        tmp[3] = (P){p2.x, p1.y};*/
        Animator a(0, 0, 0);
        for (int i = 0; i < 4; ++i) {
            switch (i) {
                case 0:
                    a = Animator(p1.y, p2.y, A / 4);
                    break;
                case 1:
                    a = Animator(p1.x, p2.x, A / 4);
                    break;
                case 2:
                    a = Animator(p2.y, p1.y, A / 4);
                    break;
                case 3:
                    a = Animator(p2.x, p1.x, A / 4);
                    break;

            }
            for (int j = 0; j < A / 4; ++j) {
                switch (i) {
                    case 0:
                        tmp[(A / 4) * i + j] = (P) {p1.x, (float) a.play()};
                        break;
                    case 1:
                        tmp[(A / 4) * i + j] = (P) {(float) a.play(), p2.y};
                        break;
                    case 2:
                        tmp[(A / 4) * i + j] = (P) {p2.x, (float) a.play()};
                        break;
                    case 3:
                        tmp[(A / 4) * i + j] = (P) {(float) a.play(), p1.y};
                        break;
                }
            }
        }
        return tmp;
        for (int i = 0; i < A; ++i) {
            cout << p1.y << endl;
            tmp[i] = (P) {
                    0, 0
            };
        }
        return tmp;
    }


    enum Type getType() {
        return type;
    }

    Collision duplicate() {
        return Collision(type, p1, p2);
    }

    void updateP(P p1, P p2) {
        this->p1 = p1;
        this->p2 = p2;
    }

private:
    enum Type type = SQUARE;

};

#endif //PROG_GAME_COLLISION_H
