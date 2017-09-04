#include "mainwindow.h"

#include "centerwidget.h"
#include "mswitch.h"
#include "measurement.h"
#include "powermanager.h"
#include "composite.h"
#include "logger.h"

mainWindow::mainWindow()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    InitWindow();
    CreateScenario();

    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(cw, SIGNAL(Exit()), this, SLOT(close()));
    connect(cw, SIGNAL(Start()), this, SLOT(run()));
    connect(cw, SIGNAL(View()), this, SLOT(view()));
}

void mainWindow::InitWindow()
{
    cw = new CenterWidget(this);

    aboutAction = new QAction(tr("&O программе"), this);
    aboutAction->setStatusTip(tr("Сведения о программе"));
    exitAction = new QAction(tr("В&ыход"));
    exitAction->setStatusTip(tr("Выход из программы"));
    exitAction->setShortcut(tr("Ctrl+Q"));

    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(aboutAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

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
    string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Начало проверок. Дата ") + log->GetDataTime() + string("</div>");
    log->log(msg);

    setCentralWidget(cw);
}

void mainWindow::CreateScenario()
{
    sc = new Scenario();

    IComposite::SPtr PowerON(new powermanager(log, 27));
    IComposite::SPtr PowerOFF(new powermanager(log, 0));

    IComposite::SPtr Volt(new measurement(log, measurement::VOLT));
    IComposite::SPtr Resist(new measurement(log, measurement::RESIST));

    IComposite::SPtr Y0(new mswitch(log,mswitch::Y0));
    IComposite::SPtr Y1(new mswitch(log,mswitch::Y1));

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

void mainWindow::setNextLine(string msg){
    cw->setMessage(QString(msg.c_str()));
}

void mainWindow::resizeEvent(QResizeEvent *event) {
    QSize sz = event->size();
    sb2->setText(QString( "(%1, %2)" ).arg( sz.width() ).arg( sz.height() ) );
}

void mainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    sb3->setText(QString( "%1, %2" ).arg( pos.x() ).arg( pos.y() ) );
}

void mainWindow::about() {
    QMessageBox::about(
    this, tr("О программе"),
    tr("<p><b>Назначение:</b> Программа предназначена для проверки модуля сопряжения МС-54.011 КИНД.468354.011 из состава блока БУСС-32.054"
       "КИНД.468332.054 аппаратуры второго рабочего места КПА-166-09</p>"
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

bool mainWindow::askClose() {
    int r = QMessageBox::question(this, tr("Подтвердите"),
    tr("Выйти из программы?"),
    QMessageBox::Yes | QMessageBox::No);
    //QMessageBox::Yes,
    //QMessageBox::Cancel | QMessageBox::Escape);
    return (r == QMessageBox::Yes);
}

void mainWindow::closeEvent(QCloseEvent *event) {
    if (askClose()) {
    event->accept();
    }
    else {
    event->ignore();
    }
}

