//
// Created by bonychops on 12/12/21.
//

#include "Player.h"
#include "ResourceManager.h"
#include "KeyboardManager.h"
#include "Drawer.h"

typedef ResourceManager RCM;
typedef KeyboardManager KBM;

Player::Player() {
    cerr << "INITIALIZED WITHOUT MAP!" << endl;
    valid = false;
}

Player::Player(Map map) {
    this->map = map;
    p = {0, 5};
    collision = new Collision(Collision::SQUARE, (P) {p.x, p.y + 1}, (P) {p.x + 1, p.y - 1});
    ph = new Physics(collision, p, &map);
    ph->y.a = -0.00005;
    ph->y.v = 0.030;
    ph->x.v = 0.0100;
}

Player::~Player() {
    delete collision;
    delete ph;
}

void Player::draw(function<P(P)> fp, float scale) {
    draw(fp, scale, false);
}

void Player::draw(function<P(P)> fp, float scale, bool skipResource) {
    if (!valid) {
        return;
    }
    bool keyResult = KBM::getKeyboard(' ', Keyboard::KEY);
    if (keyResult && ph->y.v == 0) {
        ph->y.v = 0.02;
    }
    float tmpx = 0;
    tmpx += KBM::getKeyboard('a', Keyboard::KEY) ? -0.0002 : 0;

    tmpx += KBM::getKeyboard('d', Keyboard::KEY) ? 0.0002 : 0;
    if (ph->x.v > 0.01) {
        ph->x.v = 0.01;
    }
    if (ph->x.v < -0.01) {
        ph->x.v = -0.01;
    }
    //)ph->x.v = tmpx;
    ph->x.a = tmpx;
    if (tmpx == 0 && ph->y.v == 0) {
        ph->x.v = 0;
    }
    P p = this->ph->calc();

    this->p = p;
    if (!skipResource) {
        drawResource(fp, scale);
    }
}

void Player::drawResource(function<P(P)> fp, float scale) {
    Image rc = RCM::GetImage("../images/objects/player.png");
    rc.putSprite(fp((P) {
            .x = p.x,
            .y = p.y
    }), scale / BLOCK_RC_SIZE);
    if (DEBUG) {
        array<P, COLLISION_POINTS_ACCURATE> points = collision->genP<COLLISION_POINTS_ACCURATE>();
        for (int i = 0; i < COLLISION_POINTS_ACCURATE; ++i) {
            P p = points[i];
            glColor3ub(255, 0, 0);
            Drawer::Square(fp((P) {
                    (float) (p.x - 0.1) * BLOCK_RC_SIZE,
                    (float) (p.y - 1 - 0.1) * BLOCK_RC_SIZE
            }), fp((P) {
                    (float) (p.x + 0.1) * BLOCK_RC_SIZE,
                    (float) (p.y - 1 + 0.1) * BLOCK_RC_SIZE
            }));
        }
    }


}