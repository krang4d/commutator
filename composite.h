#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <QtCore>

class AbortScenario {};

class IComposite : QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual ~IComposite() {}
    virtual void add(const SPtr&);
    virtual void remove(const SPtr&);
    bool getNext() const;
    void setNext(bool next);
    virtual void action() = 0;
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
    virtual void action() override;
public slots:
    void runScenario();
private:
    std::list<SPtr> children_;
};

#endif // COMPOSITE_H
