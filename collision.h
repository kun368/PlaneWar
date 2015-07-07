#ifndef COLLISION_H
#define COLLISION_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Collision : public QGraphicsItem
{
public:
    Collision();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pixMap;
};

#endif // COLLISION_H
