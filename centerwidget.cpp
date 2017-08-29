#include "centerwidget.h"

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    setupLayout();

    connect(ExitButton, SIGNAL(pressed()), this, SIGNAL(Exit()));
    connect(StartButton, SIGNAL(pressed()), this, SIGNAL(Start()));
    connect(AbortButton, SIGNAL(pressed()), this, SIGNAL(Abort()));
}

void CenterWidget::setupLayout(){
    //Layout setup
    QVBoxLayout *masterLayout = new QVBoxLayout;
    MessageLabel = new QLabel(tr("Cообщения оператору"));
    masterLayout->addWidget(MessageLabel);
    MessageTextEdit = new QTextEdit;
    MessageTextEdit->setReadOnly(true);
    masterLayout->addWidget(MessageTextEdit);

    QHBoxLayout *slaveLayout = new QHBoxLayout;
    StartButton = new QPushButton(tr("Начать проверку"));
    AbortButton = new QPushButton(tr("Прервать проверку"));
    ExitButton = new QPushButton(tr("Закрыть программу"));
    slaveLayout->addWidget(StartButton);
    slaveLayout->addWidget(AbortButton);
    slaveLayout->addWidget(ExitButton);
    masterLayout->addLayout(slaveLayout);
    setLayout(masterLayout);
    qDebug() << QString("setupLayout()");
}

void CenterWidget::setMessage(QString *msg){
    //qDebug() << msg->toUtf8();
    //MessageTextEdit->setText(msg->toUtf8());
    //MessageTextEdit->setText(msg->toUtf8());
    MessageTextEdit->setText(*msg);
}
