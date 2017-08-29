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
    void setMessage(QString *msg);

private:
    QLabel *MessageLabel;
    QTextEdit *MessageTextEdit;
    QPushButton *StartButton;
    QPushButton *AbortButton;
    QPushButton *ExitButton;

    void setupLayout(void);

signals:

public slots:
};

#endif // CENTERWIDGET_H
