#include <iostream>
#include <QApplication>

#include "mswitch.h"
#include "measurement.h"
#include "logger.h"
#include "powermanager.h"
#include "composite.h"
#include "mainwindow.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainWindow *mw = new mainWindow;
    //QString *msg = new QString(QWidget::tr("<p>Начало проверки модуля МС-54.011</p>"));


    mw->setWindowTitle(QMainWindow::tr("Прототип коммутатора"));
    mw->resize(500, 500);
    mw->show();

    //msg->append(QMainWindow::tr("<p>setNextLine()</p>"));

    Logger *log(new WindowLogger(mw));
    log->setMessage("<div style='color:#00ff00; margin: 5px 0px'>Начало проверк</div>");
    Scenario s1;

    IComposite::SPtr PowerON(new powermanager(log, 27));
    IComposite::SPtr PowerOFF(new powermanager(log, 0));

    IComposite::SPtr Volt(new measurement(log, measurement::VOLT));
    IComposite::SPtr Resist(new measurement(log, measurement::RESIST));

    IComposite::SPtr Y0(new mswitch(log,mswitch::Y0));
    IComposite::SPtr Y1(new mswitch(log,mswitch::Y1));

    s1.add(PowerON);
    s1.add(Y0);
    s1.add(Volt);
    s1.add(Resist);
    s1.add(Y1);
    s1.add(Volt);
    s1.add(Resist);
    s1.add(Y0);
    s1.add(PowerOFF);

    cout << "***Выполнение сценария s1***" << endl;
    s1.action();

    delete log;

    return app.exec();
}
