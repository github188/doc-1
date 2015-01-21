#include <QApplication>
#include "main_widget.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QFile qss(":/qss/Resource/SmartPss.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    MainWidget  mainwidget;
    mainwidget.show();
    return app.exec();
}
