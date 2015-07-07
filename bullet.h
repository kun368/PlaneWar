#ifndef BULLET_H
#define BULLET_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Bullet : public QGraphicsItem
{
public:
    Bullet();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
};

#endif // BULLET_H
