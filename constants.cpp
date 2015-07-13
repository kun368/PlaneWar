#include "constants.h"

bool loadmode;
QString backgroundName;
bool backgroundLoop;
int difficulty;
const int viewHeight = 600;
const int viewWidth = 500;


bool isInView(const QPointF & rhs){
    return rhs.x() <= viewWidth && rhs.x() >= 0 && rhs.y() >= 0 && rhs.y() <= viewHeight;
}
