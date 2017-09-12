#ifndef TOOLS_H
#define TOOLS_H

#include <QDialog>

class Subject;

namespace Ui {
class tools;
}

class tools : public QDialog
{
    Q_OBJECT

public:
    explicit tools(Subject *con, QDialog *parent = 0);
    ~tools();

private:
    Ui::tools *ui;
    Subject *control_value;
public slots:
    void SetDock(bool);
    void SetBodyPower(bool);
};

#endif // TOOLS_H
