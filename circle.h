#ifndef CIRCLE_H
#define CIRCLE_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPixmap>

class GameController;

class Circle : public QGraphicsItem
{
public:
    Circle(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    QPainterPath shape();
    void handleCollisions();
private:
    QPainterPath *path;
    QPixmap pixMap;
    GameController &controller;
    int cur;
};

#endif // CIRCLE_H
