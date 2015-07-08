#ifndef LIFEADDER_H
#define LIFEADDER_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
class GameController;

class LifeAdder : public QGraphicsItem
{
public:
    LifeAdder(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
    GameController &controller;
};

#endif // LIFEADDER_H
