#include "gamecontroller.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include "boss.h"
#include "collision.h"
#include "flowback.h"
#include "lifeadder.h"
#include "circle.h"
#include "rank.h"
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
    timerApperEnemy.start(1500/difficulty);
    timerApperLifeAdder.start(5000*difficulty);

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

QPointF GameController::getPlantPos()
{
    return plane->pos();
}

int GameController::getRank()
{
    if(score <= 0) return 1;
    return score/2000.0 + 1;
}

int GameController::getMyPlaneLife()
{
    return life;
}

void GameController::clearAllEnemy()
{
    updateText(-200);   //清屏大招消耗积分
    QList<QGraphicsItem *> items = scene->items(QRectF(0, 0, viewWidth, viewHeight));
    foreach (QGraphicsItem *it, items) {
        auto t = it->data(GD_type);
        if(t == GO_Ball || t == GO_Enemy || t == GO_BossBall) {
            removeItem(it);
            ariseCollision(it->pos());
        }
        if(t == GO_Boss) {
            Boss * iter = dynamic_cast<Boss *>(it);
            iter->changeLife(-5);
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


    wing1 = new WingPlane(*this); wing2 = new WingPlane(*this);  //初始化僚机
    wing1->setParentItem(plane); wing2->setParentItem(plane);
    wing1->setPos(-70, 70); wing2->setPos(70, 70);
    QTimer::singleShot(6000, this, SLOT(disappearWingPlane()));

    font = new QFont();    //初始化字体
    font->setBold(true);
    font->setPixelSize(20);

    life = myPlaneFullLife;    //初始化显示分数生命
    score = 0;
    text = new QGraphicsTextItem();
    text->setDefaultTextColor(Qt::yellow);
    text->setFont(*font);
    text->setPos(10, 10);
    scene->addItem(text);
    updateText(1000);

    nightText = new QGraphicsTextItem();      //初始化黑夜模式字体
    nightText->setFont(*font);
    nightText->setDefaultTextColor(Qt::yellow);
    nightText->setPos(10, 50);
    nightText->setPlainText("正常飞行中...");
    scene->addItem(nightText);

    //初始化游戏提示
    tip = new Tip(*this);
    scene->addItem(tip);


    QTimer::singleShot(20000, this, SLOT(addBoss())); //一定时间后出现第一个BOSS
    QTimer::singleShot(30000, this, SLOT(gotoNight()));

    connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));      //各种计时器
    connect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
    connect(&timerApperLifeAdder, SIGNAL(timeout()), this, SLOT(addLifeAdder()));
}

void GameController::gameOver()
{
    disconnect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    disconnect(&timerApperEnemy, SIGNAL(timeout()), this, SLOT(addEnemy()));
    disconnect(&timerApperLifeAdder, SIGNAL(timeout()), this, SLOT(addLifeAdder()));
    QMessageBox::question(0, tr("提示"), tr("你已经挂了,得分是：%1").arg(score), QMessageBox::Yes);
    // 如果不是上帝模式，显示排行榜
    if(!loadmode) {
        Rank rank;
        Record cur; cur.name = playerName;
        cur.score = QString::number(score);
        cur.time = QDateTime::currentDateTime().toString("yyyy.MM.dd..hh:mm.ap");
        rank.add(cur);
        rank.show();
    }
    emit exitApp();
}

void GameController::addEnemy()
{
    int x = qrand() % 300 - 150 + viewWidth/2, y = 1;
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

void GameController::addLifeAdder(QPointF pos)
{
    LifeAdder *temp = new LifeAdder(*this);
    temp->setPos(pos);
    scene->addItem(temp);
    text->setZValue(1);
}

void GameController::addBoss()
{
    boss = new Boss(*this);
    scene->addItem(boss);
}

void GameController::addCircle()
{
    updateText(-200);
    circle->setParentItem(plane);
    scene->addItem(circle);
    QTimer::singleShot(15000, this, SLOT(disappearCircle()));
}

void GameController::addWingPlane()
{
    // updateText(-300);
    scene->removeItem(wing1); scene->removeItem(wing2);    //删除旧的僚机
    wing1 = new WingPlane(*this); wing2 = new WingPlane(*this);
    wing1->setParentItem(plane); wing2->setParentItem(plane);
    wing1->setPos(-70, 70); wing2->setPos(70, 70);
    QTimer::singleShot(15000, this, SLOT(disappearWingPlane()));
}

void GameController::disappearCircle()
{
    scene->removeItem(circle);
}

void GameController::disappearWingPlane()
{
    scene->removeItem(wing1);
    scene->removeItem(wing2);
}

void GameController::ariseCollision(QPointF pos)
{
    Collision *tempCollision = new Collision();
    tempCollision->setPos(pos);
    scene->addItem(tempCollision);
    collis.push_back(tempCollision);

    QSound *sound = new QSound("://musics/Collision.wav");
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

    QSound *sound = new QSound("://musics/Shoot.wav");
    sound->setLoops(1);
    sound->play();

    updateText(-10);
}

void GameController::shootBall(QPointF pos)
{
    Ball *tempBall = new Ball(*this);
    tempBall->setPos(pos);
    tempBall->setDir();
    scene->addItem(tempBall);
    text->setZValue(1);
}

void GameController::shootBossBall(QPointF pos, qreal angle)
{
    BossBall *tempBall = new BossBall(*this);
    tempBall->setPos(pos);
    tempBall->setAngle(angle);
    scene->addItem(tempBall);
    text->setZValue(1);
}

void GameController::shootWingBullet(QPointF pos)
{
    WingBullet *temp = new WingBullet(*this);
    temp->setPos(pos);
    scene->addItem(temp);
    text->setZValue(1);
}

void GameController::updateLife(int dlife)
{
    life += dlife;
    updateText(0);
    if(life <= 0) gameOver();
}

void GameController::gotoNight()
{
    nightText->setPlainText("黑夜飞行中...");
    scene->setForegroundBrush(QColor(0, 0, 0, 127));
    QTimer::singleShot(30000, this, SLOT(outNight()));
}

void GameController::outNight()
{
    nightText->setPlainText("正常飞行中...");
    scene->setForegroundBrush(QColor(0, 0, 0, 0));
    QTimer::singleShot(30000, this, SLOT(gotoNight()));
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
        if(key == Qt::Key_A) addWingPlane();
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
