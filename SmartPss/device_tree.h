#ifndef DEVICE_TREE_H
#define DEVICE_TREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

class DeviceTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DeviceTree(QWidget *parent = 0);

signals:

public slots:

};

#endif // DEVICE_TREE_H
