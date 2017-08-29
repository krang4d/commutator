#include "mswitch.h"

#include <iostream>

using namespace std;

mswitch::mswitch(Logger *log, channel ch)
    : current_channel(ch), _plog(log)
{

}

void mswitch::switchChannel(channel ch)
{
    current_channel = ch;
    string str = "<div>Подключение канала - Y" + to_string(ch) +"</div>";
    _plog->log(str);

}

mswitch::channel mswitch::getChannel() const
{
    return current_channel;
}

void mswitch::setDefault()
{
    current_channel = default_channel;
}

void mswitch::action()
{
    switchChannel(current_channel);
}
