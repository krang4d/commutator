#include "composite.h"
#include "QThread"

IComposite::IComposite()
{

}

IComposite::~IComposite() {

}

void IComposite::add(const SPtr&) {
    throw std::runtime_error("IText: Can't add to a leaf");
}

void IComposite::remove(const SPtr&){
    throw std::runtime_error("IText: Can't remove from a leaf");
}

//string IComposite::action()
//{
//    throw std::runtime_error("IText: Can't action from a leaf");
//}

Scenario::Scenario()
{

}

void Scenario::setNext(bool next)
{
    next_ = next;
}

bool Scenario::getNext() const
{
    return next_;
}

void Scenario::add(const SPtr& sptr){
    children_.push_back(sptr);
}

void Scenario::remove(const SPtr& sptr){
    children_.remove(sptr);
}

void Scenario::replace(const SPtr& oldValue, const SPtr& newValue){
    std::replace(children_.begin(), children_.end(), oldValue, newValue);
}

std::string Scenario::action(){
    for(SPtr& sptr : children_){
        if (!getNext()) throw AbortScenario();
        setmsg(sptr->action());
        emit newmessage(QString(getmsg().c_str()));
        QThread::msleep(1000);
    }
    return msg;
}

string Scenario::getmsg()
{
    return msg;
}

void Scenario::setmsg(string m)
{
    msg = m;
}

