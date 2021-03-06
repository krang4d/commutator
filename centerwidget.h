﻿#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QString>
#include <QSpacerItem>
#include <string>

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    CenterWidget(QWidget *parent = 0);
    virtual ~CenterWidget();
    void setMessage(std::string msg);
//private:
    QVBoxLayout *masterLayout;
    QVBoxLayout *ledSlaveVLayout;
    QHBoxLayout *ledSlaveHLayout;
    QHBoxLayout *buttonSlaveLayout;

    QSpacerItem *Spacer;
    QLabel *DockingLed;
    QLabel *BodyPowerLed;
    QLabel *MessageLabel;
    QTextEdit *MessageTextEdit;
    QPushButton *StartButton;
    QPushButton *ViewButton;
    QPushButton *ExitButton;

    void setupLayout(void);

signals:
    void Exit();
    void View();
    void Start();

public slots:
    void DockingChange(bool);
    void BodyPowerChange(bool);

protected:
    std::vector<std::string> messages;
};

#endif // CENTERWIDGET_H
