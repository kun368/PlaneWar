#include "gamecontroller.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include <QDebug>
#include <QMessageBox>

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
      timer.start(1000/32);
      timerApperEnemy.start(1000);
      //初始化我的战机（唯一）
      plane = new MyPlane(*this);
      plane->setFocus();
      plane->setPos(240, 400);
      scene->addItem(plane);
      addEnemy();
      //安装事件过滤器,在GameController中处理事件
      scene->installEventFilter(this);

      resume();
}

GameController::~GameController()
{

}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    disconnect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
}

void GameController::gameOver()
{
    pause();
    scene->clear();
    int ret = QMessageBox::question(0, tr("提示"), tr("你已经挂了~\n是否重新开始游戏？"), QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes) {
        plane = new MyPlane(*this);
        plane->setFocus();
        plane->setPos(240, 400);
        scene->addItem(plane);
        addEnemy();
        resume();
    }
    else emit exitApp();
}

void GameController::addEnemy()
{
    int x = qrand() % 500, y = qrand() % 300;
    Enemy *tempEnemy = new Enemy(*this);
    tempEnemy->setPos(x, y);
    scene->addItem(tempEnemy);
    shootBall(QPointF(x + 5, y + 10));
}

void GameController::shootBullet(QPointF pos)
{
    Bullet *tempBullet = new Bullet();
    tempBullet->setPos(pos);
    scene->addItem(tempBullet);
}

void GameController::shootBall(QPointF pos)
{
    Ball *tempBall = new Ball;
    tempBall->setPos(pos);
    scene->addItem(tempBall);
}

bool GameController::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *key = (QKeyEvent*)event;
        switch (key->key()) {
        case Qt::Key_Left:
            plane->moveLeft();
            break;
        case Qt::Key_Right:
            plane->moveRight();
            break;
        case Qt::Key_Up:
            plane->moveUp();
            break;
        case Qt::Key_Down:
            plane->moveDown();
            break;
        case Qt::Key_Space:
            shootBullet(plane->pos());
            break;
        }
    }
    return QObject::eventFilter(obj, event);
}

