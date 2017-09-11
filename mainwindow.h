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
#include <string>

class Scenario;
class CenterWidget;
class Logger;
class Subject;

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

    void InitWindow();
    void CreateScenario();

private slots:
    void about();
    void run();
    void view();
    void toolsWindow();
    void updateTimer();

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
    Scenario *sc;
    Logger *log;
    Subject *control_value;

    QTimer *tm;
    bool askClose();



};

#endif // MAINWINDOW_H
