#include "gamecontroller.h"
#include <QDebug>

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
      timer.start(1000/3);
      //初始化我的战机（唯一）
      plane = new MyPlane;
      plane->setFocus();
      plane->setPos(240, 400);
      scene->addItem(plane);
      //安装事件过滤器,在GameController中处理事件
      scene->installEventFilter(this);
}

GameController::~GameController()
{

}

bool GameController::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *key = (QKeyEvent*)event;
        switch (key->key()) {
        case Qt::Key_Left:
            plane->moveLeft();
            break;
        case Qt::Key_Right:
            plane->moveRight();
            break;
        case Qt::Key_Up:
            plane->moveUp();
            break;
        case Qt::Key_Down:
            plane->moveDown();
            break;
        }
    }
    return QObject::eventFilter(obj, event);
}

