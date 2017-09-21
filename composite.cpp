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

Scenario::Scenario(Subject *sub, Logger *log) : Observer(sub), log_(log)
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
        emit newmessage(QString(msg.c_str()));
        notify();
        QThread::msleep(1000);
    }
    return msg;
}

void Scenario::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}

void Scenario::attach(ObservWindow *obsw)
{
    views.push_back(obsw);
}

void Scenario::notify()
{
    for(unsigned int i=0; i < views.size(); i++)
        views[i]->updateWindow();
}

string Scenario::getmsg()
{
    return msg;
}

void Scenario::setmsg(string m)
{
    msg = m;
}

ObservWindow::ObservWindow(Scenario *sn) : sub(sn)
{
    sub->attach(this);
}

Scenario *ObservWindow::getScenario()
{
    return sub;
}
