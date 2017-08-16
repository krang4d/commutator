#ifndef MSWITCH_H
#define MSWITCH_H

#include "composite.h"
#include "logger.h"

class mswitch : public IComposite
{
public:
    enum channel { Y0, Y1, Y2 };

    mswitch(Logger *log, channel ch);
    void switchChannel(channel ch);
    mswitch::channel getChannel() const;
    void setDefault();

    virtual void action() override;

protected:
    const channel default_channel = Y0;
    channel current_channel;
    Logger *_plog;
};

#endif // MSWITCH_H
