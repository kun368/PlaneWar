#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "myplane.h"
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

class MyPlane;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QGraphicsScene *scene, QObject *parent = 0);
    ~GameController();
signals:
    void exitApp();
public slots:
    void resume();
    void pause();
    void gameOver();
    void addEnemy();
    void shootBullet(QPointF pos);
    void shootBall(QPointF pos);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    bool gameIsRun;
    QTimer timer, timerApperEnemy;
    QGraphicsScene *scene;
    MyPlane *plane;
};

#endif // GAMECONTROLLER_H
