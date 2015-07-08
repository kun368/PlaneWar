#include "myview.h"
#include "myplane.h"
#include "flowback.h"
#include <QDebug>
#include <QWidget>
#include <QPixmap>


MyView::MyView(QWidget *parent)
{
    sound = new QSound(":/musics/TheDawn.wav");
    sound->setLoops(10);
    sound->play();

    icon = new QIcon(":/images/Icon.png");

    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(viewWidth + 10, viewHeight + 10);  //设置窗口
    setMaximumSize(viewWidth + 10, viewHeight + 10);
    setWindowTitle(tr("飞机大战"));
    setWindowIcon(*icon);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    // scene->setBackgroundBrush(QPixmap(":/images/background.jpg")); //设置背景
    setScene(scene);

    game = new GameController(scene, this);
    connect(game, SIGNAL(exitApp()), this, SLOT(close()));
}

