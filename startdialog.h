#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    QString getFIO();
    QString getNumber();
private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_H
