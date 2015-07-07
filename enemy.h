#ifndef ENEMY_H
#define ENEMY_H

#include "myplane.h"
#include <QObject>

class Enemy : public MyPlane
{
public:
    Enemy();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
};

#endif // ENEMY_H
