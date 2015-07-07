#include "myview.h"
#include "myplane.h"
#include <QDebug>
#include <QWidget>
#include <QPixmap>

MyView::MyView(QWidget *parent)
{
    icon = new QIcon(":/images/Icon.png");

    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(510, 610);  //设置窗口
    setMaximumSize(510, 610);
    setWindowTitle(tr("飞机大战"));
    setWindowIcon(*icon);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 500, 600);
    scene->setBackgroundBrush(QPixmap(":/images/background.jpg")); //设置背景
    setScene(scene);

    game = new GameController(scene, this);
    connect(game, SIGNAL(exitApp()), this, SLOT(close()));
}

