#include "menu_dialog.h"

MenuDialog::MenuDialog(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    main_splitter = new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Vertical);
    main_splitter->setHandleWidth(1);

    top_splitter = new QSplitter();
    top_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    top_splitter->setOrientation(Qt::Horizontal);
    top_splitter->setHandleWidth(1);

    this->InitTopleft();
    this->InitTopleftCenter();
    this->InitToprightCenter();
    this->InitTopright();
    top_left_widget->setFixedSize(240,130);
    top_leftcenter_widget->setFixedSize(240,130);
    top_rightcenter_widget->setFixedSize(240,130);
    top_right_widget->setFixedSize(240,130);
    top_splitter->addWidget(top_left_widget);
    top_splitter->addWidget(top_leftcenter_widget);
    top_splitter->addWidget(top_rightcenter_widget);
    top_splitter->addWidget(top_right_widget);

    bottom_splitter = new QSplitter();
    bottom_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bottom_splitter->setOrientation(Qt::Horizontal);
    bottom_splitter->setHandleWidth(1);

    this->InitBottomleft();
    this->InitBottomCenter();
    this->InitBottomright();
    bottom_left_widget->setFixedSize(320,130);
    bottom_center_widget->setFixedSize(320,130);
    bottom_right_widget->setFixedSize(320,130);
    bottom_splitter->addWidget(bottom_left_widget);
    bottom_splitter->addWidget(bottom_center_widget);
    bottom_splitter->addWidget(bottom_right_widget);

    main_splitter->addWidget(top_splitter);
    main_splitter->addWidget(bottom_splitter);
    for(int i = 0; i<top_splitter->count();i++)
    {
         QSplitterHandle *handle = top_splitter->handle(i);
         handle->setEnabled(false);
    }

    for(int i = 0; i<bottom_splitter->count();i++)
    {
         QSplitterHandle *handle = bottom_splitter->handle(i);
         handle->setEnabled(false);
    }

    for(int i = 0; i<main_splitter->count();i++)
    {
         QSplitterHandle *handle = main_splitter->handle(i);
         handle->setEnabled(false);
    }


    QHBoxLayout* main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);


    connect(label_Camera,SIGNAL(clicked()),this,SLOT(showCameraDlg()));
    this->setLayout(main_layout);
    this->setObjectName("MainWindow");
}

