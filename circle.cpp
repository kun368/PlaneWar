#include "circle.h"
#include "gamecontroller.h"
#include <QPainter>
#include <QDebug>



Circle::Circle(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Circle);
    pixMap.load(":/images/Circle.png");
    qDebug() << "111";
}

QRectF Circle::boundingRect() const
{
    int w = pixMap.width() * 0.7, h = pixMap.height() * 0.7;
    return QRectF(-w/2, -h/2, w, h);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        painter->scale(0.7, 0.7);
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Circle::advance(int phace)
{
    if(!phace) return;
    setPos(controller.getPlanePos());
    handleCollisions();
}

void Circle::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GD_type) == GO_Ball || item->data(GD_type) == GO_Enemy) {
            controller.removeItem(item);
            controller.ariseCollision(item->pos());
            return;
        }
    }
}
