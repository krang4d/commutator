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
#include <mainwindow.h>

class AbortScenario {};

class Mediator;
class Colleague;
class ConcreteMediator;
class mainWindow;

class Mediator
{
public:
        virtual void Send(std::string const& message, Colleague *colleague) const = 0;
};

class Colleague
{
protected:
        Mediator* mediator_;

public:
        explicit Colleague(Mediator *mediator):mediator_(mediator)
        {
        }
};

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

class Scenario: public IComposite, Observer, public Colleague
{
public:
    Scenario(Subject *sub, Logger *log, Mediator *m);
    virtual ~Scenario() {}
    bool getNext() const;
    void setNext(bool next);
    void add(const SPtr& sptr) override;
    void remove(const SPtr& sptr) override;
    void replace(const SPtr& oldValue, const SPtr& newValue);
    std::string action() override;
    void update() override;

    void Send(std::string message);
    void Notify(std::string message);

    std::string msg;
private:
    std::string getmsg();
    void setmsg(std::string m);

protected:
    std::list<SPtr> children_;
    bool next_;
    Logger *log_;
};


class ConcreteMediator: public Mediator
{
protected:
        Scenario *m_Colleague1;
        mainWindow *m_Colleague2;
public:
        void SetScenario(Scenario *c);

        void SetMainWindow(mainWindow *c);

        virtual void Send(std::string message, Colleague *colleague) const;
};

#endif // COMPOSITE_H
