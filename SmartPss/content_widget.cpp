#include "content_widget.h"

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pRtsp = NULL;
    layout_1 = new QHBoxLayout();
    layout_2 = new QHBoxLayout();
    layout_3 = new QHBoxLayout();
    layout_4 = new QHBoxLayout();
    device_tree = new DeviceTree();
    main_layout = new QVBoxLayout();

    device_tree->setFixedWidth(200);

    QSignalMapper* signal_mapper = new QSignalMapper(this);
    for(int i=0; i<16;i++)
    {
        VideoWidget* video_widget = new VideoWidget();
        video_widget->setObjectName("VideoWindow");
        connect(video_widget,SIGNAL(VideoClicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(video_widget,QString::number(i,10));
        widget_list.append(video_widget);
        if(i<4)
        {
            layout_1->addWidget(video_widget);
        }
        if(i>=4 && i<8)
        {
            layout_2->addWidget(video_widget);
        }
        if(i>=8 && i<12)
        {
            layout_3->addWidget(video_widget);
        }
        if(i>=12 && i<16)
        {
            layout_4->addWidget(video_widget);
        }
    }
    layout_1->setContentsMargins(0,0,0,0);
    layout_2->setContentsMargins(0,0,0,0);
    layout_3->setContentsMargins(0,0,0,0);
    layout_4->setContentsMargins(0,0,0,0);

    layout_1->setSpacing(0);
    layout_2->setSpacing(0);
    layout_3->setSpacing(0);
    layout_4->setSpacing(0);

    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(SelectVideo(QString)));
    main_layout->addLayout(layout_1);
    main_layout->addLayout(layout_2);
    main_layout->addLayout(layout_3);
    main_layout->addLayout(layout_4);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);

    contentLayout = new QHBoxLayout();
    contentLayout->addLayout(main_layout);
    contentLayout->addWidget(device_tree);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);

    setLayout(contentLayout);
    setFixedHeight(QApplication::desktop()->height()-80);
    setObjectName("MainWindow");


    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    m_bFull = false;
    connect(device_tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(connectImage(QTreeWidgetItem*,int)));
}

void ContentWidget::TurnPage(int nPage)
{
    switch(nPage)
    {
    case 1:
    {
        selectOne();
    }
        break;
    case 4:
    {
        selectFour();
    }
        break;
    case 9:
    {
        selectNine();
    }
        break;
    case 16:
    {
        selectSixteen();
    }
        break;
    default:
        break;
    }
}

void ContentWidget::removelayout(QLayout* layout_video)
{
    while(layout_video->count())
    {
        QLayoutItem* item = layout_video->takeAt(layout_video->count()-1);
        if(item->widget())
        {
            layout_video->removeWidget(item->widget());
            item->widget()->setVisible(false);
        }
        if(item->layout())
        {
            layout_video->removeItem(item);
        }

    }
//    layout_1->removeWidget(widget_list.at(0));
//    layout_1->removeWidget(widget_list.at(1));
//    layout_1->removeWidget(widget_list.at(2));
//    layout_1->removeWidget(widget_list.at(3));


//    widget_list.at(0)->setVisible(false);
//    widget_list.at(1)->setVisible(false);
//    widget_list.at(2)->setVisible(false);
//    widget_list.at(3)->setVisible(false);
}

void ContentWidget::removelayout2()
{
    layout_2->removeWidget(widget_list.at(4));
    layout_2->removeWidget(widget_list.at(5));
    layout_2->removeWidget(widget_list.at(6));
    layout_2->removeWidget(widget_list.at(7));

    widget_list.at(4)->setVisible(false);
    widget_list.at(5)->setVisible(false);
    widget_list.at(6)->setVisible(false);
    widget_list.at(7)->setVisible(false);
}

void ContentWidget::removelayout3()
{
    layout_3->removeWidget(widget_list.at(8));
    layout_3->removeWidget(widget_list.at(9));
    layout_3->removeWidget(widget_list.at(10));
    layout_3->removeWidget(widget_list.at(11));

    widget_list.at(8)->setVisible(false);
    widget_list.at(9)->setVisible(false);
    widget_list.at(10)->setVisible(false);
    widget_list.at(11)->setVisible(false);
}

