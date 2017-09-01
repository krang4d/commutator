#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

class AbortScenario {};

class IComposite
{

public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual void action() = 0;
    virtual void add(const SPtr&);
    virtual void remove(const SPtr&);
    virtual bool nextAction();

private:
    bool _next;
};

class Scenario: public IComposite{

public:
    Scenario();
    void add(const SPtr& sptr);
    void remove(const SPtr& sptr);
    void replace(const SPtr& oldValue, const SPtr& newValue);

    virtual void action();

private:
    std::list<SPtr> children_;
};

#endif // COMPOSITE_H
