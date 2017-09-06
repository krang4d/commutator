#ifndef MSWITCH_H
#define MSWITCH_H

#include "composite.h"
#include "logger.h"
#include "observer.h"

class mswitch : public IComposite, public Observer
{
public:
    enum channel { Y0, Y1, Y2 };

    mswitch(Logger *log, channel ch, Subject *con);
    void switchChannel(channel ch);
    mswitch::channel getChannel() const;
    void setDefault();

    virtual void action() override;
    virtual void update() override;

protected:
    const channel default_channel = Y0;
    channel current_channel;
    Logger *_plog;
};

#endif // MSWITCH_H
