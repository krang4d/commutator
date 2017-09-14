#ifndef MSWITCH_H
#define MSWITCH_H

#include "composite.h"
#include "observer.h"

class mswitch : public IComposite, public Observer
{
public:
    enum channel { Y0, Y1, Y2 };

    mswitch(channel ch, Subject *con);
    std::string switchChannel(channel ch);
    mswitch::channel getChannel() const;
    void setDefault();

    virtual std::string action() override;
    virtual void update() override;

protected:
    const channel default_channel = Y0;
    channel current_channel;
};

#endif // MSWITCH_H
