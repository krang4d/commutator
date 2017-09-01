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
#include <string>

class Scenario;
class CenterWidget;
class Logger;

using std::string;

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow();
    ~mainWindow();
    void setNextLine(string);


protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void about();
    void run();
    void view();

private:
    QAction *aboutAction;
    QAction *exitAction;
    QMenu *fileMenu;
    QLabel *sb1;
    QLabel *sb2;
    QLabel *sb3;

    CenterWidget *cw;
    Scenario *sc;
    Logger *log;

    bool askClose();



};

#endif // MAINWINDOW_H
