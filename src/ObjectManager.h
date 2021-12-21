//
// Created by bonychops on 10/12/21.
//

#ifndef PROG_GAME_OBJECTMANAGER_H
#define PROG_GAME_OBJECTMANAGER_H

#include "Collision.h"
#include "Object.h"

#include <list>
#include <array>
#include <algorithm>
#include <iostream>
#include "Point.h"
#include <functional>
#include "objects/Block.h"
#include <variant>

using namespace std;
typedef Point P;

typedef variant<Block, Segment, Cable> AllObject;

//template<typename T, int S>
template<int S>
class ObjectManager {
public:
    ObjectManager() {
        cout << "INIT" << endl;
    }

    Collision *CheckCollision(Collision c) {
        array<P, COLLISION_POINTS_ACCURATE> pArray = c.genP<COLLISION_POINTS_ACCURATE>();
        int size = pArray.size();
        for (int i = 0; i < size; ++i) {
            Collision *result = CheckCollision(pArray.at(i));
            if (result->getType() != Collision::INVALID_COLLISION) {
                return result;
            }
        }
        return new Collision(Collision::INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
    }

    bool CheckCollisionWithBool(Collision c) {
        array<P, COLLISION_POINTS_ACCURATE> pArray = c.genP<COLLISION_POINTS_ACCURATE>();
        int size = pArray.size();
        for (int i = 0; i < size; ++i) {
            bool result = CheckCollisionWithBool(pArray.at(i));
            if (result) {
                return true;
            }
        }
        return false;
    }

    Collision *CheckCollision(P p) {
        //auto ite = find_if(begin(objects), end(objects), [p](auto o) { return o.collision->CheckCollision(p); });
        //return ite != end(objects);
        for (int i = 0; i < objIndex; ++i) {
            //for (Collision* collision: objects.at(i).collisions.getCollisions()) {
            Collision *c = std::visit([p](auto object) {
                GameArray<Collision, COLLISIONS_PER_OBJECT> *collisions = object.collisions.getCollisions();

                for (auto i = collisions->begin(); i != collisions->end(); ++i) {
                    Collision *collision = &*i;
                    //Collision *collision = objects.at(i).collision;
                    if (collision->CheckCollision(p)) {
                        return collision;
                    }
                }

               return new Collision(Collision::INVALID_COLLISION, (P){0, 0}, (P){0, 0});
            }, objects[i]);
            if(c->getType() != Collision::INVALID_COLLISION){
                return c;
            }
        }


        return new Collision(Collision::INVALID_COLLISION, (P) {0, 0}, (P) {0, 0});
    }

    bool CheckCollisionWithBool(P p) {
        Collision *result = CheckCollision(p);
        return result->getType() != Collision::INVALID_COLLISION;
    }

    void addObject(AllObject object) {
        if (objIndex >= S) {
            cerr << "[!]MAXIMUM SIZE OF " << typeid(Object).name() << "(" << S << ")" << " REACHED!!";
            return;
        }
        objects[objIndex] = object;
        objIndex += 1;
    }

    void drawAll(function<P(P)> fp, float scale) {
        for (int i = 0; i < objIndex; ++i) {
            std::visit([fp, scale](auto object) { object.draw(fp, scale); }, objects[i]);
            //object.draw(fp, scale);
        }
        //for_each(begin(objects), end(objects), [fp, scale](T o) { o.draw(fp, scale); });
    }

    template<class T>
    T at(int index) {
        if (auto p = std::get_if<T>(&objects[index])) {  // ポインタで渡す
            return *p;
        }
        return nullptr;
        //return objects.at(index);
    }

    template<class T>
    T *ats(int index) {
        if (auto p = std::get_if<T>(&objects[index])) {  // ポインタで渡す
            return p;
        }
        return nullptr;
    }


private:
    //array<Object, S> objects;
    array<AllObject, S> objects;
    // Object objects[10000];
    int objIndex = 0;
};

#endif //PROG_GAME_OBJECTMANAGER_H
