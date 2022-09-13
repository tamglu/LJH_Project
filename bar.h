#ifndef BAR_H
#define BAR_H
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPointF>
class Bar
{
protected:
    QPixmap bar;
    QRectF bar_rect;
    int length;
    int direction;
    int bar_mv;
    int bar_select;
    int HP;
    void movement(int d);
public:
    Bar();
};

#endif // BAR_H
