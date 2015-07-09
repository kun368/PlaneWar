#ifndef FLOWBACK_H
#define FLOWBACK_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainterPath>

class GameController;

class FlowBack : public QGraphicsItem
{
public:
    FlowBack(GameController & controller);
    ~FlowBack();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    int cur, up;
    QPixmap pixMap;
    GameController &controller;
};

#endif // FLOWBACK_H
