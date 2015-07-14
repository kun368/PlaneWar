#ifndef WINGBULLET_H
#define WINGBULLET_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class WingBullet : public QGraphicsItem
{
public:
    WingBullet(GameController &controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
    GameController &controller;
};

#endif // WINGBULLET_H
