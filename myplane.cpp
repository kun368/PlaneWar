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
    pixMap.load(":/images/MyPlane.png");
    speedX = speedY = isFireing = 0;
}

QRectF MyPlane::boundingRect() const
{
    qreal w = pixMap.width(), h = pixMap.height();
    w *= getScale(); h *= getScale();
    return QRectF(-w/2, -h/2, w, h);
}

void MyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        painter->scale(getScale(), getScale());
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
        if(isFireing % 5  == 1) fire(8);
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
    int len = controller.getRank() * 10 + 1;
    int n = controller.getRank() / 3 + 1;
    while(n--)
        controller.shootBullet(QPointF(x + qrand() % len - len/2, y - 15), speed);
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

qreal MyPlane::getScale() const
{
    qreal s = controller.getRank();
    return qMin(s/5.0 + 0.7, 2.0);
}

