#include "enemy.h"
#include "gamecontroller.h"
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QString>

Enemy::Enemy(GameController &controller):
    controller(controller),
    speedY(7),
    speedX(qrand() % 7 - 3)
{
    setData(GD_type, GO_Enemy);
    QString str = QString(":/images/Enemy%1.png").arg(qrand()%5+1);
    pixMap.load(str);  //五种敌机图
    rad = -(atan(speedX*1.0/speedY) / 3.1415926) * 180.0;
}

QRectF Enemy::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        // qDebug() << speedX << " " << speedY << " " << rad;
        painter->rotate(rad);
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Enemy::advance(int phace)
{
    if(!phace) return;

    moveBy(speedX, speedY);
    if(!isInView(pos()))
        controller.removeItem(this);

    int r = qrand() % 600;
    if(r < controller.getRank())
        controller.shootBall(pos());

    handleCollisions();
}

void Enemy::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GD_type) == GO_Bullet) {
            controller.updateText(100 + qrand() % 20);
            controller.removeItem(this);
            controller.ariseCollision(pos());
            controller.removeItem(item);
            return;
        }
        if(item->data(GD_type) == GO_WingBullet) {
            controller.updateText(50 + qrand() % 20);
            controller.removeItem(this);
            controller.ariseCollision(pos());
            controller.removeItem(item);
            return;
        }
    }
}
