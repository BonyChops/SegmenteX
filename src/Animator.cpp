//
// Created by bonychops on 12/12/21.
//

#include "Animator.h"
#include <iostream>

Animator::Animator() {
    Animator(0.0, 0.0, 0);
}

Animator::Animator(double init, double end, int frame, bool timeMode) {
    m_init = init;
    m_state = init;
    m_end = end;
    m_maxFrame = frame;
    this->timeMode = timeMode;
    this->tm = TimeManager();
}

/*Animator::Animator(double init, double end, int frame) {
    Animator(init, end, frame, false);
}*/

Animator::~Animator() {

}

double Animator::play() {
    if (frame > m_maxFrame) {
        played = true;
        return m_end;
    }
    if(frame == 0){
        this->tm = TimeManager();
        frame += 1;
    }
    double t = ((double) frame / (double) m_maxFrame);
    frame += (this->timeMode ? tm.deltaTime() : 1);
    switch (mode) {
        case A_LINER:
            return liner(t);
        case A_BEGIN_V0:
            return beginV0(t);
        case A_END_V0:
            return endV0(t);
        case A_BOUND_V0:
            return CubicBoundaryV0(t);
    }
    return 0.0;
}

void Animator::reset() {
    frame = 0;
}

double Animator::liner(double t) {
    return ((m_end - m_init) * t) + m_init;
}

double Animator::beginV0(double t) {
    double a = m_end - m_init;
    return (a * t * t) + m_init;
}

double Animator::endV0(double t) {
    double a = m_init - m_end;
    double b = -2.0 * a;
    double ret = a;
    ret *= t;
    ret += b;
    ret *= t;
    ret += m_init;
    return ret;
}

double Animator::CubicBoundaryV0(double t) {
    double a = 2.0 * (m_init - m_end);
    double b = 3.0 * (m_end - m_init);
    double ret = a;
    ret *= t;
    ret += b;
    ret *= t;
    ret *= t;
    ret += m_init;
    return ret;
}


