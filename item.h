#ifndef ITEM_H
#define ITEM_H
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPointF>

class Item
{
public:
    Item();
    QPixmap item;
    QRectF item_rect;
    int item_x,item_y;
    int item_select;
    int item_check;
    int whatItem;
    int item_count;
};

#endif // ITEM_H
