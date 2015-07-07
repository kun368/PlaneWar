#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>

class Ball : public QGraphicsItem
{
public:
    Ball();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
};

#endif // BALL_H
