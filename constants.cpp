#include "constants.h"

bool loadmode;
QString backgroundName;
bool backgroundLoop;
int difficulty;
int myPlaneFullLife;
const int viewHeight = 750;
const int viewWidth = 500;
QString playerName;


bool isInView(const QPointF & rhs){
    return rhs.x() <= viewWidth && rhs.x() >= 0 && rhs.y() >= 0 && rhs.y() <= viewHeight;
}
