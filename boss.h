#ifndef BOSS_H
#define BOSS_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class Boss : public QGraphicsItem
{
public:
    Boss(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    int posX, dirl;
    QPixmap pixMap;
    GameController &controller;
};

#endif // BOSS_H
