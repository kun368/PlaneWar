#ifndef MYPLANE_H
#define MYPLANE_H

#include "constants.h"
#include "gamecontroller.h"
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QPicture>
#include <QPixmap>
#include <QLinearGradient>

class GameController;

class MyPlane : public QGraphicsItem
{
public:
    MyPlane(GameController &controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
    void fire(int speed);
    void setSpeedX(int x);
    void setSpeedY(int y);
    void setFireStatus(bool can);
private:
    QLinearGradient *gradient;
    int speedX, speedY, isFireing;
    GameController &controller;
    QPixmap pixMap;
};

#endif // MYPLANE_H
