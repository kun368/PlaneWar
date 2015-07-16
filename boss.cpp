#include "boss.h"
#include "gamecontroller.h"

#include <QPainter>
#include <QDebug>


Boss::Boss(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Boss);
    pixMap.load(":/images/Boss.png");
    gradient = new QLinearGradient(QPoint(-50, -50), QPoint(50, 50));
    gradient->setColorAt(0, Qt::red);
    gradient->setColorAt(0.2, Qt::yellow);
    gradient->setColorAt(0.7, Qt::blue);
    gradient->setColorAt(1, Qt::green);
    setPos(viewWidth/2, 150);
    life = fullLife = 30 * difficulty;
    rad = cnt = 0;
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
        painter->scale(1.3, 1.3);
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

    if(++cnt == 10) {
        rad = (rad + 18) % 360;
        controller.shootBossBall(pos(), rad + 0);
        controller.shootBossBall(pos(), rad + 72);
        controller.shootBossBall(pos(), rad + 144);
        controller.shootBossBall(pos(), rad + 216);
        controller.shootBossBall(pos(), rad + 288);
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
