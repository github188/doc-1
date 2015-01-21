#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include "title_widget.h"
#include "content_widget.h"
#include "main_menu.h"
#include "menu_dialog.h"
#include "camera_widget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:
    void AddDeviceTree(QList<DeviceInfo>* pDevice);
public slots:

private slots:
    void showMainMenu();
    void showMenuDialog();
    void showCameraDialog();
private:
    TitleWidget* title_widget;
    ContentWidget* content_widget;
    MainMenu *main_menu;
    MenuDialog* menu_dialog;
    CameraWidget* camera_widget;
};

#endif // MAIN_WIDGET_H
