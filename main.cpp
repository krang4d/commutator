#include <iostream>
#include <QApplication>

#include "mainwindow.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainWindow *mw = new mainWindow();
    //QString *msg = new QString(QWidget::tr("<p>Начало проверки модуля МС-54.011</p>"));
    mw->setWindowTitle(QMainWindow::tr("Прототип коммутатора"));
    mw->resize(500, 500);
    mw->show();

    //msg->append(QMainWindow::tr("<p>setNextLine()</p>"));

    return app.exec();
}
