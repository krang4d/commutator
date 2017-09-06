#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include "logger.h"
#include "composite.h"
#include "observer.h"

class powermanager : public IComposite, public Observer
{
public:
    powermanager(Logger *log, double current_voltage, Subject *con);
    void setVoltage(double v);

    virtual void action() override;
    virtual void update() override;

protected:
    Logger *_plog;
    double _current_voltage;

};

#endif // POWERMANAGER_H
