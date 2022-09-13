#ifndef BRICK_H
#define BRICK_H
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPointF>
#include <QDebug>

class Brick
{
public:
    QPixmap bricks;
    QRectF bricks_rect;
    int brick_x;
    int brick_y;
    int brick_show;
    Brick();
};

#endif // BRICK_H
