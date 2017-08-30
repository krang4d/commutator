#include <iostream>
#include <QApplication>

#include "mainwindow.h"


using namespace std;

int main(int argc, char *argv[])
{
    //setlocale(LC_CTYPE, "Russian");
    QApplication app(argc, argv);

    mainWindow *mw = new mainWindow();
    mw->setWindowTitle(QWidget::tr("Прототип коммутатора"));
    mw->resize(500, 500);
    mw->show();
    return app.exec();
}
