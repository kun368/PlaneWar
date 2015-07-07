#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class Enemy :public QGraphicsItem
{
public:
    Enemy(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
private:
    GameController &controller;
    QPixmap pixMap;
};

#endif // ENEMY_H
