#ifndef TIP_H
#define TIP_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
class GameController;


class Tip : public QGraphicsItem
{
public:
    Tip(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pixMap;
    GameController &controller;
};

#endif // TIP_H
