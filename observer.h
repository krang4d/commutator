#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
//#include "logger.h"

using namespace std;

class Observer;

class Subject
{
public:
    Subject();
    void attach(Observer *obs);
    void setBodyPower(bool);
    void setDock(bool);
    bool getBodyPower();
    bool getDock();
    void notify();

protected:
    vector<Observer *> views;
    bool BodyPower;
    bool Dock;
};

class Observer
{
public:
    Observer(Subject *con);
    virtual void update() = 0;
protected:
    Subject *control;
    Subject *getSubject();
};

#endif // OBSERVER_H
