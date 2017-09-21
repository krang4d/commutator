#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QFile>
#include <QTextCodec>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QProcess>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <string>
#include <observer.h>
#include <composite.h>

class CenterWidget;
class Logger;
class StartDialog;

using std::string;

class mainWindow : public QMainWindow, Observer
{
    Q_OBJECT

public:
    explicit mainWindow(Subject *control, Logger *log);
    ~mainWindow();
    void setNextLine(string);
    Logger *getLogger();
    void moveToCenter();
    virtual void update() override;

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void closeEvent(QCloseEvent *event);

    void InitWindow();

private slots:
    void about();
    void run();
    void view();
    void toolsWindow();
    void setmessage(QString str);

signals:
    void tools(bool);
    void runScenario();

private:
    QAction *startAction;
    QAction *viewAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *toolsAction;

    QMenu *fileMenu;
    QMenu *HelpMenu;
    QLabel *sb1;
    QLabel *sb2;
    QLabel *sb3;

    CenterWidget *cw;
    Logger *log_;

    QTimer *tm;
    bool askClose();



};

#endif // MAINWINDOW_H
