#include "video_widget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent)
{
    mouse_press = false;
    mouse_over = false;
    widget_fullscreen = false;
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setContentsMargins(0,0,0,0);
    video_bottom = new VideoBottom();

    QHBoxLayout* videoLayout = new QHBoxLayout();
    videoLayout->addStretch(50);
    videoLayout->addWidget(video_bottom);
    videoLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch(5);
    mainLayout->addLayout(videoLayout);
    mainLayout->addStretch(5);
    mainLayout->setContentsMargins(0,0,0,0);

    this->setLayout(mainLayout);
   // video_bottom->setFixedSize(rect().width()*0.2,rect().height()*0.8);
 //   video_bottom->move(rect().right()-video_bottom->rect().right(),rect().top()-15);
    video_bottom->setVisible(false);
}


void VideoWidget::enterEvent(QEvent *event)
{
    mouse_over = true;
}

void VideoWidget::leaveEvent(QEvent *event)
{
    mouse_over = false;
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    brush.setColor(QColor(100,100,100));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(rect());
    QPen pen(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    painter.setPen(pen);
    QString text = "No video signal";
    QFont font = painter.font();
    font.setPixelSize(30);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();
    QPoint pt((rect().width() - fm.width(text))/2,(rect().height()-(fm.ascent()+fm.descent()))/2+fm.ascent());
    painter.drawText(pt,text);
    if(mouse_press)
    {
        pen.setColor(QColor(0,255,0));
        painter.setPen(pen);
        int x1 = rect().left();
        int y1 = rect().top();
        int x2 = rect().right();
        int y2 = rect().bottom();
        painter.drawLine(x1,y1,x2,y1);
        painter.drawLine(x2,y1,x2,y2);
        painter.drawLine(x2,y2,x1,y2);
        painter.drawLine(x1,y2,x1,y1);
    }
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit VideoClicked();
    }
}

void VideoWidget::setMousePress(bool mouse_press)
{
    this->mouse_press = mouse_press;
    video_bottom->setVisible(mouse_press);

    update();
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(widget_fullscreen)
        {
            this->setWindowFlags(Qt::SubWindow);
            this->showNormal();
            widget_fullscreen = false;
        }
        else
        {
            this->setWindowFlags(Qt::Dialog);
            this->showFullScreen();
            widget_fullscreen = true;
        }
    }
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
//    if(event->isAutoRepeat())
//    {
//        event->ignore();
//        return;
//    }
    if(event->key()== Qt::Key_Escape)
    {
        if(widget_fullscreen)
        {
            this->setWindowFlags(Qt::SubWindow);
            this->showNormal();
            widget_fullscreen = false;
        }
    }
//    qDebug()<<event->key()<<"------"<<event->type()<<"-------"<<event->modifiers();
//    if((event->modifiers()==Qt::AltModifier) && (event->key()== Qt::Key_F4))
//    {
//        qDebug()<<"you press Alt + F4";
//    }
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
