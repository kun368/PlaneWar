#include "myview.h"
#include "myplane.h"

MyView::MyView(QWidget *parent)
{
    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(510, 610);  //设置窗口
    setMaximumSize(510, 610);
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 500, 600);
    scene->setBackgroundBrush(QBrush(Qt::gray)); //设置背景
    setScene(scene);
    // scene->addEllipse(10, 10, 300, 300);

    //初始化我的战机
    plane = new MyPlane;
    plane->setFocus();
    scene->addItem(plane);
}

