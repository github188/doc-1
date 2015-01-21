#include "main_widget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());
    title_widget = new TitleWidget();
    content_widget = new ContentWidget();
    main_menu = new MainMenu();
    menu_dialog = new MenuDialog();
    camera_widget =  new CameraWidget();

    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget,SIGNAL(SelectImageCount(int)),content_widget,SLOT(TurnPage(int)));
    connect(title_widget,SIGNAL(showProgramFullScreen()),content_widget,SLOT(showFull()));
    connect(main_menu,SIGNAL(ShowMenuDialog()),this,SLOT(showMenuDialog()));
    connect(menu_dialog,SIGNAL(showDeviceDlg()),this,SLOT(showCameraDialog()));
    connect(this,SIGNAL(AddDeviceTree(QList<DeviceInfo>*)),content_widget,SLOT(addDevTree(QList<DeviceInfo>*)));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(content_widget);
    mainLayout->addWidget(title_widget);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setObjectName("MainWindow");

}

void MainWidget::showMainMenu()
{
    QPoint p = title_widget->pos();
    p.setX(p.x()+10);
    p.setY(p.y()-125);
    main_menu->exec(this->mapToGlobal(p));
}

void MainWidget::showMenuDialog()
{
    menu_dialog->setWindowModality(Qt::ApplicationModal);
    menu_dialog->show();
    menu_dialog->move ((content_widget->width() - menu_dialog->width())/2,(content_widget->height() - menu_dialog->height())/2);
}

void MainWidget::showCameraDialog()
{
    camera_widget->setWindowModality(Qt::ApplicationModal);
    camera_widget->exec();
    emit AddDeviceTree(&camera_widget->m_DeviceList);
}

