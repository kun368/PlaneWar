#include "gamecontroller.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include "collision.h"
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QMessageBox>
#include <QSound>

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
      timer.start(1000/32);
      timerApperEnemy.start(2000);
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

void GameController::updateText(int dscore)
{
    text->setZValue(1);
    score += dscore;
    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    text->setDefaultTextColor(Qt::yellow);
    text->setFont(font);
    text->setPlainText(tr("得分:%1  等级:%2  生命:%3").arg(score).arg(getRank()).arg(life));
}

int GameController::getRank()
{
    return score/2000.0 + 1;
}

void GameController::resume()
{
    plane = new MyPlane(*this);
    plane->setFocus();
    plane->setPos(240, 400);
    scene->addItem(plane);

    life = loadmode ? 2147483647 : 10;
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
    text->setZValue(1);
}

void GameController::ariseCollision(QPointF pos)
{
    Collision *tempCollision = new Collision();
    tempCollision->setPos(pos);
    scene->addItem(tempCollision);
    collis.push_back(tempCollision);

    QSound *sound = new QSound(":/musics/Collision.wav");
    sound->setLoops(1);
    sound->play();

    QTimer::singleShot(200, this, SLOT(disappearCollision()));
}

void GameController::disappearCollision()
{
    if(!collis.isEmpty()){
        Collision* tempCollision = collis.takeFirst();
        scene->removeItem(tempCollision);
    }
}

void GameController::shootBullet(QPointF pos)
{
    Bullet *tempBullet = new Bullet(*this);
    tempBullet->setPos(pos);
    scene->addItem(tempBullet);

    QSound *sound = new QSound(":/musics/Shoot.wav");
    sound->setLoops(1);
    sound->play();

    text->setZValue(1);
}

void GameController::shootBall(QPointF pos)
{
    Ball *tempBall = new Ball(*this);
    tempBall->setPos(pos);
    scene->addItem(tempBall);
    text->setZValue(1);
}

void GameController::updateLife()
{
    --life;
    updateText(0);
    if(life <= 0)
        gameOver();
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
            int len = getRank() * 10 + 1;
            int n = getRank() / 3 + 1;
            for(int i = 0; i < n; ++i)
                shootBullet(QPointF(p.x()+qrand()%len-len/2, p.y()-15));
            break;
        }
    }
    return QObject::eventFilter(obj, event);
}

