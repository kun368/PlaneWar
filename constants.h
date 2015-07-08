#ifndef CONSTANTS_H
#define CONSTANTS_H

extern bool loadmode;

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
    GO_FlowBack
};

#endif // CONSTANTS_H

