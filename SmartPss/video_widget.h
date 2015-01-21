#ifndef VIDEO_WIDGET_H
#define VIDEO_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QCloseEvent>
#include "video_bottom.h"

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);
    void setMousePress(bool mouse_press);
signals:
    void VideoClicked();
public slots:

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);

private:
    bool mouse_press;
    bool mouse_over;
    bool widget_fullscreen;
    QPoint m_point;
    VideoBottom* video_bottom;
};

#endif // VIDEO_WIDGET_H
