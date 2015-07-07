#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Ball : public QGraphicsItem
{
public:
    Ball();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
};

#endif // BALL_H
