#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

QString StartDialog::getFIO()
{
    return ui->FIO->text();
}

QString StartDialog::getNumber()
{
    return ui->Number->text();
}
