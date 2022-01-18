//
// Created by bonychops on 12/12/21.
//

#include "Player.h"
#include "ResourceManager.h"
#include "KeyboardUtils.h"
#include "Drawer.h"


typedef ResourceManager RCM;
typedef KeyboardUtils KBM;

Player::Player() {
    cerr << "INITIALIZED WITHOUT MAP!" << endl;
    valid = false;
}

Player::Player(Map *map) : collision(Collision::SQUARE, (P) {p.x, p.y + 1}, (P) {p.x + 1, p.y - 1}),
                           ph(&collision, p, map) {
    //std::srand(std::time(nullptr));
    this->map = map;
    ph = Physics(&collision, p, map);
    ph.y.a = GRAVITY;
    updateParticles(p);

//    ph->y.v = 0.030;
//    ph->x.v = 0.0100;
}

void Player::updateParticles(P p) {
    for (int i = 0; i < PARTICLES; ++i) {
        cout << "Helol" << endl;
        //particles.at(i) = Particle(this->map, p);
    }
}

void Player::setP(P p, bool check) {
    this->p = check ? findNearestP(p) : p;
    ph = Physics(&collision, this->p, map);
    ph.y.a = GRAVITY;
    this->collision.p1 = {this->p.x, this->p.y + 1};
    this->collision.p2 = {this->p.x + 1, this->p.y - 1};
    updateParticles(p);
}

P Player::findNearestP(P p) {
    if (!map->CheckCollisionWithBool(generateCollision(p))) {
        return p;
    }
    for (float i = 0; i < SEARCH_AROUND_DISTANCE; i += 0.1) {
        for (int j = 0; j < SEARCH_AROUND_ACCURATE; ++j) {
            float angle = (2 * (float) M_PI * j / SEARCH_AROUND_ACCURATE);
            P tmpP = {
                    round(p.x) + (cos(angle) * i),
                    round(p.y) + (sin(angle) * i),
            };
            bool result = map->CheckCollisionWithBool(generateCollision(tmpP));
            if (!result) {
                return tmpP;
            }
        }
    }
    return p;
}

Collision Player::generateCollision(P p) {
    return Collision(Collision::SQUARE, (P) {p.x, p.y + 1}, (P) {p.x + 1, p.y - 1});
}

Player::~Player() {
}

void Player::draw(function<P(P)> fp, float scale) {
    draw(fp, scale, false);
}


void Player::draw(function<P(P)> fp, float scale, bool skipResource) {
    draw(fp, scale, skipResource, false);
}

void Player::draw(function<P(P)> fp, float scale, bool skipResource, bool editorView) {
    if (!editorView) {
        if (!valid) {
            return;
        }
        bool keyResult = KBM::getKeyboard(' ', Keyboard::KEY);
        if (keyResult && ph.y.v == 0) {
            ph.y.v = 0.02;
        }
        float tmpx = 0;
        bool shiftPressed = KBM::getKeyboard(SHIFT_KEY, Keyboard::SPECIAL);
        tmpx += KBM::getKeyboard('a', Keyboard::KEY) ? (shiftPressed ? -0.0002 : -0.0004) : 0;
        tmpx += KBM::getKeyboard('d', Keyboard::KEY) ? (shiftPressed ? 0.0002 : 0.0004) : 0;
        if (ph.x.v > 0.01) {
            ph.x.v = 0.01;
        }
        if (ph.x.v < -0.01) {
            ph.x.v = -0.01;
        }
        //)ph.x.v = tmpx;
        ph.x.a = tmpx;
        if (tmpx == 0 && ph.y.v == 0) {
            ph.x.v = 0;
        }
        if (KBM::getKeyboard('s', Keyboard::KEY)) {
            ph.x.v = 0;
            ph.y.v = -0.03;
        }

        if (ph.lastCollision.objectType == Collision::GOAL){
            ph.x.a = 0;
            ph.x.v = 0;
            ph.y.a = 0;
            ph.y.v = 0;
            clear = true;
        }

        P p = this->ph.calc(dead);

        if (ph.y.x < -2 || ph.lastCollision.objectType == Collision::SPIKE) {
            dead = true;
        }


        this->p = p;
    } else {
        float moveSpeed = KBM::getKeyboard(GLUT_ACTIVE_SHIFT, Keyboard::SPECIAL) ? 0.1 : 0.2;
        auto check = [&](char c) { return KBM::getKeyboard(c, Keyboard::KEY); };
        if (check('w')) {
            p.y += moveSpeed;
        }
        if (check('a')) {
            p.x -= moveSpeed;
        }
        if (check('s')) {
            p.y -= moveSpeed;
        }
        if (check('d')) {
            p.x += moveSpeed;
        }
    }
    if (!skipResource) {
        drawResource(fp, scale);
    }
    //cout << //particles.at(0).ph.x.x << endl;
    //cout << //particles.at(0).ph.y.x << endl;
    for (int i = 0; i < PARTICLES; ++i) {
        //cout << //particles[i].r << endl;
        //cout << //particles[i].ph.y.v << endl;
        //particles.at(i).draw(fp, scale * 100, map);
    }
}

void Player::drawResource(function<P(P)> fp, float scale) {
    Image rc = RCM::GetImage("../images/objects/player.png");
    rc.putSprite(fp((P) {
            .x = p.x,
            .y = p.y
    }), scale / BLOCK_RC_SIZE);
    if (DEBUG) {
        array<P, COLLISION_POINTS_ACCURATE> points = collision.genP<COLLISION_POINTS_ACCURATE>();
        for (int i = 0; i < COLLISION_POINTS_ACCURATE; ++i) {
            P p = points[i];
            glColor3ub(255, 0, 0);
            Drawer::Square(fp((P) {
                    (float) (p.x - 0.1),
                    (float) (p.y - 1 - 0.1)
            }), fp((P) {
                    (float) (p.x + 0.1),
                    (float) (p.y - 1 + 0.1)
            }));
        }
    }


}