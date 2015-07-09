#ifndef CIRCLE_H
#define CIRCLE_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class Circle : public QGraphicsItem
{
public:
    Circle(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
private:
    int cur;
    QPixmap pixMap;
    GameController &controller;
};

#endif // CIRCLE_H
