#include "ball.h"

Ball::Ball()
{
    ball_x=12;
    ball_y=12;
    deg=0;
    radian=0;
    speed=2;
}
void Ball::move(int d)
{
    deg=d;
    radian=(deg/180.0)*PI;
    ball_x+=speed*cos(radian);
    ball_y-=speed*sin(radian);
}
