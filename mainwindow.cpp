#include "mainwindow.h"
#include "centerwidget.h"
#include "tools.h"
#include "startdialog.h"
#include "logger.h"


mainWindow::mainWindow(Subject *control, Logger *log) : Observer(control), log_(log)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    InitWindow();
}

void mainWindow::InitWindow()
{
    fileMenu = new QMenu("&Файл");
    startAction = new QAction(tr("Начать проверку"));
    startAction->setShortcut(tr("Ctrl+R"));
    connect(startAction, SIGNAL(triggered(bool)), SIGNAL(runScenario()));
    fileMenu->addAction(startAction);

    viewAction = new QAction(tr("Просмотреть файл"));
    connect(viewAction, SIGNAL(triggered(bool)), SLOT(view()));
    fileMenu->addAction(viewAction);

    toolsAction = new QAction(tr("Дополнительные возможности..."));
    connect(toolsAction, SIGNAL(triggered(bool)), SIGNAL(tools(bool)));
    fileMenu->addAction(toolsAction);

    exitAction = new QAction(tr("Выход"));
    exitAction->setStatusTip(tr("Выход из программы"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered(bool)), SLOT(close()));
    fileMenu->addAction(exitAction);
    fileMenu->addSeparator();

    HelpMenu = new QMenu("&Спаравка");
    aboutAction = new QAction(tr("O программе"), this);
    aboutAction->setStatusTip(tr("Сведения о программе"));
    connect(aboutAction, SIGNAL(triggered(bool)), SLOT(about()));
    HelpMenu->addAction(aboutAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(HelpMenu);

    sb1 = new QLabel(statusBar());
    sb2 = new QLabel(statusBar());
    sb3 = new QLabel(statusBar());

    statusBar()->setSizeGripEnabled(false);
    statusBar()->addWidget(sb1, 3);
    statusBar()->addWidget(sb2, 1);
    statusBar()->addWidget(sb3, 1);

    sb1->setText(tr("Привет!"));
    setMouseTracking(true);

    cw = new CenterWidget();
    setCentralWidget(cw);
    connect(&thread1, SIGNAL(threadmessage(QString)), SLOT(setNextLine(QString)));
    connect(&thread1, SIGNAL(finished()), SLOT(finishScenario()));
    connect(cw, SIGNAL(Start()), SLOT(runScenario()));
    connect(cw, SIGNAL(Exit()), SLOT(close()));
    connect(cw, SIGNAL(View()), SLOT(view()));

}

mainWindow::~mainWindow()
{
}

void mainWindow::setNextLine(QString msg, bool time)
{
    if(time)
    {
        msg = "<div>" + msg + " " + QString(log_->GetTime().c_str()) + "</div>";
        sb1->setText(msg);
        log_->log(msg.toStdString());
        cw->setMessage(msg);
    }
    else
    {
    msg = "<div>" + msg + "</div>";
    log_->log(msg.toStdString());
    cw->setMessage(msg);
    }
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
    cw->BodyPowerChange(getSubject()->getBodyPower());
    cw->DockingChange(getSubject()->getDock());
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
    //string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Завершение работы программы ") + log->GetDateTime() + string("</div>");
    //log->log(msg);
    thread1.terminate();
    thread1.wait();
    event->accept();
//    if (askClose()) { event->accept(); }
    //    else { event->ignore(); }
}

void mainWindow::runScenario()
{
    if(thread1.isRunning())
    {
        thread1.terminate();
        cw->StartButton->setText(tr("Начать проверку"));
    }
    else
    {
        thread1.start();
        cw->StartButton->setText(tr("Прервать проверку"));
    }
}

void mainWindow::finishScenario()
{
    cw->StartButton->setText(tr("Начать проверку"));
}

