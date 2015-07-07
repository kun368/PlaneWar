#include "myview.h"
#include "myplane.h"
#include <QDebug>
#include <QWidget>
#include <QPixmap>

MyView::MyView(QWidget *parent)
{
    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(510, 610);  //设置窗口
    setMaximumSize(510, 610);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 500, 600);
    scene->setBackgroundBrush(QBrush(Qt::gray)); //设置背景
    setScene(scene);

    game = new GameController(scene, this);
}

