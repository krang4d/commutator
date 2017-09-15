#include "mainwindow.h"
#include "centerwidget.h"
#include "tools.h"
#include "startdialog.h"
#include "logger.h"


mainWindow::mainWindow(Subject *control) : Observer(control)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    InitWindow();

    connect(startAction, SIGNAL(triggered(bool)), this, SLOT(run()));
    connect(viewAction, SIGNAL(triggered(bool)), this, SLOT(view()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(cw, SIGNAL(Exit()), this, SLOT(close()));
    connect(cw, SIGNAL(Start()), this, SLOT(run()));
    connect(cw, SIGNAL(View()), this, SLOT(view()));
    connect(toolsAction, SIGNAL(triggered(bool)), this, SLOT(toolsWindow()));
}

void mainWindow::InitWindow()
{
    cw = new CenterWidget(this);
    startAction = new QAction(tr("Начать проверку"));
    startAction->setShortcut(tr("Ctrl+R"));
    viewAction = new QAction(tr("Просмотреть файл"));
    toolsAction = new QAction(tr("Дополнительные возможности..."));
    aboutAction = new QAction(tr("O программе"), this);
    aboutAction->setStatusTip(tr("Сведения о программе"));
    exitAction = new QAction(tr("Выход"));
    exitAction->setStatusTip(tr("Выход из программы"));
    exitAction->setShortcut(tr("Ctrl+Q"));

    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(startAction);
    fileMenu->addAction(toolsAction);
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

    setCentralWidget(cw);
}

mainWindow::~mainWindow()
{
}

void mainWindow::setNextLine(string msg)
{
    cw->setMessage(msg);
}

void mainWindow::moveToCenter()
{
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void mainWindow::update()
{

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

void mainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keystr = "KeyPressed " + QString(to_string(event->key()).c_str());
    sb1->setText(keystr);
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
    emit runScenario();
    //sc->action();
}

void mainWindow::view()
{
    QProcess vim;
    vim.startDetached("google-chrome Commutator.html");
    vim.waitForFinished();
}

void mainWindow::toolsWindow()
{
    emit tools(false);
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
    //string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Завершение работы программы ") + log->GetDateTime() + string("</div>");
    //log->log(msg);
    event->accept();
//    if (askClose()) { event->accept(); }
//    else { event->ignore(); }
}

