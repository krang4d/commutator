#include "composite.h"

class notify {};

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

Scenario::Scenario(Subject *sub, Logger *log, Mediator *m) : Observer(sub), log_(log), Colleague(m)
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
        setmsg("<div>" + sptr->action() + " " + log_->GetTime() + "</div>");
        log_->log(msg);
        Send(msg);
    }
    return msg;
}

void Scenario::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}

void Scenario::Send(string message)
{
    mediator_->Send(message, this);
}

void Scenario::Notify(string message)
{
    //throw notify;
}

string Scenario::getmsg()
{
    return msg;
}

void Scenario::setmsg(string m)
{
    msg = m;
}


void ConcreteMediator::SetScenario(Scenario *c)
{
           m_Colleague1=c;
}

void ConcreteMediator::SetMainWindow(mainWindow *c)
{
           m_Colleague2=c;
}

void ConcreteMediator::Send(string message, Colleague *colleague) const
{
    if (colleague==m_Colleague1)
    {
            m_Colleague2->Notify(message);
    }
    else if (colleague==m_Colleague2)
    {
            m_Colleague1->Notify(message);
}
