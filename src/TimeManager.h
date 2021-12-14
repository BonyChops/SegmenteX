//
// Created by bonychops on 12/12/21.
//

#ifndef PROG_GAME_TIMEMANAGER_H
#define PROG_GAME_TIMEMANAGER_H


class TimeManager {
public:
    TimeManager();
    ~TimeManager();

    int deltaTime();

private:
    long bufTime;
};


#endif //PROG_GAME_TIMEMANAGER_H
