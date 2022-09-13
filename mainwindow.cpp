#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setFixedSize(450,800);
    move(543,0);//1536:864

    myball=new Ball();
    myitem=new Item();
    for(int i=0; i<60; i++)
    {
        mybrick[i]=new Brick();
    }

    bar.load(":/new/prefix1/resource/bar.png");
    myball->ball.load(":/new/prefix1/resource/ball.png");
    myitem->item.load(":/new/prefix1/resource/item.png");
    for(int i=0; i<60; i++)
    {
        mybrick[i]->bricks.load(":/new/prefix1/resource/brick.png");
        mybrick[i]->bricks_rect.setRect(mybrick[i]->brick_show*45,0,45,22);
    }
    backgound.load(":/new/prefix1/resource/backgound.png");
    heart.load(":/new/prefix1/resource/heart.png");
    message.load(":/new/prefix1/resource/message.png");

    bar_rect.setRect(50,0,100,27);
    myball->ball_rect.setRect(0,0,24,24);
    myball->rot_rect.setRect(0,0,34,34);
    myitem->item_rect.setRect(0,0,31,31);
    backgound_rect.setRect(0,0,450,800);
    heart_rect.setRect(0,0,84,20);
    message_rect.setRect(0,0,5,42);

    srand(time(NULL));

    space=false;
    right=false;
    left=false;
    direction=0;
    start_count=0;
    rest_count=60;

    start=false;

    Tm=new QTimer(parent);
    connect(Tm,SIGNAL(timeout()),this,SLOT(timer()));
    Tm->start(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter backgound_painter(this);
    backgound_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    backgound_painter.setPen(QPen(Qt::transparent));
    backgound_painter.drawPixmap(QPointF(0,0),backgound,backgound_rect);

    QPainter heart_painter(this);
    heart_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    heart_painter.setPen(QPen(Qt::transparent));
    heart_painter.drawPixmap(QPointF(0,770),heart,heart_rect);

    QPainter bar_painter(this);
    bar_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    bar_painter.setPen(QPen(Qt::transparent));
    bar_painter.drawPixmap(QPointF(bar_mv,700),bar,bar_rect);

    QPainter ball_painter(this);
    ball_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    ball_painter.setPen(QPen(Qt::transparent));

    ball_painter.translate(myball->ball_x,myball->ball_y);
    ball_painter.rotate(myball->deg);
    ball_painter.drawPixmap(QPointF(-12,-12),myball->ball,myball->rot_rect);

    QPainter brick_painter(this);
    brick_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    brick_painter.setPen(QPen(Qt::transparent));
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<10; j++)
        {
            mybrick[(10*i)+j]->brick_x=(j*45);
            mybrick[(10*i)+j]->brick_y=(i*22);
            brick_painter.drawPixmap(QPointF(mybrick[(10*i)+j]->brick_x,mybrick[(10*i)+j]->brick_y),mybrick[(10*i)+j]->bricks,mybrick[(10*i)+j]->bricks_rect);
        }

    }

    QPainter item_painter(this);
    item_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    item_painter.setPen(QPen(Qt::transparent));
    item_painter.drawPixmap(QPointF(myitem->item_x,myitem->item_y),myitem->item,myitem->item_rect);

    QPainter message_painter(this);
    message_painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    message_painter.setPen(QPen(Qt::transparent));
    message_painter.drawPixmap(QPointF(81,400),message,message_rect);
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Space)
    {
        space=true;
        if(start_count==0)
        {
            start_count=1;
            start=true;
        }
    }
    else if(e->key()==Qt::Key_Right)
    {
        right=true;
        direction=1;
    }
    else if(e->key()==Qt::Key_Left)
    {
        left=true;
        direction=-1;
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat()==false)
    {
        if(e->key()==Qt::Key_Space)
        {
            space=false;
        }
        else if(e->key()==Qt::Key_Right)
        {
            right=false;
            direction=0;
        }
        else if(e->key()==Qt::Key_Left)
        {
            left=false;
            direction=0;
        }
    }
}
void MainWindow::timer()
{
    if(start==false && start_count==0)//Setting
    {
        myball->ball_x=bar_mv+50;
        myball->ball_y=12+670;
        if(right==true || left==true)
        {
            movement(direction);
        }
    }
    else if(start==true && start_count==1)//Start
    {
        if(right==true || left==true)
        {
            movement(direction);
        }
        myball->move(45);
        if(myball->ball_x>=450-12)
        {
            start_count=2;
        }
    }
    else if(start==true && start_count==2)//InGame
    {
//wall_collide
        if(right==true || left==true)
        {
            movement(direction);
        }
        myball->move(myball->deg);

        if(myball->ball_x>=438)
        {
            if(myball->deg<90)
            {
                myball->deg+=90;
            }
            else if(myball->deg>=270 && myball->deg<360)
            {
                myball->deg-=90;
            }
        }
        else if(myball->ball_x<=12)
        {
            if(myball->deg>=180 && myball->deg<270)
            {
                myball->deg+=90;
            }
            else if(myball->deg>=90 && myball->deg<180)
            {
                myball->deg-=90;
            }
        }
        else if(myball->ball_y<=12)
        {
            if(myball->deg>=90 && myball->deg<180)
            {
                myball->deg+=90;
            }
            else if(myball->deg<90)
            {
                myball->deg+=270;
            }
        }
        else if(myball->ball_x>=bar_mv+10 && myball->ball_x<=bar_mv+(50*bar_select)-10 && myball->ball_y>=690 && myball->ball_y<=695)//bar
        {
            if(myball->deg>=180 && myball->deg<270)
            {
                myball->deg-=90;
            }
            else if(myball->deg>=270 && myball->deg<360)
            {
                myball->deg-=270;
            }
        }
        else if(myball->ball_y>750)
        {
            HP--;
            heart_rect.setRect(0,0,84-(28*(3-HP)),20);
            myitem->item_count=0;
            myitem->whatItem=5;
            myball->speed=2;
            Tm->start(5);
            direction*=1;
            bar_select=2;
            bar_rect.setRect((bar_select-1)*50,0,bar_select*50,27);
            start=false;
            start_count=0;
        }
        if(HP==-1)
        {
          Tm->stop();
        }
        if(HP==0)
        {
            message_rect.setRect(5,0,277,42);
            HP=-1;
        }
//brick_collide
        for(int i=0; i<60; i++)
        {
            if(mybrick[i]->brick_show==0)
            {
                if(mybrick[i]->brick_y-12<myball->ball_y && mybrick[i]->brick_y+34>myball->ball_y)
                {
                    if(myball->ball_x+12==mybrick[i]->brick_x)//left wall
                    {
                        if(myball->deg<90)
                        {
                            myball->deg+=90;
                        }
                        else if(myball->deg>=270 && myball->deg<360)
                        {
                            myball->deg-=90;
                        }
                        mybrick[i]->brick_show=1;
                        mybrick[i]->bricks_rect.setRect(mybrick[i]->brick_show*45,0,45,22);
                        rest_count--;
                    }
                    else if(myball->ball_x-12==mybrick[i]->brick_x+45)//right wall
                    {
                        if(myball->deg>=180 && myball->deg<270)
                        {
                            myball->deg+=90;
                        }
                        else if(myball->deg>=90 && myball->deg<180)
                        {
                            myball->deg-=90;
                        }
                        mybrick[i]->brick_show=1;
                        mybrick[i]->bricks_rect.setRect(mybrick[i]->brick_show*45,0,45,22);
                        rest_count--;
                    }
                }
                else if(mybrick[i]->brick_x-12<myball->ball_x && mybrick[i]->brick_x+57>myball->ball_x)
                {
                    if(myball->ball_y-12==mybrick[i]->brick_y+22)//down wall
                    {
                        if(myball->deg>=90 && myball->deg<180)
                        {
                            myball->deg+=90;
                        }
                        else if(myball->deg<90)
                        {
                            myball->deg+=270;
                        }
                        mybrick[i]->brick_show=1;
                        mybrick[i]->bricks_rect.setRect(mybrick[i]->brick_show*45,0,45,22);
                        rest_count--;
                    }
                    else if(myball->ball_y+12==mybrick[i]->brick_y)//up wall
                    {
                        if(myball->deg>=180 && myball->deg<270)
                        {
                            myball->deg+=90;
                        }
                        else if(myball->deg>=90 && myball->deg<180)
                        {
                            myball->deg-=90;
                        }
                        mybrick[i]->brick_show=1;
                        mybrick[i]->bricks_rect.setRect(mybrick[i]->brick_show*45,0,45,22);
                        rest_count--;
                    }
                }
            }
        }
        if(rest_count==-1)
        {
            Tm->stop();
        }
        else if(rest_count==0)
        {
            start=false;
            start_count=0;
            rest_count=-1;
            message_rect.setRect(282,0,297,42);
        }
//item
        static int timer_count=0;
        if(myitem->item_check==0)
        {
            timer_count++;
            if(timer_count==2000)
            {
                myitem->item_select=rand()%6;
                myitem->item_x=rand()%420;
                myitem->item_rect.setRect(31*myitem->item_select,0,31,31);
                myitem->item_check=1;
            }
        }
        else if(myitem->item_check==1)
        {
            myitem->item_y+=2;
            if(myitem->item_y>=750)
            {
                myitem->item_check=0;
                timer_count=0;
                myitem->item_y=-40;
            }
            else if(myitem->item_x>=bar_mv+10 && myitem->item_x<=bar_mv+(50*bar_select)-10 && myitem->item_y>=690 && myitem->item_y<=695)
            {
                myitem->whatItem=myitem->item_select;
                myitem->item_check=0;
                timer_count=0;
                myitem->item_y=-40;
            }
        }
        if(myitem->whatItem !=5)//0:long_bar 1:short_bar 2:speed_up 3:speed_down 4:reverse
        {
            myitem->item_count++;
            if(myitem->item_count==1000)
            {
                myitem->item_count=0;
                myitem->whatItem=5;
                myball->speed=2;
                Tm->start(5);
                direction*=1;
                bar_select=2;
                bar_rect.setRect((bar_select-1)*50,0,bar_select*50,27);

            }
            if(myitem->whatItem==0)
            {
                bar_select=3;
                bar_rect.setRect((bar_select)*50,0,bar_select*50,27);
            }
            else if(myitem->whatItem==1)
            {
                bar_select=1;
                bar_rect.setRect((bar_select-1)*50,0,bar_select*50,27);
            }
            else if(myitem->whatItem==2)
            {
                myball->speed=2;
                Tm->start(3);
            }
            else if(myitem->whatItem==3)
            {
                myball->speed=2;
                Tm->start(7);
            }
            else if(myitem->whatItem==4)
            {
                if(direction==1)
                {
                    bar_mv-=4;
                }
                else if(direction==-1)
                {
                    bar_mv+=4;
                }
            }
        }
//        qDebug()<<myitem->whatItem;
    }
    update();
}
