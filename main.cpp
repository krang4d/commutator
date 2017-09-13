#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "startdialog.h"
#include "logger.h"

using namespace std;

int main(int argc, char *argv[])
{
    //setlocale(LC_CTYPE, "Russian");
    QApplication app(argc, argv);

    mainWindow *mw = new mainWindow();
    mw->setWindowTitle(QWidget::tr("Прототип коммутатора"));
    mw->resize(1000, 500);
    mw->moveToCenter();
    mw->show();

    StartDialog *st = new StartDialog(mw);
    QObject::connect(st, SIGNAL(rejected()), mw, SLOT(close()));
    if(st->exec() == QDialog::Accepted) {
        mw->getLogger()->log("<div>Ф.И.О. оператора: "+st->getFIO().toStdString()+"</div>");
        mw->getLogger()->log("<div>Номер прибора: "+st->getNumber().toStdString()+"</div>");
    }
    return app.exec();

    delete st;
    delete mw;
}
