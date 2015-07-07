#ifndef MYVIEW_H
#define MYVIEW_H

#include "myplane.h"
#include "gamecontroller.h"
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
private:
    QGraphicsScene *scene;
    MyPlane *plane;
    GameController *game;
};

#endif // MYVIEW_H
