#ifndef BULLET_H
#define BULLET_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class Bullet : public QGraphicsItem
{
public:
    Bullet(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void setSpeed(int x);
private:
    int speed;
    QPixmap pixMap;
    GameController &controller;
};

#endif // BULLET_H
