//
// Created by bonychops on 9/12/21.
//

#ifndef PROG_GAME_ANIMATOR_H
#define PROG_GAME_ANIMATOR_H

#include "TimeManager.h"


#define A_LINER 0
#define A_BEGIN_V0 1
#define A_END_V0 2
#define A_BOUND_V0 3


using namespace std;

class Animator {
public:
    int mode = 0;
    bool played = false;

    Animator();

    Animator(double init, double end, int frame, bool timeMode = false);


    ~Animator();

    double play();

    void reset();

    double liner(double t);

    double beginV0(double t);

    double endV0(double t);

    double CubicBoundaryV0(double t);

private:
    double m_init;
    double m_end;
    double m_state = 0.0;
    int m_maxFrame = 0;
    int frame = 0;
    bool timeMode;
    TimeManager tm;
};


#endif //PROG_GAME_ANIMATOR_H
