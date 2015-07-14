#include "myplane.h"
#include <QKeyEvent>
#include <QDebug>
#include <QtAlgorithms>
#include <QList>
#include <QDebug>
#include <QtAlgorithms>


MyPlane::MyPlane(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_MyPlane);
    pixMap.load(":/images/MyPlane2.png");
    speedX = speedY = isFireing = 0;
}

QRectF MyPlane::boundingRect() const
{
    qreal w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void MyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        qreal sc = qMin((1.0+controller.getRank()/10.0), 2.0);
        painter->scale(0.6 * sc, 0.6 * sc);
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void MyPlane::advance(int phace)
{
    if(!phace) return;
    // 设置战机位置，放置超出屏幕
    setPos(pos().x() + speedX, pos().y() + speedY);
    if(pos().x() < 0) setPos(0, pos().y());
    if(pos().x() > viewWidth) setPos(viewWidth, pos().y());
    if(pos().y() < 0) setPos(pos().x(), 0);
    if(pos().y() > viewHeight) setPos(pos().x(), viewHeight);

    if(isFireing) {
        if(isFireing % 7  == 1) fire(10);
        isFireing++;
    }
    handleCollisions();
}

void MyPlane::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GD_type) == GO_Ball) {
            controller.removeItem(item);
            controller.updateLife(-1);
            controller.ariseCollision(pos());
            return;
        }
        if(item->data(GD_type) == GO_BossBall) {
            controller.removeItem(item);
            controller.updateLife(-1);
            controller.ariseCollision(pos());
            return;
        }
        if(item->data(GD_type) == GO_Enemy) {
            controller.removeItem(item);
            controller.updateLife(-1);
            controller.ariseCollision(pos());
            return;
        }
        if(item->data(GD_type) == GO_LifeAdder) {
            controller.removeItem(item);
            controller.updateLife(1);
            return;
        }
    }
}

void MyPlane::fire(int speed)
{
    qreal x = pos().x(), y = pos().y();
    controller.shootBullet(QPointF(x, y - 20), speed);
}

void MyPlane::setSpeedX(int x)
{
    speedX = x;
}

void MyPlane::setSpeedY(int y)
{
    speedY = y;
}

void MyPlane::setFireStatus(bool can)
{
    if(isFireing == 0 && can) isFireing = 1;
    else if(isFireing > 0 && !can) isFireing = 0;
}

