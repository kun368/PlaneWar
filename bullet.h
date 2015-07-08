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
private:
    QPixmap pixMap;
    GameController &controller;
};

#endif // BULLET_H
