#ifndef BOSSBALL_H
#define BOSSBALL_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;


class BossBall : public QGraphicsItem
{
public:
    BossBall(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
    GameController &controller;
};

#endif // BOSSBALL_H
