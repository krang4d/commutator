#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QString>

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    CenterWidget(QWidget *parent = 0);
    void setMessage(QString msg);
private:
    QLabel *Connection;
    QLabel *BodePower;
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
};

#endif // CENTERWIDGET_H
