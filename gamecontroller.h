#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "myplane.h"
#include "collision.h"
#include <QObject>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsTextItem>

class MyPlane;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QGraphicsScene *scene, QObject *parent = 0);
    ~GameController();
    void removeItem(QGraphicsItem *item);
    void updateText(int dscore);
    int getRank();
signals:
    void exitApp();
public slots:
    void resume();
    void pause();
    void gameOver();
    void addEnemy();
    void ariseCollision(QPointF pos);
    void disappearCollision();
    void shootBullet(QPointF pos);
    void shootBall(QPointF pos);
    void updateLife();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    int score, life;
    bool gameIsRun;
    QList<Collision*> collis;
    QTimer timer, timerApperEnemy;
    QGraphicsScene *scene;
    MyPlane *plane;
    QGraphicsTextItem *text;
};

#endif // GAMECONTROLLER_H
