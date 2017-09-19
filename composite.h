#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <observer.h>
#include <logger.h>

class AbortScenario {};
class ObservWindow;

class IComposite
{
public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual ~IComposite();
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
    void add(const SPtr& sptr) override;
    void remove(const SPtr& sptr) override;
    void replace(const SPtr& oldValue, const SPtr& newValue);
    std::string action() override;
    void update() override;

    void attach(ObservWindow *obsw);
    void notify();

    std::string msg;
private:
    std::list<SPtr> children_;
    std::vector<ObservWindow *> views;
    bool next_;
    Logger *log_;
};

class ObservWindow
{
public:
    ObservWindow(Scenario *sn);
    virtual void updateWindow() = 0;
protected:
    Scenario *sub;
    Scenario *getScenario();
};

#endif // COMPOSITE_H
