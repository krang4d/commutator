#include "tools.h"
#include "observer.h"
#include "ui_tools.h"

tools::tools(Subject *con, QDialog *parent) : control_value(con),
    QDialog(parent),
    ui(new Ui::tools)
{
    ui->setupUi(this);
    connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->dockBox, SIGNAL(toggled(bool)), this, SLOT(SetDock(bool)));
    connect(ui->bodyPowerkBox, SIGNAL(toggled(bool)), this, SLOT(SetBodyPower(bool)));

}

tools::~tools()
{
    delete ui;
}

void tools::SetDock(bool d)
{
    control_value->setDock(d);
}

void tools::SetBodyPower(bool b)
{
    control_value->setBodyPower(b);
}
