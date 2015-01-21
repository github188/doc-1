#include "title_widget.h"

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(qtimeslot()));
    timer->start(1000);
    menuButton = new ToolButton(":/img/temp");

    connect(menuButton, SIGNAL(clicked()), this, SIGNAL(showMainMenu()));

    fullScreenButton = new ToolButton(":/img/fullscreen");
    OneScreenButton = new ToolButton(":/img/one");
    FourScreenButton = new ToolButton(":/img/four");
    NineScreenButton = new ToolButton(":/img/nine");
    SixteenScreenButton = new ToolButton(":/img/sixteen");
    ExternScreenButton = new ToolButton(":/img/temp");
    CircleButton = new ToolButton(":/img/temp");
    OsdButton = new ToolButton(":/img/temp");

    PreviewButton = new ToolButton(":/img/temp");;
    ManualButton = new ToolButton(":/img/temp");
    RecordButton = new ToolButton(":/img/temp");
    LocalButton = new ToolButton(":/img/temp");
    NetworkButton = new ToolButton(":/img/temp");
    NeighbourButton = new ToolButton(":/img/temp");;
    DiskButton = new ToolButton(":/img/temp");

    DateLabel = new QLabel();
    DateLabel->setFixedHeight(48);

    connect(fullScreenButton,SIGNAL(clicked()),this,SIGNAL(showProgramFullScreen()));
    connect(OneScreenButton,SIGNAL(clicked()),this,SLOT(changeLayout()));
    connect(FourScreenButton,SIGNAL(clicked()),this,SLOT(changeLayout()));
    connect(NineScreenButton,SIGNAL(clicked()),this,SLOT(changeLayout()));
    connect(SixteenScreenButton,SIGNAL(clicked()),this,SLOT(changeLayout()));
    QHBoxLayout* menuLayout = new QHBoxLayout();
    menuLayout->addWidget(menuButton,0,Qt::AlignCenter);
    menuLayout->addStretch();

    QHBoxLayout* ScreenLayout = new QHBoxLayout();
    ScreenLayout->addStretch();
    ScreenLayout->addWidget(fullScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(OneScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(FourScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(NineScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(SixteenScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(ExternScreenButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(CircleButton,0,Qt::AlignCenter);
    ScreenLayout->addWidget(OsdButton,0,Qt::AlignCenter);

    QHBoxLayout* FunctionLayout = new QHBoxLayout();
    FunctionLayout->addStretch();
    FunctionLayout->addWidget(PreviewButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(ManualButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(RecordButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(LocalButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(NetworkButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(NeighbourButton,0,Qt::AlignCenter);
    FunctionLayout->addWidget(DiskButton,0,Qt::AlignCenter);

    QHBoxLayout* DateLayout = new QHBoxLayout();
    DateLayout->addStretch();
    DateLayout->addWidget(DateLabel,0,Qt::AlignCenter);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(menuLayout);
    mainLayout->addStretch(40);
    mainLayout->addLayout(ScreenLayout);
    mainLayout->addStretch(60);
    mainLayout->addLayout(FunctionLayout);
    mainLayout->addStretch(10);
    mainLayout->addLayout(DateLayout);
    mainLayout->addStretch(10);
    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);
    setFixedHeight(60);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

}

void TitleWidget::changeLayout()
{
    QObject* pSend = sender();
    if(OneScreenButton == pSend)
    {
       emit SelectImageCount(1);
    }
    else if(FourScreenButton == pSend)
    {
        emit SelectImageCount(4);
    }
    else if(NineScreenButton == pSend)
    {
        emit SelectImageCount(9);
    }
    else if(SixteenScreenButton == pSend)
    {
        emit SelectImageCount(16);
    }
}

void TitleWidget::qtimeslot()
{
    QTime qtimeobj = QTime::currentTime();
    QString strTime = qtimeobj.toString("hh:mm:ss");
    QDate qdateobj = QDate::currentDate();
    QString strDate = qdateobj.toString("MM-dd-yyyy");
    QString strDateTime;
    strDateTime = strDate + "\r\n" + strTime;
    DateLabel->setText(strDateTime);
    DateLabel->setAlignment(Qt::AlignCenter);
    QFont dateFont = DateLabel->font();
    dateFont.setPointSize(10);
    DateLabel->setFont(dateFont);

}
