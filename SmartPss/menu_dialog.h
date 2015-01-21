#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H

#include <QWidget>
#include <QSplitter>
#include <QLayout>
#include <QLabel>
#include <QPushButton>


class MenuDialog : public QWidget
{
    Q_OBJECT
public:
    explicit MenuDialog(QWidget *parent = 0);

signals:
    void showDeviceDlg();
public slots:
    void showCameraDlg();
private:
    void InitTopleft();
    void InitTopleftCenter();
    void InitToprightCenter();
    void InitTopright();
    void InitBottomleft();
    void InitBottomCenter();
    void InitBottomright();
private:
    QSplitter* main_splitter;

    QSplitter* top_splitter;
    QWidget* top_left_widget;
    QLabel* label_Camera_img;
    QPushButton* label_Camera;
    QPushButton* addCamera_button;
    QPushButton* edit_button;

    QWidget* top_leftcenter_widget;
    QLabel* label_Record_img;
    QPushButton* label_Record;
    QPushButton* Code_button;
    QPushButton* Record_button;

    QWidget* top_rightcenter_widget;
    QLabel* label_Alarm_img;
    QPushButton* label_Alarm;
    QPushButton* Sensor_button;
    QPushButton* Alarm_button;

    QWidget* top_right_widget;
    QLabel* label_Disk_img;
    QPushButton* label_Disk;
    QPushButton* Addraid_button;
    QPushButton* Storage_button;

    QSplitter* bottom_splitter;
    QWidget* bottom_left_widget;
    QLabel* label_Network_img;
    QPushButton* label_Network;
    QPushButton* TCP_button;
    QPushButton* DDNS_button;

    QWidget* bottom_center_widget;
    QLabel* label_User_img;
    QPushButton* label_User;
    QPushButton* Adduser_button;
    QPushButton* Edituser_button;

    QWidget* bottom_right_widget;
    QLabel* label_System_img;
    QPushButton* label_System;
    QPushButton* Basic_button;
    QPushButton* Date_button;
};

#endif // MENU_DIALOG_H
