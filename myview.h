#ifndef MYVIEW_H
#define MYVIEW_H

#include "myplane.h"
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
public slots:

private:
    QGraphicsScene *scene;
    MyPlane *plane;
};

#endif // MYVIEW_H
