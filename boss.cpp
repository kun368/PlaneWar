#include "boss.h"
#include "gamecontroller.h"

#include <QPainter>
#include <QDebug>


Boss::Boss(GameController &controller):
    controller(controller),
    posX(qrand() % viewWidth),
    dirl(true),
    fullLife(30 * difficulty),
    life(30 * difficulty)
{
    setData(GD_type, GO_Boss);
    pixMap.load(":/images/Boss.png");
    gradient = new QLinearGradient(QPoint(-50, -50), QPoint(50, 50));
    gradient->setColorAt(0, Qt::red);
    gradient->setColorAt(0.2, Qt::yellow);
    gradient->setColorAt(0.7, Qt::blue);
    gradient->setColorAt(1, Qt::green);
}

QRectF Boss::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2 - 10, w, h + 10);
}

void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->setBrush(*gradient);
        painter->drawRect(-w/2, -h/2 - 10, w * life / fullLife, 8);
        painter->restore();
    }
}

void Boss::advance(int phace)
{
    if(!phace) return;

    if(dirl) posX -= 5;
    else posX += 5;
    if(posX >= viewWidth || posX <= 0)
        dirl = !dirl;
    setPos(posX, 150);

    int r = qrand() % 300;
    if(++cnt == (300/difficulty)){
        controller.shootBossBall(QPointF(posX, 210));
        cnt = 0;
    }
    handleCollisions();
}

void Boss::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        auto t = item->data(GD_type);
        if(t == GO_Bullet || t == GO_WingBullet) {
            controller.ariseCollision(pos());
            controller.removeItem(item);
            if(--life <= 0) {
                controller.updateText(2000 + qrand() % 100);
                controller.removeItem(this);
                QTimer::singleShot(70000, &controller, SLOT(addBoss()));
            }
            return;
        }
    }
}

void Boss::changeLife(const int d)
{
    life += d;
}
