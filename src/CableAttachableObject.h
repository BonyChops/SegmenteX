//
// Created by bonychops on 17/12/21.
//

#ifndef PROG_GAME_CABLEATTACHABLEOBJECT_H
#define PROG_GAME_CABLEATTACHABLEOBJECT_H

#include "Point.h"
#include "Object.h"
typedef Point P;

class CableAttachableObject : public Object{
public:
    CableAttachableObject() : Object(){
        type = CABLE_ATTACHABLE;
    }
    ~CableAttachableObject(){

    }
    virtual void changePower(bool power){
        changePower(power, 0);
    }

    void changePower(bool power, int n){
        cout << "T ADDRESS: " << this << endl;
        this->powers[n] = power;
        if(power){
            cout << this << endl;
        }
    };
    ;
    P getCableSocket(){
        return cableSocket;
    }

    bool isCableAttachable() override{
        return true;
    }

    P cableSocket;
protected:
    bool powers[POWERS_NUM] = {0};
};



#endif //PROG_GAME_CABLEATTACHABLEOBJECT_H
