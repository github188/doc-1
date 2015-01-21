#include "video_bottom.h"

VideoBottom::VideoBottom(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    audio_input_button = new QToolButton();
    audio_output_button = new QToolButton();
    talk_button = new QToolButton();
    camera_button = new QToolButton();
    replay_button = new QToolButton();
    shotnap_button = new QToolButton();
    zoom_button = new QToolButton();

    QPixmap* pixmap = new QPixmap(":/videobottom/sound");
    audio_input_button->setIcon(*pixmap);

    QPixmap* pixmap1 = new QPixmap(":/videobottom/audio");
    audio_output_button->setIcon(*pixmap1);

    QPixmap* pixmap2 = new QPixmap(":/videobottom/talk");
    talk_button->setIcon(*pixmap2);

    QPixmap* pixmap3 = new QPixmap(":/videobottom/replay");
    replay_button->setIcon(*pixmap3);

    QPixmap* pixmap4 = new QPixmap(":/videobottom/snapshot");
    shotnap_button->setIcon(*pixmap4);

    QPixmap* pixmap5 = new QPixmap(":/videobottom/zoom");
    zoom_button->setIcon(*pixmap5);

    QPixmap* pixmap6 = new QPixmap(":/videobottom/camera");
    camera_button->setIcon(*pixmap6);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(audio_input_button);
    mainLayout->addWidget(replay_button);
    mainLayout->addWidget(audio_output_button);
    mainLayout->addWidget(shotnap_button);
    mainLayout->addWidget(camera_button);
    mainLayout->addWidget(zoom_button);
    mainLayout->addWidget(talk_button);
    mainLayout->addSpacing(0);

    this->setObjectName("MainWindow");
    this->setLayout(mainLayout);

}

void VideoBottom::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap* pixmap = new QPixmap();
    pixmap->load(":/videobottom/tool");
    painter.drawPixmap(QRect(0,0,this->width(),this->height()),*pixmap);
}
