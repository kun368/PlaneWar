#include "gamecontroller.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
      timer.start(1000/32);
      timerApperEnemy.start(1000);
      scene->installEventFilter(this);
      resume();
}

GameController::~GameController()
{

}

void GameController::removeItem(QGraphicsItem *item)
{
    scene->removeItem(item);
}

void GameController::updateText(int x)
{
    text->setZValue(0);
    score += x;
    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    text->setDefaultTextColor(Qt::white);
    text->setFont(font);
    text->setPlainText(tr("得分:%1").arg(score));
}

void GameController::resume()
{
    plane = new MyPlane(*this);
    plane->setFocus();
    plane->setPos(240, 400);
    scene->addItem(plane);

    score = 0;
    text = new QGraphicsTextItem();
    text->setPos(10, 10);
    scene->addItem(text);
    updateText(1000);

    connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
}

void GameController::pause()
{
    scene->clear();
    disconnect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    disconnect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
}

void GameController::gameOver()
{
    pause();
    QString msg(tr("你已经挂了,得分是：%1\n是否重新开始游戏？").arg(score));
    int ret = QMessageBox::question(0, tr("提示"), msg, QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes) resume();
    else emit exitApp();
}

void GameController::addEnemy()
{
    int x = qrand() % 500, y = 1;
    Enemy *tempEnemy = new Enemy(*this);
    tempEnemy->setPos(x, y);
    scene->addItem(tempEnemy);
    shootBall(QPointF(x, y + 30));
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
    if(event->type() == QEvent::KeyPress) {
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
            QPointF p = plane->pos();
            shootBullet(QPointF(p.x(), p.y()-15));
            break;
        }
    }
    return QObject::eventFilter(obj, event);
}

