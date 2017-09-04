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
    Logger *_plog;
    double _current_voltage;

};

#endif // POWERMANAGER_H
