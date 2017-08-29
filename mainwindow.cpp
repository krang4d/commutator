#include "mainwindow.h"

mainWindow::mainWindow(){
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);

    cw = new CenterWidget(this);

    aboutAction = new QAction(tr("&O программе"), this);
    aboutAction->setStatusTip(tr("Сведения о программе"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

    exitAction = new QAction(tr("В&ыход"));
    exitAction->setStatusTip(tr("Выход из программы"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

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

    setCentralWidget(cw);

}
void mainWindow::setNextLine(QString *msg){
    cw->setMessage(msg);
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
