#include "camera_widget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QDialog(parent)
{
    this->setObjectName("MainWindow");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());
    camera_img = new QLabel();
    camera_label = new QLabel();
    close_button = new QPushButton();
    top_widget = new QWidget();
    QPixmap* pixmap = new QPixmap(":/videobottom/camera");
    camera_img->setPixmap(*pixmap);
    camera_img->setFixedSize(pixmap->width(),pixmap->height());
    QFont font = camera_label->font();
    font.setPointSize(25);
    camera_label->setFont(font);
    camera_label->setText("Camera");
    QPixmap* btnpixmap = new QPixmap(":/img/back");
    close_button->setIcon(*btnpixmap);
    close_button->setFixedSize(btnpixmap->width(),btnpixmap->height());

    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->addWidget(camera_img);
    labelLayout->addWidget(camera_label);
    labelLayout->addStretch();
    labelLayout->addWidget(close_button);
    labelLayout->setContentsMargins(0,0,0,0);
    top_widget->setLayout(labelLayout);

    down_splitter = new QSplitter();
    down_left_splitter = new QSplitter();
    main_splitter = new QSplitter();

    down_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    down_splitter->setOrientation(Qt::Horizontal);
    down_splitter->setHandleWidth(1);
    down_left_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    down_left_splitter->setOrientation(Qt::Vertical);
    down_left_splitter->setHandleWidth(1);
    main_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    main_splitter->setOrientation(Qt::Vertical);
    main_splitter->setHandleWidth(1);

    this->InitDownLeft();
    this->InitDownRight();



    down_left_splitter->addWidget(manage_camera);
    down_left_splitter->addWidget(image_setting);


    down_splitter->addWidget(down_left_splitter);
    down_splitter->addWidget(camera_info);

    main_splitter->addWidget(top_widget);
    main_splitter->addWidget(down_splitter);


    QVBoxLayout* mainlayout = new QVBoxLayout();
 //   mainlayout->addWidget(top_widget);
    mainlayout->addWidget(main_splitter);
    mainlayout->addStretch();
    mainlayout->setContentsMargins(5,0,5,0);

    this->setLayout(mainlayout);
    connect(close_button,SIGNAL(clicked()),this,SLOT(CloseDialog()));
    InitOnvif();
}

void CameraWidget::InitDownLeft()
{
    manage_camera = new QWidget();
    label_camera = new QLabel();
    add_camera = new QPushButton();
    edit_camera = new QPushButton();
    QFont font = label_camera->font();
    font.setPointSize(18);
    label_camera->setFont(font);
    label_camera->setText("Manage Camera");

    add_camera->setText("add camera");
    edit_camera->setText("edit camera");

    add_camera->setObjectName("blueButton");
    edit_camera->setObjectName("blueButton");

    QVBoxLayout * manageLayout = new QVBoxLayout();
    manageLayout->addWidget(label_camera);
    manageLayout->addWidget(add_camera);
    manageLayout->addWidget(edit_camera);
    manageLayout->setSpacing(0);
    manageLayout->setContentsMargins(0,0,0,0);
    manage_camera->setLayout(manageLayout);
    manage_camera->setFixedWidth(200);
    manage_camera->setFixedHeight(100);

    image_setting = new QWidget();
    label_image = new QLabel();
    osd_config = new QPushButton();
    image_config = new QPushButton();

    QFont font1 = label_image->font();
    font1.setPointSize(18);
    label_image->setFont(font1);
    label_image->setText("Image Setting");

    osd_config->setText("osd config");
    image_config->setText("image config");

    osd_config->setObjectName("blueButton");
    image_config->setObjectName("blueButton");
    QVBoxLayout * imageLayout = new QVBoxLayout();
    imageLayout->addWidget(label_image);
    imageLayout->addWidget(osd_config);
    imageLayout->addWidget(image_config);
    imageLayout->setSpacing(0);
    imageLayout->setContentsMargins(0,0,0,0);
    image_setting->setLayout(imageLayout);
    image_setting->setFixedWidth(200);
    image_setting->setFixedHeight(100);
}

void CameraWidget::InitDownRight()
{
    camera_info = new QWidget();
    camera_list = new QTableWidget();
    InitTable();
    camera_info->setFixedWidth(QApplication::desktop()->width()-210);
    camera_info->setFixedHeight(QApplication::desktop()->height()-20);
    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->addWidget(camera_list);
    infoLayout->setContentsMargins(80,80,80,80);

    camera_info->setLayout(infoLayout);

}

void CameraWidget::InitTable()
{
    QStringList stringList;
    stringList<<"NO"<<"IP Address"<<"url"<<"Port";
    camera_list->setColumnCount(stringList.count());

    QFont font = camera_list->horizontalHeader()->font();
    font.setBold(true);
    camera_list->horizontalHeader()->setFont(font);
    camera_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    camera_list->setHorizontalHeaderLabels(stringList);
    camera_list->verticalHeader()->setVisible(false);

    camera_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    camera_list->setSelectionMode(QAbstractItemView::SingleSelection);
    camera_list->setFrameShape(QFrame::NoFrame);
    camera_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    camera_list->setAlternatingRowColors(true);

    //camera_list->setShowGrid(false);
   // camera_list->setRowCount(18);
    camera_list->setObjectName("CameraList");
}

