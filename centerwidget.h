#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QString>
#include <QSpacerItem>

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    CenterWidget(QWidget *parent = 0);
    void setMessage(QString msg);
private:
    QSpacerItem *Spacer;
    QLabel *Docking;
    QLabel *BodyPower;
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
};

#endif // CENTERWIDGET_H
