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
#include <QWidget>
#include <QString>

class AbortScenario {};
class ObservWindow;

class IComposite : public QWidget
{
public:
    typedef std::shared_ptr<IComposite> SPtr;

    IComposite();
    virtual ~IComposite();
    virtual void add(const SPtr&);
    virtual void remove(const SPtr&);
    virtual std::string action() = 0;
};

class Scenario: public IComposite
{
    Q_OBJECT
public:
    Scenario();
    virtual ~Scenario() {}
    bool getNext() const;
    void setNext(bool next);
    void add(const SPtr& sptr) override;
    void remove(const SPtr& sptr) override;
    void replace(const SPtr& oldValue, const SPtr& newValue);
    std::string action() override;

    std::string getmsg();
    void setmsg(std::string m);

signals:
    void newmessage(QString);

private:
    std::list<SPtr> children_;
    bool next_;
    std::string msg;
};

#endif // COMPOSITE_H
