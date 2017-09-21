#ifndef SCENARIOTHREAD_H
#define SCENARIOTHREAD_H

#include <QThread>
#include "logger.h"
#include "observer.h"
#include "composite.h"
#include "logger.h"
#include "mswitch.h"
#include "measurement.h"
#include "powermanager.h"

class ScenarioThread : public QThread
{
    Q_OBJECT
    Subject *control_value;
    Logger *log;
    Scenario *sc;
public:
    ScenarioThread();
    ~ScenarioThread();
    void run() override;
signals:
    void threadmessage(QString);
};

#endif // SCENARIOTHREAD_H
