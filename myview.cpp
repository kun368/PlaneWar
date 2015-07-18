#include "myview.h"
#include "myplane.h"
#include "flowback.h"
#include <QDir>
#include <QDebug>
#include <QWidget>
#include <QPixmap>
#include <QDateTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>


MyView::MyView(QWidget *parent):
    QGraphicsView(parent)
{
    QMediaPlayer * player = new QMediaPlayer(this);     //背景音乐
    QMediaPlaylist * list = new QMediaPlaylist(this);
    list->addMedia(QUrl(QDir::currentPath() + "/a.mp3"));
    list->setCurrentIndex(0);
    list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(list);
    player->play();

    icon = new QIcon("://images/Icon.png");

    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(viewWidth + 10, viewHeight + 10);  //设置窗口
    setMaximumSize(viewWidth + 10, viewHeight + 10);
    if(loadmode) setWindowTitle(tr("飞机大战 [上帝模式]"));
    else setWindowTitle(tr("飞机大战"));
    setWindowIcon(*icon);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);

    game = new GameController(scene, this);
    connect(game, SIGNAL(exitApp()), this, SLOT(close()));
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        QPixmap pix(viewWidth, viewHeight);
        QPainter painter(&pix);
        render(&painter, QRect(0, 0, viewWidth, viewHeight), QRect(0, 0, viewWidth, viewHeight));
        QString fileName = QString("%1.png").arg(qrand());
        qDebug() << fileName;
        pix.save(fileName);
    }
    QGraphicsView::mousePressEvent(event);
}

