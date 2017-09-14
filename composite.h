#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <string>

#include <observer.h>
#include <logger.h>

class AbortScenario {};

class IComposite
{
public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual ~IComposite() {}
    virtual void add(const SPtr&);
    virtual void remove(const SPtr&);
    virtual std::string action() = 0;
};

class Scenario: public IComposite, Observer
{
public:
    Scenario(Subject *sub, Logger *log);
    virtual ~Scenario() {}
    bool getNext() const;
    void setNext(bool next);
    void add(const SPtr& sptr);
    void remove(const SPtr& sptr);
    void replace(const SPtr& oldValue, const SPtr& newValue);
    std::string action() override;
    void update() override;

private:
    std::list<SPtr> children_;
    bool next_;
    Logger *log_;
};

#endif // COMPOSITE_H
