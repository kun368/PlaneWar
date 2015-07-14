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
    void changeLife(const int d);
private:
    QPixmap pixMap;
    QLinearGradient *gradient;
    GameController &controller;
    int posX, dirl, life, cnt, fullLife;
};

#endif // BOSS_H
