#include "enemy.h"
#include "gamecontroller.h"
#include <QPainter>

Enemy::Enemy(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Enemy);
    pixMap.load(":/images/Enemy.png");
}

QRectF Enemy::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Enemy::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() + 4);

    int r = qrand() % 700;
    if(r < controller.getRank()) controller.shootBall(pos());

    if(pos().y() > 600) controller.removeItem(this);

    handleCollisions();
}

void Enemy::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GD_type) == GO_Bullet) {
            controller.updateText(100 + qrand() % 50);
            controller.removeItem(this);
            controller.ariseCollision(pos());
            return;
        }
    }
}
