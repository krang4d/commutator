#include "composite.h"

IComposite::IComposite()
{

}

void IComposite::add(const SPtr&) {
    throw std::runtime_error("IText: Can't add to a leaf");
}

void IComposite::remove(const SPtr&){
    throw std::runtime_error("IText: Can't remove from a leaf");
}

Scenario::Scenario(Subject *sub) : Observer(sub)
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
    std::string msg;
    for(SPtr& sptr : children_){
        if (!getNext()) throw AbortScenario();
        msg += sptr->action();
    }
    return msg;
}

void Scenario::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
