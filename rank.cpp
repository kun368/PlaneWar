#include "rank.h"
#include <QDialog>
#include <QDataStream>
#include <QtAlgorithms>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>

Rank::Rank(QObject *parent) :
    QObject(parent),
    file("rank.dat")
{
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
        qDebug() << "Can't open file";
}

Rank::~Rank()
{
    file.close();
}

void Rank::read()
{
    list.clear();
    file.seek(0);
    QDataStream in(&file);
    while(!in.atEnd()) {
        Record t;
        in >> t.name >> t.score >> t.time;
        list.push_back(t);
    }
    qSort(list);
}

void Rank::write()
{
    file.resize(0);
    qSort(list);
    QDataStream out(&file);
    for(Record i : list) {
        out << i.name << i.score << i.time;
    }
}

void Rank::add(Record rhs)
{
    list.push_back(rhs);
    qSort(list);
    QDataStream out(&file);
    out << rhs.name << rhs.score << rhs.time;
}

void Rank::show()
{
    read();
    qSort(list);
    qDebug() << list.size();
    for(Record i : list) {
        qDebug() << i.name << i.score << i.time;
    }
    QStandardItemModel * model = new QStandardItemModel(list.size(), 3);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("玩家姓名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("玩家得分")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("时间")));
    for(int i = 0; i < list.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(list[i].name));
        model->setItem(i, 1, new QStandardItem(QString::number(list[i].score)));
        model->setItem(i, 2, new QStandardItem(list[i].time.toString()));
    }
    QTableView * view = new QTableView;
    view->setModel(model);
    view->setFixedSize(500, 400);
    view->setWindowTitle("飞机大战得分排行榜");
    view->setColumnWidth(2, 200);
    view->show();
}

