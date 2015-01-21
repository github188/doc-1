#ifndef TITLE_WIDGET_H
#define TITLE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QTime>
#include <QTimer>
#include <QDate>
#include "tool_button.h"

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);

signals:
    void showMainMenu();
    void SelectImageCount(int nCount);
    void showProgramFullScreen();
public slots:
private slots:
    void changeLayout();
    void qtimeslot();
private:
    ToolButton* menuButton;

    ToolButton* fullScreenButton;
    ToolButton* OneScreenButton;
    ToolButton* FourScreenButton;
    ToolButton* NineScreenButton;
    ToolButton* SixteenScreenButton;
    ToolButton* ExternScreenButton;
    ToolButton* CircleButton;
    ToolButton* OsdButton;


    ToolButton* PreviewButton;
    ToolButton* ManualButton;
    ToolButton* RecordButton;
    ToolButton* LocalButton;
    ToolButton* NetworkButton;
    ToolButton* NeighbourButton;
    ToolButton* DiskButton;

    QLabel* DateLabel;
    QTimer* timer;
};

#endif // TITLE_WIDGET_H
