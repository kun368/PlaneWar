#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

extern bool loadmode;
extern QString backgroundName;
extern bool backgroundLoop;
extern const int viewHeight;
extern const int viewWidth;

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
    GO_BossBall
};

#endif // CONSTANTS_H

