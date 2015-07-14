#ifndef WINGPLANE_H
#define WINGPLANE_H
#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;


class WingPlane : public QGraphicsItem
{
public:
    WingPlane(GameController &controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    int cnt;
    QPixmap pixMap;
    GameController &controller;
};

#endif // WINGPLANE_H
