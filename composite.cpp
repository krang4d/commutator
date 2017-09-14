#include "composite.h"

IComposite::IComposite() : next_(false)
{

}

void IComposite::add(const SPtr&) {
    throw std::runtime_error("IText: Can't add to a leaf");
}

void IComposite::remove(const SPtr&){
    throw std::runtime_error("IText: Can't remove from a leaf");
}

void IComposite::setNext(bool next)
{
    next_ = next;
}

bool IComposite::getNext() const
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
        if (!sptr->getNext()) throw AbortScenario();
        log.log(sptr->action());
    }
}
