#ifndef BALL_H
#define BALL_H
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPointF>
#include<QtMath>
#include <QDebug>
#define PI 3.1415926535
class Ball
{
public:
    QPixmap ball;
    QRectF ball_rect;
    QRectF rot_rect;
    int ball_x;
    int ball_y;
    int deg;
    int speed;
    double radian;
    void move(int d);
    Ball();

};

#endif // BALL_H
