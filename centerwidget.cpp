#include "centerwidget.h"

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    setupLayout();

    connect(ExitButton, SIGNAL(pressed()), this, SIGNAL(Exit()));
    connect(StartButton, SIGNAL(pressed()), this, SIGNAL(Start()));
    connect(ViewButton, SIGNAL(pressed()), this, SIGNAL(View()));
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
    ViewButton = new QPushButton(tr("Просмотреть файл"));
    ExitButton = new QPushButton(tr("Закрыть программу"));
    slaveLayout->addWidget(StartButton);
    slaveLayout->addWidget(ViewButton);
    slaveLayout->addWidget(ExitButton);
    masterLayout->addLayout(slaveLayout);
    setLayout(masterLayout);
}

void CenterWidget::setMessage(QString msg){
    MessageTextEdit->setText(msg);
}
