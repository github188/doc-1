#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QSplitter>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>

#include "common.h"

class CameraWidget : public QDialog
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = 0);
    bool DeviceExist(char* IpAddress);
    bool DeviceInList(char* IpAddress);
    void GetRtspUrl(char* ipaddress,char* url,int port,char* username,char* password);

signals:

public slots:
    void SearchDevice();
    void CloseDialog();
private:
    void InitDownLeft();
    void InitDownRight();
    void InitTable();
    void InitOnvif();

    //static void DeviceCallBack(DEVICE_BINFO* p_res,void* pData);
private:
    QWidget* top_widget;
    QLabel* camera_img;
    QLabel* camera_label;
    QPushButton* close_button;

    QSplitter* down_splitter;
    QSplitter* down_left_splitter;
    QWidget* manage_camera;
    QLabel* label_camera;
    QPushButton* add_camera;
    QPushButton* edit_camera;

    QWidget* image_setting;
    QLabel* label_image;
    QPushButton* osd_config;
    QPushButton* image_config;

    QSplitter* main_splitter;
    QWidget* camera_info;
    QTableWidget* camera_list;

   // ONVIF_DEVICE* m_pDev;
public:
    QList<DeviceInfo> m_DeviceList;
};

#endif // CAMERA_WIDGET_H
