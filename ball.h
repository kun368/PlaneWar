#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class GameController;

class Ball : public QGraphicsItem
{
public:
    Ball(GameController & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    int dirx;
    QPixmap pixMap;
    GameController &controller;
};

#endif // BALL_H
