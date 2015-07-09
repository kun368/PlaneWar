#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "constants.h"
#include "collision.h"
#include "myplane.h"
#include "circle.h"
#include "flowback.h"
#include <QObject>
#include <QFont>
#include <QRectF>
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
    QPointF getPlanePos();
signals:
    void exitApp();
public slots:
    void clearAllEnemy();
    void startGame();
    void gameOver();
    void addEnemy();
    void addLifeAdder();
    void addCircle();
    void disappearCircle();
    void ariseCollision(QPointF pos);
    void disappearCollision();
    void shootBullet(QPointF pos, int speed);
    void shootBall(QPointF pos);
    void updateLife(int dlife);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyReleased(QKeyEvent *event);
private:
    int score, life;
    bool gameIsRun;
    QList<Collision*> collis;
    QTimer timer, timerApperEnemy, timerApperLifeAdder;
    FlowBack *back;
    QGraphicsScene *scene;
    MyPlane *plane;
    Circle *circle;
    QFont *font;
    QGraphicsTextItem *text;
};

#endif // GAMECONTROLLER_H
