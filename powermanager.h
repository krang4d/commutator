#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include "logger.h"
#include "composite.h"
class powermanager : public IComposite
{
public:

    powermanager(Logger *log, double current_voltage);
    void setVoltage(double v);

    virtual void action() override;

protected:
    double _current_voltage;
    Logger *_plog;

};

#endif // POWERMANAGER_H
