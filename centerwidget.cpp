#include "centerwidget.h"

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    setupLayout();

    connect(ExitButton, SIGNAL(pressed()), this, SIGNAL(Exit()));
    connect(StartButton, SIGNAL(pressed()), this, SIGNAL(Start()));
    connect(ViewButton, SIGNAL(pressed()), this, SIGNAL(View()));
}

CenterWidget::~CenterWidget()
{
    delete Spacer;
    delete DockingLed;
    delete BodyPowerLed;
    delete MessageLabel;
    delete MessageTextEdit;
    delete StartButton;
    delete ViewButton;
    delete ExitButton;

    delete buttonSlaveLayout;
    delete ledSlaveHLayout;
    delete ledSlaveVLayout;
    delete masterLayout;
}

void CenterWidget::setupLayout(){
    //Layout setup
    masterLayout = new QVBoxLayout;

    MessageLabel = new QLabel(tr("Cообщения оператору"));
    MessageLabel->setFont(QFont("Courier", 14));
    //masterLayout->addWidget(MessageLabel);
    MessageTextEdit = new QTextEdit;
    MessageTextEdit->setFont(QFont("Courier", 14));
    MessageTextEdit->setReadOnly(true);

    ledSlaveVLayout = new QVBoxLayout;
    ledSlaveHLayout = new QHBoxLayout;

    Spacer = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    DockingLed = new QLabel(tr("Стыковка"));
    DockingLed->setStyleSheet(tr("border-radius: 10px; background-color: #ff2200;"));
    DockingLed->setAlignment(Qt::AlignCenter);
    DockingLed->setFont(QFont("Courier", 14, QFont::Bold, true));
    //DockingLed->resize(100, 50);
    BodyPowerLed =  new QLabel(tr("Корпус"));
    BodyPowerLed->setStyleSheet(tr("border-radius: 10px; background-color: #00ff00;"));
    BodyPowerLed->setAlignment(Qt::AlignCenter);
    BodyPowerLed->setFont(QFont("Courier", 14, QFont::Bold, true));

    ledSlaveHLayout->addSpacerItem(Spacer);
    ledSlaveVLayout->addWidget(DockingLed);
    ledSlaveVLayout->addWidget(BodyPowerLed);
    ledSlaveHLayout->addLayout(ledSlaveVLayout);

    buttonSlaveLayout = new QHBoxLayout;
    StartButton = new QPushButton(tr("Начать проверку"));
    StartButton->setFont(QFont("Courier", 14));
    ViewButton = new QPushButton(tr("Просмотреть файл"));
    ViewButton->setFont(QFont("Courier", 14));
    ExitButton = new QPushButton(tr("Закрыть программу"));
    ExitButton->setFont(QFont("Courier", 14));
    buttonSlaveLayout->addWidget(StartButton);
    buttonSlaveLayout->addWidget(ViewButton);
    buttonSlaveLayout->addWidget(ExitButton);

    masterLayout->addLayout(ledSlaveHLayout);
    masterLayout->addWidget(MessageLabel);
    masterLayout->addWidget(MessageTextEdit);
    masterLayout->addLayout(buttonSlaveLayout);
    this->setLayout(masterLayout);
}

void CenterWidget::DockingChange(bool b)
{
    if(b) DockingLed->setStyleSheet("border-radius: 10px; background-color: #ff0000;");
    else DockingLed->setStyleSheet("border-radius: 10px; background-color: #00ff00;");
}

void CenterWidget::BodyPowerChange(bool b)
{
    if(b) BodyPowerLed->setStyleSheet("border-radius: 10px; background-color: #ff0000;");
    else BodyPowerLed->setStyleSheet("border-radius: 10px; background-color: #00ff00;");
}

void CenterWidget::setMessage(std::string msg){
    messages.push_back(msg);
    std::string wstr;
    for(uint i = 0; i < messages.size(); i++)
        {
            wstr += messages[i];
            wstr += '\n';
        }
    MessageTextEdit->setText(QString(wstr.c_str()));
}
