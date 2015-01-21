#ifndef VIDEO_BOTTOM_H
#define VIDEO_BOTTOM_H

#include <QWidget>
#include <QToolButton>
#include <QLayout>
#include <QPainter>
#include <QPaintEvent>

class VideoBottom : public QWidget
{
    Q_OBJECT
public:
    explicit VideoBottom(QWidget *parent = 0);

signals:

public slots:
private:
    QToolButton* audio_input_button;
    QToolButton* replay_button;
    QToolButton* audio_output_button;
    QToolButton* shotnap_button;
    QToolButton* camera_button;
    QToolButton* zoom_button;
    QToolButton* talk_button;
protected:
    void paintEvent(QPaintEvent * event);

};

#endif // VIDEO_BOTTOM_H
