#include "mainwindow.h"

#include "centerwidget.h"
#include "mswitch.h"
#include "measurement.h"
#include "powermanager.h"
#include "composite.h"
#include "logger.h"
#include "observer.h"

mainWindow::mainWindow()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    InitWindow();
    CreateScenario();

    connect(startAction, SIGNAL(triggered(bool)), this, SLOT(run()));
    connect(viewAction, SIGNAL(triggered(bool)), this, SLOT(view()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(cw, SIGNAL(Exit()), this, SLOT(close()));
    connect(cw, SIGNAL(Start()), this, SLOT(run()));
    connect(cw, SIGNAL(View()), this, SLOT(view()));
}

void mainWindow::InitWindow()
{
    cw = new CenterWidget(this);

    startAction = new QAction(tr("Начать проверку"));
    startAction->setShortcut(tr("Ctrl+R"));
    viewAction = new QAction(tr("Просмотреть файл"));
    aboutAction = new QAction(tr("O программе"), this);
    aboutAction->setStatusTip(tr("Сведения о программе"));
    exitAction = new QAction(tr("Выход"));
    exitAction->setStatusTip(tr("Выход из программы"));
    exitAction->setShortcut(tr("Ctrl+Q"));

    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(startAction);
    fileMenu->addAction(viewAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    HelpMenu = menuBar()->addMenu(tr("&Спаравка"));
    HelpMenu->addAction(aboutAction);

    sb1 = new QLabel(statusBar());
    sb2 = new QLabel(statusBar());
    sb3 = new QLabel(statusBar());

    statusBar()->setSizeGripEnabled(false);
    statusBar()->addWidget(sb1, 2);
    statusBar()->addWidget(sb2, 1);
    statusBar()->addWidget(sb3, 1);

    sb1->setText(tr("Привет!"));
    setMouseTracking(true);

    log = new AllLogger(this);
    //log->log("<meta http-equiv=\"refresh\" content=\"10\">");
    //QString("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>%1 %2</div>").arg("Начало проверок").arg(log->GetDataTime());
    string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Начало проверок. ") + log->GetDateTime() + string("</div>");
    log->log(msg);

    setCentralWidget(cw);
}

void mainWindow::CreateScenario()
{
    control_value = new Subject(log);

    IComposite::SPtr PowerON(new powermanager(log, 27, control_value));
    IComposite::SPtr PowerOFF(new powermanager(log, 0, control_value));

    IComposite::SPtr Volt(new measurement(log, measurement::VOLT, control_value));
    IComposite::SPtr Resist(new measurement(log, measurement::RESIST, control_value));

    IComposite::SPtr Y0(new mswitch(log,mswitch::Y0, control_value));
    IComposite::SPtr Y1(new mswitch(log,mswitch::Y1, control_value));

    control_value->setBodyPower(true);
    control_value->setDock(false);

    sc = new Scenario();
    sc->add(PowerON);
    sc->add(Y0);
    sc->add(Volt);
    sc->add(Resist);
    sc->add(Y1);
    sc->add(Volt);
    sc->add(Resist);
    sc->add(Y0);
    sc->add(PowerOFF);
}

mainWindow::~mainWindow()
{
    delete log;
    delete sc;
}

void mainWindow::setNextLine(string msg)
{
    cw->setMessage(QString(msg.c_str()));
}

void mainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sz = event->size();
    sb2->setText(QString( "(%1, %2)" ).arg( sz.width() ).arg( sz.height() ) );
}

void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    sb3->setText(QString( "%1, %2" ).arg( pos.x() ).arg( pos.y() ) );
}

void mainWindow::about()
{
    QMessageBox::about(
    this, tr("О программе"),
    tr("<p><b>Назначение:</b> Программа предназначена для проверки модуля сопряжения МС-XX.XXX КИНД.XXXXXX.XXX из состава аппаратуры входного контроля КПА-XXX.XX</p>"
       "<p><b>Автор:</b> Головкин П.Г.</p>"));
}

void mainWindow::run()
{
    sc->action();
}

void mainWindow::view()
{
    QProcess vim;
    vim.startDetached("google-chrome Commutator.html");
    vim.waitForFinished();
}

bool mainWindow::askClose()
{
    int r = QMessageBox::question(this, tr("Подтвердите"),
    tr("Выйти из программы?"),
    QMessageBox::Yes | QMessageBox::No);
    //QMessageBox::Yes,
    //QMessageBox::Cancel | QMessageBox::Escape);
    return (r == QMessageBox::Yes);
}

void mainWindow::closeEvent(QCloseEvent *event)
{
    if (askClose()) { event->accept(); }
    else { event->ignore(); }
}

