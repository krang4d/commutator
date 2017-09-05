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
    MessageLabel->setFont(QFont("Courier", 14));
    //masterLayout->addWidget(MessageLabel);
    MessageTextEdit = new QTextEdit;
    MessageTextEdit->setFont(QFont("Courier", 14));
    MessageTextEdit->setReadOnly(true);

    QHBoxLayout *ledSlaveLayout = new QHBoxLayout;
    Spacer = new QSpacerItem(500,30);
    Docking = new QLabel(tr("Стыковка"));
    Docking->setStyleSheet(tr("border-radius: 10px; background-color: #ff2200;"));
    Docking->setAlignment(Qt::AlignCenter);
    Docking->setFont(QFont("Courier", 14, QFont::Bold, true));
    Docking->resize(20, 20);
    BodyPower =  new QLabel(tr("Корпус"));
    BodyPower->setStyleSheet(tr("border-radius: 10px; background-color: #00ff00;"));
    BodyPower->setAlignment(Qt::AlignCenter);
    BodyPower->setFont(QFont("Courier", 14, QFont::Bold, true));

    ledSlaveLayout->addSpacerItem(Spacer);
    ledSlaveLayout->addWidget(Docking);
    ledSlaveLayout->addWidget(BodyPower);

    QHBoxLayout *buttonSlaveLayout = new QHBoxLayout;
    StartButton = new QPushButton(tr("Начать проверку"));
    StartButton->setFont(QFont("Courier", 14));
    ViewButton = new QPushButton(tr("Просмотреть файл"));
    ViewButton->setFont(QFont("Courier", 14));
    ExitButton = new QPushButton(tr("Закрыть программу"));
    ExitButton->setFont(QFont("Courier", 14));
    buttonSlaveLayout->addWidget(StartButton);
    buttonSlaveLayout->addWidget(ViewButton);
    buttonSlaveLayout->addWidget(ExitButton);

    masterLayout->addLayout(ledSlaveLayout);
    masterLayout->addWidget(MessageLabel);
    masterLayout->addWidget(MessageTextEdit);
    masterLayout->addLayout(buttonSlaveLayout);
    setLayout(masterLayout);
}

void CenterWidget::DockingChange(bool b)
{
    if(b) Docking->setStyleSheet("border-radius: 10px; background-color: #ff0000;");
    else Docking->setStyleSheet("border-radius: 10px; background-color: #00ff00;");
}

void CenterWidget::BodyPowerChange(bool b)
{
    if(b) BodyPower->setStyleSheet("border-radius: 10px; background-color: #ff0000;");
    else BodyPower->setStyleSheet("border-radius: 10px; background-color: #00ff00;");
}

void CenterWidget::setMessage(QString msg){
    MessageTextEdit->setText(msg);
}
