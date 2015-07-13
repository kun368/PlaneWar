#include "bossball.h"
#include "gamecontroller.h"
#include <QPainter>

BossBall::BossBall(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_BossBall);
    pixMap.load(":/images/BossBall.png");
}

QRectF BossBall::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void BossBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->scale(0.7, 0.7);
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void BossBall::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() + 7);
    if(!isInView(pos())) controller.removeItem(this);
}
