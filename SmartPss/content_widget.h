#ifndef CONTENT_WIDGET_H
#define CONTENT_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QList>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QSignalMapper>
#include <qnamespace.h>
#include "video_widget.h"
#include "device_tree.h"
#include "common.h"


class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);

signals:

public slots:
    void TurnPage(int nPage);
    void SelectVideo(QString current_page);
    void showFull();
    void addDevTree(QList<DeviceInfo>* pDev);
    void connectImage(QTreeWidgetItem* item,int nCloumn);
private:
    void removelayout1();
    void removelayout2();
    void removelayout3();
    void removelayout4();
    void removemainlayout();
    void removelayout(QLayout* layout_video);
    void selectOne();
    void selectFour();
    void selectNine();
    void selectSixteen();

private:
    QHBoxLayout* layout_1;
    QHBoxLayout* layout_2;
    QHBoxLayout* layout_3;
    QHBoxLayout* layout_4;
    QVBoxLayout* main_layout;
    DeviceTree* device_tree;
    QHBoxLayout* contentLayout;
    QList<VideoWidget*> widget_list;
    bool m_bFull;
protected:
    void keyPressEvent(QKeyEvent* event);

public:
    void* m_pRtsp;
    static int VideoCallback (char* pData, int nLength, unsigned int ts, unsigned short seq, void *pContent);
};

#endif // CONTENT_WIDGET_H