void ContentWidget::removelayout4()
{
    layout_4->removeWidget(widget_list.at(12));
    layout_4->removeWidget(widget_list.at(13));
    layout_4->removeWidget(widget_list.at(14));
    layout_4->removeWidget(widget_list.at(15));

    widget_list.at(12)->setVisible(false);
    widget_list.at(13)->setVisible(false);
    widget_list.at(14)->setVisible(false);
    widget_list.at(15)->setVisible(false);
}

void ContentWidget::removemainlayout()
{
    device_tree->setVisible(false);
    main_layout->removeItem(layout_1);
    main_layout->removeItem(layout_2);
    main_layout->removeItem(layout_3);
    main_layout->removeItem(layout_4);
}

void ContentWidget::selectOne()
{


    removelayout(layout_1);
    removelayout(layout_2);
    removelayout(layout_3);
    removelayout(layout_4);
    removemainlayout();


    layout_1->addWidget(widget_list.at(0));
    widget_list.at(0)->setVisible(true);
    main_layout->addLayout(layout_1);
    device_tree->setVisible(true);
}



void ContentWidget::selectFour()
{

    removelayout(layout_1);
    removelayout(layout_2);
    removelayout(layout_3);
    removelayout(layout_4);
    removemainlayout();


    layout_1->addWidget(widget_list.at(0));
    widget_list.at(0)->setVisible(true);

    layout_1->addWidget(widget_list.at(1));
    widget_list.at(1)->setVisible(true);

    layout_2->addWidget(widget_list.at(2));
    widget_list.at(2)->setVisible(true);

    layout_2->addWidget(widget_list.at(3));
    widget_list.at(3)->setVisible(true);

    main_layout->addLayout(layout_1);
    main_layout->addLayout(layout_2);

    device_tree->setVisible(true);
}

void ContentWidget::selectNine()
{


    removelayout(layout_1);
    removelayout(layout_2);
    removelayout(layout_3);
    removelayout(layout_4);
    removemainlayout();

    layout_1->addWidget(widget_list.at(0));
    widget_list.at(0)->setVisible(true);
    layout_1->addWidget(widget_list.at(1));
    widget_list.at(1)->setVisible(true);
    layout_1->addWidget(widget_list.at(2));
    widget_list.at(2)->setVisible(true);

    layout_2->addWidget(widget_list.at(3));
    widget_list.at(3)->setVisible(true);
    layout_2->addWidget(widget_list.at(4));
    widget_list.at(4)->setVisible(true);
    layout_2->addWidget(widget_list.at(5));
    widget_list.at(5)->setVisible(true);

    layout_3->addWidget(widget_list.at(6));
    widget_list.at(6)->setVisible(true);
    layout_3->addWidget(widget_list.at(7));
    widget_list.at(7)->setVisible(true);
    layout_3->addWidget(widget_list.at(8));
    widget_list.at(8)->setVisible(true);
    main_layout->addLayout(layout_1);
    main_layout->addLayout(layout_2);
    main_layout->addLayout(layout_3);

    device_tree->setVisible(true);
}

