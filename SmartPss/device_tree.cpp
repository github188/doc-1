#include "device_tree.h"

DeviceTree::DeviceTree(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setObjectName("DeviceTree");
    this->setHeaderLabel("Group");
    this->headerItem()->setTextAlignment(0,Qt::AlignCenter);
}
