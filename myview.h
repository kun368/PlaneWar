#ifndef MYVIEW_H
#define MYVIEW_H

#include "constants.h"
#include "myplane.h"
#include "gamecontroller.h"
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QIcon>
#include <QSound>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
private:
    QIcon *icon;
    QSound *sound;
    QGraphicsScene *scene;
    MyPlane *plane;
    GameController *game;
};

#endif // MYVIEW_H
