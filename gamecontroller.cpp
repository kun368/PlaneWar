#include "gamecontroller.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include "boss.h"
#include "collision.h"
#include "flowback.h"
#include "lifeadder.h"
#include "circle.h"
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QMessageBox>
#include <QSound>

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
    timer.start(1000/33);
    timerApperEnemy.start(1500);
    timerApperLifeAdder.start(10000);
    timerAddBoss.start(40000);
    scene->installEventFilter(this);
    startGame();
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
    if(!loadmode || dscore > 0)   //上帝模式不减分数
        score += dscore;
    if(score < 0) gameOver();
    text->setPlainText(tr("得分:%1  等级:%2  生命:%3").arg(score).arg(getRank()).arg(life));
}

int GameController::getRank()
{
    if(score <= 0) return 1;
    return score/2000.0 + 1;
}
void GameController::clearAllEnemy()
{
    updateText(-800);   //一个清屏大招消耗800积分
    QList<QGraphicsItem *> items = scene->items(QRectF(0, 0, viewWidth, viewHeight));
    foreach (QGraphicsItem *it, items) {
        if(it->data(GD_type) == GO_Ball || it->data(GD_type) == GO_Enemy || it->data(GD_type) == GO_Boss) {
            removeItem(it);
            ariseCollision(it->pos());
        }
    }
}

void GameController::startGame()
{
    back = new FlowBack(*this);   //添加流动背景
    scene->addItem(back);

    plane = new MyPlane(*this);      //唯一我的飞机
    plane->setFocus();
    plane->setPos(viewWidth/2, 400);
    scene->addItem(plane);

    circle = new Circle(*this);    //初始化光环
    circle->setParentItem(plane);
    QTimer::singleShot(15000, this, SLOT(disappearCircle()));

    life = loadmode ? 999999 : 5;    //初始化显示分数
    score = 0;
    text = new QGraphicsTextItem();
    font = new QFont();
    font->setBold(true);
    font->setPixelSize(22);
    text->setDefaultTextColor(Qt::yellow);
    text->setFont(*font);
    text->setPos(10, 10);
    scene->addItem(text);
    updateText(1000);

    connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
    connect(&timerApperLifeAdder, SIGNAL(timeout()), this, SLOT(addLifeAdder()));
    connect(&timerAddBoss, SIGNAL(timeout()), this, SLOT(addBoss()));
}

void GameController::gameOver()
{
    disconnect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    disconnect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
    disconnect(&timerApperLifeAdder, SIGNAL(timeout()), this, SLOT(addLifeAdder()));
    disconnect(&timerAddBoss, SIGNAL(timeout()), this, SLOT(addBoss()));
    QMessageBox::question(0, tr("提示"), tr("你已经挂了,得分是：%1").arg(score), QMessageBox::Yes);
    emit exitApp();
}

void GameController::addEnemy()
{
    int x = qrand() % viewWidth, y = 1;
    Enemy *tempEnemy = new Enemy(*this);
    tempEnemy->setPos(x, y);
    scene->addItem(tempEnemy);
    shootBall(QPointF(x, y + 30));
    text->setZValue(1);
}

void GameController::addLifeAdder()
{
    int x = qrand() % viewWidth, y = 1;
    LifeAdder *temp = new LifeAdder(*this);
    temp->setPos(x, y);
    scene->addItem(temp);
    text->setZValue(1);
}

void GameController::addBoss()
{
    boss = new Boss(*this);
    scene->addItem(boss);
    QTimer::singleShot(12000, this, SLOT(disappearBoss()));
}

void GameController::disappearBoss()
{
    scene->removeItem(boss);
}

void GameController::addCircle()
{
    updateText(-1000);
    circle->setParentItem(plane);
    scene->addItem(circle);
    QTimer::singleShot(15000, this, SLOT(disappearCircle()));
}

void GameController::disappearCircle()
{
    scene->removeItem(circle);
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
    if(!collis.isEmpty()) {
        Collision* tempCollision = collis.takeFirst();
        scene->removeItem(tempCollision);
    }
}

void GameController::shootBullet(QPointF pos, int speed)
{
    Bullet *tempBullet = new Bullet(*this);
    tempBullet->setPos(pos);
    tempBullet->setSpeed(speed);
    scene->addItem(tempBullet);

    QSound *sound = new QSound(":/musics/Shoot.wav");
    sound->setLoops(1);
    sound->play();

    updateText(-30);
}

void GameController::shootBall(QPointF pos)
{
    Ball *tempBall = new Ball(*this);
    tempBall->setPos(pos);
    scene->addItem(tempBall);
    text->setZValue(1);
}

void GameController::shootBossBall(QPointF pos)
{
    BossBall *tempBall = new BossBall(*this);
    tempBall->setPos(pos);
    scene->addItem(tempBall);
    text->setZValue(1);
}

void GameController::updateLife(int dlife)
{
    life += dlife;
    updateText(0);
    if(life <= 0) gameOver();
}

bool GameController::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    if(event->type() == QEvent::KeyRelease) {
        handleKeyReleased((QKeyEvent *)event);
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    if(!event->isAutoRepeat()) {
        int key = event->key();
        if(key == Qt::Key_M) addCircle();
        if(key == Qt::Key_B) clearAllEnemy();
        if(key == Qt::Key_D) plane->fire(0);
        if(key == Qt::Key_Left) plane->setSpeedX(-10);
        if(key == Qt::Key_Right) plane->setSpeedX(10);
        if(key == Qt::Key_Up) plane->setSpeedY(-10);
        if(key == Qt::Key_Down) plane->setSpeedY(10);
        if(key == Qt::Key_Space) plane->setFireStatus(true);
    }
}

void GameController::handleKeyReleased(QKeyEvent *event)
{
    if(!event->isAutoRepeat()) {
        int key = event->key();
        if(key == Qt::Key_Left) plane->setSpeedX(0);
        if(key == Qt::Key_Right) plane->setSpeedX(0);
        if(key == Qt::Key_Up) plane->setSpeedY(0);
        if(key == Qt::Key_Down) plane->setSpeedY(0);
        if(key == Qt::Key_Space) plane->setFireStatus(false);
    }
}