void CameraWidget::InitOnvif()
{
    //m_pDev = new ONVIF_DEVICE;
   // ONVIF_Init(m_pDev);
    //ONVIF_DeviceSearch(DeviceCallBack,this);
}

void CameraWidget::SearchDevice()
{
  //  ONVIF_SendProbe();
}

//void CameraWidget::DeviceCallBack(DEVICE_BINFO *p_res, void *pData)
//{
//    qDebug()<<"recv a device\n ";
//    if(NULL == p_res || NULL == pData)
//    {
//        return;
//    }
//    qDebug()<<p_res->xaddr.host<<"\n"<<p_res->xaddr.port<<"\n"<<p_res->xaddr.url<<"\n";
//    CameraWidget* pThis = (CameraWidget*)pData;
//    if(pThis->DeviceExist(p_res->xaddr.host))
//    {
//        return;
//    }
//    pThis->camera_list->insertRow(pThis->camera_list->rowCount());
//    pThis->camera_list->setItem(pThis->camera_list->rowCount()-1,0,new QTableWidgetItem(QString::number(pThis->camera_list->rowCount())));
//    pThis->camera_list->setItem(pThis->camera_list->rowCount()-1,1,new QTableWidgetItem(QString(QLatin1String(p_res->xaddr.host))));
//    pThis->camera_list->setItem(pThis->camera_list->rowCount()-1,2,new QTableWidgetItem(QString(QLatin1String(p_res->xaddr.url))));
//    pThis->camera_list->setItem(pThis->camera_list->rowCount()-1,3,new QTableWidgetItem(QString::number(p_res->xaddr.port)));
//}

bool CameraWidget::DeviceExist(char* IpAddress)
{
    for(int i=0; i < camera_list->rowCount();i++)
    {
        QTableWidgetItem* item_widget = camera_list->item(i,1);
        QString str = item_widget->text();
        if(0 == str.compare(QLatin1String(IpAddress)))
        {
            return true;
        }
    }
    return false;
}

void CameraWidget::GetRtspUrl(char* ipaddress,char* url,int port,char* username,char* password)
{
    if(DeviceInList(ipaddress))
    {
        return;
    }
    DeviceInfo devinfo;
    memset(&devinfo,0,sizeof(DeviceInfo));
//    memset(m_pDev,0,sizeof(ONVIF_DEVICE));
//    strcpy(m_pDev->username,username);
//    strcpy(m_pDev->password,password);
//    strcpy(m_pDev->binfo.xaddr.host,ipaddress);
//    strcpy(m_pDev->binfo.xaddr.url,url);
//    m_pDev->binfo.xaddr.port = port;
//    qDebug()<<"username:"<<m_pDev->username<<"\n";
//    qDebug()<<"password:"<<m_pDev->password<<"\n";
////    if(ONVIF_GetDevInfo(m_pDev,cmdGetStreamUri))
//    {
//       QMessageBox message(QMessageBox::NoIcon,"Show Qt","Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, NULL);
//       message.exec();
//        return;
//    }
//    strcpy(devinfo.ip,ipaddress);
//    strcpy(devinfo.szName,ipaddress);
//    strcpy(devinfo.Mainrtspurl,m_pDev->profiles->stream_uri);
//    strcpy(devinfo.SubrtspUrl,m_pDev->profiles->next->stream_uri);
//    strcpy(devinfo.username,username);
//    strcpy(devinfo.password,password);
//    qDebug()<<"devinfo.Mainrtspurl:"<<devinfo.Mainrtspurl<<"\n";
//    qDebug()<<"devinfo.SubrtspUrl:"<<devinfo.SubrtspUrl<<"\n";
//    m_DeviceList.append(devinfo);
}

bool CameraWidget::DeviceInList(char *IpAddress)
{
    if(0 == m_DeviceList.count())
    {
        return false;
    }
    for(int i =0; i<m_DeviceList.count(); i++)
    {
       if(0==strcmp(m_DeviceList.at(i).ip,IpAddress))
       {
           return true;
       }
    }
    return false;
}

void CameraWidget::CloseDialog()
{
    for(int i=0; i < camera_list->rowCount();i++)
    {
        QTableWidgetItem* item_ip = camera_list->item(i,1);
        QString strIP = item_ip->text();
        QTableWidgetItem* item_url = camera_list->item(i,2);
        QString strUrl = item_url->text();
        QTableWidgetItem* item_port = camera_list->item(i,3);
        QString strPort = item_port->text();
        QByteArray IPba = strIP.toLatin1();
        QByteArray Urlba = strUrl.toLatin1();
        int nPort = strPort.toInt();
        qDebug()<<"GetRtspUrl---"<<IPba.data()<<"---"<<Urlba.data()<<"----"<<nPort<<"\n";
        GetRtspUrl(IPba.data(),Urlba.data(),nPort,"admin","default");
    }
    qDebug()<<"close camera Dialog\n";
    this->close();
}
