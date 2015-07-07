#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "myplane.h"
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QGraphicsScene *scene, QObject *parent = 0);
    ~GameController();
public slots:
    void resume();
    void pause();
    void gameOver();
    void addEnemy();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QTimer timer, timerApperEnemy;
    QGraphicsScene *scene;
    MyPlane *plane;
};

#endif // GAMECONTROLLER_H
