#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include "bar.h"
#include "ball.h"
#include "brick.h"
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,Bar
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap backgound;
    QRectF backgound_rect;
    QPixmap heart;
    QRectF heart_rect;
    QPixmap message;
    QRectF message_rect;

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);

    bool space;
    bool right;
    bool left;
    bool start;
    int start_count;
    int rest_count;
    QTimer *Tm;
    Ball *myball;
    Brick *mybrick[60];
    Item *myitem;
private slots:
    void timer();
};
#endif // MAINWINDOW_H
