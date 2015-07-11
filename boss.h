#ifndef BOSS_H
#define BOSS_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QLinearGradient>

class GameController;

class Boss : public QGraphicsItem
{
public:
    Boss(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
private:
    int posX, dirl, life;
    QPixmap pixMap;
    QLinearGradient *gradient;
    GameController &controller;
};

#endif // BOSS_H
