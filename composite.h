#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <string>

class AbortScenario {};

class IComposite
{
public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual ~IComposite() {}
    virtual void add(const SPtr&);
    virtual void remove(const SPtr&);
    bool getNext() const;
    void setNext(bool next);
    virtual std::string action() = 0;
protected:
    bool next_;
};

class Scenario: public IComposite
{
public:
    virtual ~Scenario() {}
    void add(const SPtr& sptr);
    void remove(const SPtr& sptr);
    void replace(const SPtr& oldValue, const SPtr& newValue);
    std::string action() override;
private:
    std::list<SPtr> children_;
};

#endif // COMPOSITE_H
