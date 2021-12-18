//
// Created by bonychops on 16/12/21.
//

#ifndef PROG_GAME_COLLISIONMANAGER_H
#define PROG_GAME_COLLISIONMANAGER_H

#include "GameArray.h"
#include "Collision.h"



template<int T>
class CollisionManager {
public:
    CollisionManager(){
        collisions = GameArray<Collision, T>();
    }
    CollisionManager(Collision c){
        CollisionManager<T>();
        collisions.push(c);
    }

    bool CheckCollision(P p){
        for (auto c: collisions) {
            if(c.CheckCollision(p)){
                return true;
            }
        }
        return false;
    }

    void addCollision(Collision c){
        collisions.push(c);
    }

    GameArray<Collision, T> getCollisions(){
        return collisions;
    }


private:
    GameArray<Collision, T> collisions;
    int cIndex = 0;
};


#endif //PROG_GAME_COLLISIONMANAGER_H
