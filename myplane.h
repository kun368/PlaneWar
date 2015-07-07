#ifndef MYPLANE_H
#define MYPLANE_H

#include "constants.h"
#include "gamecontroller.h"
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>

class GameController;

class MyPlane : public QGraphicsItem
{
public:
    MyPlane(GameController &controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
private:
    GameController &controller;
};

#endif // MYPLANE_H
