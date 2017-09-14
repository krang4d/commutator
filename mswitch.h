#ifndef MSWITCH_H
#define MSWITCH_H

#include "composite.h"

class mswitch : public IComposite
{
public:
    enum channel { Y0, Y1, Y2 };

    mswitch(channel ch);
    std::string switchChannel(channel ch);
    mswitch::channel getChannel() const;
    void setDefault();

    virtual std::string action() override;

protected:
    const channel default_channel = Y0;
    channel current_channel;
};

#endif // MSWITCH_H
