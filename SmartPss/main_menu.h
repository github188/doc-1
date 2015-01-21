#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QMenu>

class MainMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void translateActions();
signals:
    void ShowMenuDialog();
public slots:

private:

    void createActions();
private:
    QAction* action_Camera;
    QAction* action_Record;
    QAction* action_Alarm;
    QAction* action_Disk;
    QAction* action_Menu;

};

#endif // MAIN_MENU_H
