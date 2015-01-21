#include "main_menu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMenu(parent)
{
    this->createActions();
    this->translateActions();
    this->setObjectName("menu");
    setFixedWidth(200);
}

void MainMenu::createActions()
{
    action_Camera = new QAction(this);
    action_Record = new QAction(this);
    action_Alarm = new QAction(this);
    action_Disk = new QAction(this);
    action_Menu = new QAction(this);

    action_Alarm->setIcon(QIcon(QPixmap(":/img/menualarm")));
    action_Menu->setIcon(QIcon(QPixmap(":/img/body")));
    action_Camera->setIcon(QIcon(QPixmap(":/img/devcfg")));
    this->addAction(action_Camera);
    this->addAction(action_Record);
    this->addAction(action_Alarm);
    this->addAction(action_Disk);
    this->addSeparator();
    this->addAction(action_Menu);

//	action_help_online->setObjectName(QString::number(HELP_ONLINE, 10));
//	action_platform_help->setObjectName(QString::number(PLATFORM_HELP, 10));
//	action_login_home->setObjectName(QString::number(LOGIN_HOME, 10));
//	action_protect->setObjectName(QString::number(PROTECT, 10));

    connect(action_Menu,SIGNAL(triggered()),this,SIGNAL(ShowMenuDialog()));
//	connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
//	connect(action_new_character, SIGNAL(triggered()), this, SIGNAL(showNewCharacter()));
//	connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));
//	connect(action_help_online, SIGNAL(triggered()), this, SLOT(showPage()));
//	connect(action_platform_help, SIGNAL(triggered()), this, SLOT(showPage()));
//	connect(action_login_home, SIGNAL(triggered()), this, SLOT(showPage()));
//	connect(action_protect, SIGNAL(triggered()), this, SLOT(showPage()));
}

void MainMenu::translateActions()
{
    action_Camera->setText("Camera");
    action_Record->setText("Record");
    action_Alarm->setText("Alarm");
    action_Disk->setText("Disk");
    action_Menu->setText("Menu");
}
