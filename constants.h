#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QPointF>

extern bool loadmode;
extern QString backgroundName;
extern int difficulty;
extern int myPlaneFullLife;
extern bool backgroundLoop;
extern const int viewHeight;
extern const int viewWidth;
extern QString playerName;

bool isInView(const QPointF & rhs);

enum GameObjectsData {
    GD_type
};

enum GameObjectTypes {
    GO_Ball,
    GO_Bullet,
    GO_Enemy,
    GO_MyPlane,
    GO_Collision,
    GO_FlowBack,
    GO_LifeAdder,
    GO_Circle,
    GO_Boss,
    GO_BossBall,
    GO_WingPlane,
    GO_WingBullet,
    GO_Tip
};

#endif // CONSTANTS_H

