//
// Created by bonychops on 15/01/22.
//

#ifndef PROG_GAME_PARTICLE_H
#define PROG_GAME_PARTICLE_H

#include <functional>
#include <iostream>

#include "Physics.h"
#include "Map.h"
#include "Collision.h"

class Particle {
public:
    bool invalid = false;

    int r = 0;
    Particle() {
        invalid = true;
    }

    ~Particle() {}

    Particle(Map *map, P p) : Particle(map, p, rand() % 256, rand() % 256, rand() % 256){}

    Particle(Map *map, P p, int r, int g, int b) : collision(Collision::SQUARE,
                                                             (P) {p.x - (float) 0.1, p.y + 1 - (float) 0.1},
                                                             (P) {p.x + (float) 0.1, p.y  + 1+ (float) 0.1}),
                                                             ph(&collision, p, map){
        ph = Physics(&collision, p, map);
        std::cout << "MAP: "<<(map != nullptr) << std::endl;
        this->map = map;
        ph.x.x = p.x;
        ph.y.x = p.y;
        ph.y.a = GRAVITY / 10;
        ph.x.v = (std::rand()/((RAND_MAX + 1u)/10) - 5.0) / 100.0;
        ph.y.v = (std::rand()/((RAND_MAX + 1u)/10)) / 100.0;
        cout << (std::rand()/((RAND_MAX + 1u)/10)) / 100.0 << endl;
        this->r = r;
        this->g = g;
        this->b = b;
        cout << "Welcome" << endl;
    }

    void draw(function<P(P)> fp, float scale, Map *map) {
        //cout << &this->map << endl;
        //cout << &map << endl;
        if (invalid || (this->map == nullptr)) {
            return;
        }
        //cout << "aa" << endl;
        ph.map = map;
        ph.calc(false);
        glColor3ub(r, g, b);
        P p = {
                ph.x.x,
                ph.y.x
        };

        Drawer::Square(fp((P) {
                (float) (p.x - 0.1),
                (float) (p.y - 0.1)
        }), fp((P) {
                (float) (p.x + 0.1) ,
                (float) (p.y + 0.1)
        }));
        //Drawer::Square(fp((P){0, 0}), fp((P){3, 3}));
    }

    Physics ph;
private:
    Map *map;
    int g = 0;
    int b = 0;
    Collision collision;
};

#endif //PROG_GAME_PARTICLE_H