void ContentWidget::selectSixteen()
{


    removelayout(layout_1);
    removelayout(layout_2);
    removelayout(layout_3);
    removelayout(layout_4);
    removemainlayout();


    layout_1->addWidget(widget_list.at(0));
    widget_list.at(0)->setVisible(true);
    layout_1->addWidget(widget_list.at(1));
    widget_list.at(1)->setVisible(true);
    layout_1->addWidget(widget_list.at(2));
    widget_list.at(2)->setVisible(true);
    layout_1->addWidget(widget_list.at(3));
    widget_list.at(3)->setVisible(true);

    layout_2->addWidget(widget_list.at(4));
    widget_list.at(4)->setVisible(true);
    layout_2->addWidget(widget_list.at(5));
    widget_list.at(5)->setVisible(true);
    layout_2->addWidget(widget_list.at(6));
    widget_list.at(6)->setVisible(true);
    layout_2->addWidget(widget_list.at(7));
    widget_list.at(7)->setVisible(true);

    layout_3->addWidget(widget_list.at(8));
    widget_list.at(8)->setVisible(true);
    layout_3->addWidget(widget_list.at(9));
    widget_list.at(9)->setVisible(true);
    layout_3->addWidget(widget_list.at(10));
    widget_list.at(10)->setVisible(true);
    layout_3->addWidget(widget_list.at(11));
    widget_list.at(11)->setVisible(true);

    layout_4->addWidget(widget_list.at(12));
    widget_list.at(12)->setVisible(true);
    layout_4->addWidget(widget_list.at(13));
    widget_list.at(13)->setVisible(true);
    layout_4->addWidget(widget_list.at(14));
    widget_list.at(14)->setVisible(true);
    layout_4->addWidget(widget_list.at(15));
    widget_list.at(15)->setVisible(true);
    main_layout->addLayout(layout_1);
    main_layout->addLayout(layout_2);
    main_layout->addLayout(layout_3);
    main_layout->addLayout(layout_4);

    device_tree->setVisible(true);
}

void ContentWidget::SelectVideo(QString current_page)
{
    bool ok;
    int current_index = current_page.toInt(&ok, 10);

    for(int i=0; i<widget_list.count(); i++)
    {
        VideoWidget *video_widget = widget_list.at(i);
        if(current_index == i)
        {
            video_widget->setMousePress(true);
        }
        else
        {
            video_widget->setMousePress(false);
        }
    }
}


void ContentWidget::showFull()
{
    m_bFull = !m_bFull;
    if(m_bFull)
    {
        this->setWindowFlags(Qt::Dialog);
        this->showFullScreen();
    }
    else
    {
        this->setWindowFlags(Qt::SubWindow);
        this->showNormal();
    }
}

void ContentWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(m_bFull)
        {
            showFull();
        }
    }
}

void ContentWidget::addDevTree(QList<DeviceInfo> *pDev)
{
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(QStringList()<<"Camera");
    device_tree->addTopLevelItem(rootItem);
    qDebug()<<"dev number"<<pDev->count()<<"\n";
    for(int i = 0; i< pDev->count(); i++)
    {
        QTreeWidgetItem* devItem = new QTreeWidgetItem(QStringList()<<pDev->at(i).szName);
        rootItem->addChild(devItem);

        QTreeWidgetItem* childItem = new QTreeWidgetItem(QStringList()<<"mainstream");
        devItem->addChild(childItem);
      //  childItem->setData(0,Qt::UserRole,QVariant::fromValue(int(&pDev->at(i))));
        QTreeWidgetItem* childItem1 = new QTreeWidgetItem(QStringList()<<"substream");
        devItem->addChild(childItem1);
    }
}

void ContentWidget::connectImage(QTreeWidgetItem *item, int nCloumn)
{
    DeviceInfo* pDev = (DeviceInfo*)item->data(nCloumn,Qt::UserRole).value<int>();
    qDebug()<<"double clicked tree:"<<pDev->Mainrtspurl<<"\n";
    qDebug()<<"double clicked tree:"<<pDev->SubrtspUrl<<"\n";
//   int nRes = RtspInit(VideoCallback,NULL,&m_pRtsp,this);
 //  int nStart =  RtspStart(m_pRtsp,pDev->Mainrtspurl,pDev->username,pDev->password,RTSPOVERTCP);
   //qDebug()<<"nRes::"<<nRes<<"-----nStart::"<<nStart<<"\n";
}


int ContentWidget::VideoCallback(char *pData, int nLength, unsigned int ts, unsigned short seq, void *pContent)
{
    ContentWidget* pThis = (ContentWidget*)pContent;
    qDebug()<<"pData::"<<pData<<"\n";
    return 0;
}
