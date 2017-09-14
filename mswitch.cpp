#include "mswitch.h"

#include <iostream>

using namespace std;

mswitch::mswitch(channel ch, Subject *con)
    : current_channel(ch), Observer(con)
{

}

std::string mswitch::switchChannel(channel ch)
{
    current_channel = ch;
    std::string str = "Подключение канала - Y" + to_string(ch);
    return str;
}

mswitch::channel mswitch::getChannel() const
{
    return current_channel;
}

void mswitch::setDefault()
{
    current_channel = default_channel;
}

string mswitch::action()
{
    return switchChannel(current_channel);
}

void mswitch::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