void MenuDialog::InitTopleft()
{
    top_left_widget = new QWidget();
    label_Camera = new QPushButton();
    label_Camera_img = new QLabel();
    addCamera_button = new QPushButton();
    edit_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/camera");
    label_Camera_img->setPixmap(*pixmap);
    label_Camera_img->setFixedSize(pixmap->width(),pixmap->height());

    label_Camera->setObjectName("whiteButton");
    addCamera_button->setObjectName("blueButton");
    edit_button->setObjectName("blueButton");

    label_Camera->setText("Camera");
    QFont dev_font = label_Camera->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_Camera->setFont(dev_font);
    //label_Camera->setAlignment(Qt::AlignHCenter);

    addCamera_button->setText("Add Camera");
    edit_button->setText("Edit Camera");

    QVBoxLayout* rightLayout = new QVBoxLayout();


    rightLayout->addWidget(label_Camera);
    rightLayout->addWidget(addCamera_button);
    rightLayout->addWidget(edit_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_Camera_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    top_left_widget->setLayout(mainLayout);
    top_left_widget->setObjectName("blueWindow");
}

void MenuDialog::InitTopleftCenter()
{

    top_leftcenter_widget = new QWidget();
    label_Record = new QPushButton();
    label_Record_img = new QLabel();
    Code_button = new QPushButton();
    Record_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/record");
    label_Record_img->setPixmap(*pixmap);
    label_Record_img->setFixedSize(pixmap->width(),pixmap->height());

    label_Record->setObjectName("whiteButton");
    Code_button->setObjectName("blueButton");
    Record_button->setObjectName("blueButton");

    label_Record->setText("Record");
    QFont dev_font = label_Record->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_Record->setFont(dev_font);
    //label_Record->setAlignment(Qt::AlignHCenter);

    Code_button->setText("Code Parammeters");
    Record_button->setText("Record Schedule");

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(label_Record);
    rightLayout->addWidget(Code_button);
    rightLayout->addWidget(Record_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_Record_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    top_leftcenter_widget->setLayout(mainLayout);
    top_leftcenter_widget->setObjectName("blackWindow");
}

void MenuDialog::InitToprightCenter()
{

    top_rightcenter_widget = new QWidget();
    label_Alarm = new QPushButton();
    label_Alarm_img = new QLabel();
    Sensor_button = new QPushButton();
    Alarm_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/alarm");
    label_Alarm_img->setPixmap(*pixmap);
    label_Alarm_img->setFixedSize(pixmap->width(),pixmap->height());

    label_Alarm->setObjectName("whiteButton");
    Sensor_button->setObjectName("blueButton");
    Alarm_button->setObjectName("blueButton");

    label_Alarm->setText("Alarm");
    QFont dev_font = label_Alarm->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_Alarm->setFont(dev_font);
    //label_Alarm->setAlignment(Qt::AlignHCenter);

    Sensor_button->setText("Sensor Alarm");
    Alarm_button->setText("Alarm out");

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(label_Alarm);
    rightLayout->addWidget(Sensor_button);
    rightLayout->addWidget(Alarm_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_Alarm_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    top_rightcenter_widget->setLayout(mainLayout);
    top_rightcenter_widget->setObjectName("blueWindow");
}

void MenuDialog::InitTopright()
{

    top_right_widget = new QWidget();
    label_Disk = new QPushButton();
    label_Disk_img = new QLabel();
    Addraid_button = new QPushButton();
    Storage_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/disk");
    label_Disk_img->setPixmap(*pixmap);
    label_Disk_img->setFixedSize(pixmap->width(),pixmap->height());

    label_Disk->setObjectName("whiteButton");
    Addraid_button->setObjectName("blueButton");
    Storage_button->setObjectName("blueButton");


    label_Disk->setText("Disk");
    QFont dev_font = label_Disk->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_Disk->setFont(dev_font);
    //label_Disk->setAlignment(Qt::AlignHCenter);

    Addraid_button->setText("Add RAID");
    Storage_button->setText("Storage Mode");

    QVBoxLayout* rightLayout = new QVBoxLayout();


    rightLayout->addWidget(label_Disk);
    rightLayout->addWidget(Addraid_button);
    rightLayout->addWidget(Storage_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_Disk_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    top_right_widget->setLayout(mainLayout);
    top_right_widget->setObjectName("greenWindow");
}

void MenuDialog::InitBottomleft()
{

    bottom_left_widget = new QWidget();
    label_Network = new QPushButton();
    label_Network_img = new QLabel();
    TCP_button = new QPushButton();
    DDNS_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/network");
    label_Network_img->setPixmap(*pixmap);
    label_Network_img->setFixedSize(pixmap->width(),pixmap->height());

    label_Network->setObjectName("whiteButton");
    DDNS_button->setObjectName("blueButton");
    TCP_button->setObjectName("blueButton");

    label_Network->setText("Network");
    QFont dev_font = label_Network->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_Network->setFont(dev_font);
    //label_Network->setAlignment(Qt::AlignHCenter);


    TCP_button->setText("TCP/IPV4");
    DDNS_button->setText("DDNS");

    QVBoxLayout* rightLayout = new QVBoxLayout();


    rightLayout->addWidget(label_Network);
    rightLayout->addWidget(TCP_button);
    rightLayout->addWidget(DDNS_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_Network_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    bottom_left_widget->setLayout(mainLayout);
    bottom_left_widget->setObjectName("greenWindow");
}

void MenuDialog::InitBottomCenter()
{

    bottom_center_widget = new QWidget();
    label_User = new QPushButton();
    label_User_img = new QLabel();
    Adduser_button = new QPushButton();
    Edituser_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/user");
    label_User_img->setPixmap(*pixmap);
    label_User_img->setFixedSize(pixmap->width(),pixmap->height());

    label_User->setObjectName("whiteButton");
    Edituser_button->setObjectName("blueButton");
    Adduser_button->setObjectName("blueButton");

    label_User->setText("Account and Security");
    QFont dev_font = label_User->font();
    dev_font.setPointSize(12);
    dev_font.setBold(true);
    label_User->setFont(dev_font);
    //label_User->setAlignment(Qt::AlignHCenter);

    Adduser_button->setText("Add User");
    Edituser_button->setText("Edit User");

    QVBoxLayout* rightLayout = new QVBoxLayout();


    rightLayout->addWidget(label_User);
    rightLayout->addWidget(Adduser_button);
    rightLayout->addWidget(Edituser_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_User_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    bottom_center_widget->setLayout(mainLayout);
    bottom_center_widget->setObjectName("blueWindow");
}

void MenuDialog::InitBottomright()
{

    bottom_right_widget = new QWidget();
    label_System = new QPushButton();
    label_System_img = new QLabel();
    Basic_button = new QPushButton();
    Date_button = new QPushButton();

    QPixmap* pixmap = new QPixmap(":/img/system");
    label_System_img->setPixmap(*pixmap);
    label_System_img->setFixedSize(pixmap->width(),pixmap->height());

    label_System->setObjectName("whiteButton");
    Date_button->setObjectName("blueButton");
    Basic_button->setObjectName("blueButton");

    label_System->setText("System");
    QFont dev_font = label_System->font();
    dev_font.setPointSize(24);
    dev_font.setBold(true);
    label_System->setFont(dev_font);
    //label_System->setAlignment(Qt::AlignHCenter);

    Basic_button->setText("Basic");
    Date_button->setText("Date and Time");

    QVBoxLayout* rightLayout = new QVBoxLayout();


    rightLayout->addWidget(label_System);
    rightLayout->addWidget(Basic_button);
    rightLayout->addWidget(Date_button);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(label_System_img);
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacing(0);

    bottom_right_widget->setLayout(mainLayout);
    bottom_right_widget->setObjectName("blackWindow");
}


void MenuDialog::showCameraDlg()
{
    emit showDeviceDlg();
    this->close();
}
