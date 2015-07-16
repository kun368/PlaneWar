#include "rank.h"
#include <QDialog>
#include <QDataStream>
#include <QTextStream>
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
    read();
}

Rank::~Rank()
{
    file.close();
}

void Rank::read()
{
    list.clear();
    file.seek(0);
    QTextStream in(&file);
    while(!in.atEnd()){
        Record t;
        in >> t.name >> t.score >> t.time;
        list.push_back(t);
    }
}

void Rank::write()
{
    file.resize(0);
    file.seek(0);
    QTextStream out(&file);
    for(Record i : list)
        out << i.name << " " << i.score << " "<< i.time << " ";
}

void Rank::add(Record rhs)
{
    list.push_back(rhs);
    write();
}

void Rank::show()
{
    read();
    QList<Record> showList = list;
    qSort(showList);
    QStandardItemModel * model = new QStandardItemModel(showList.size(), 3);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("玩家姓名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("玩家得分")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("时间")));
    for(int i = 0; i < list.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(showList[i].name));
        model->setItem(i, 1, new QStandardItem(showList[i].score));
        model->setItem(i, 2, new QStandardItem(showList[i].time));
    }
    QTableView * view = new QTableView;
    view->setModel(model);
    view->setFixedSize(500, 400);
    view->setWindowTitle("飞机大战得分排行榜");
    view->setColumnWidth(2, 200);
    view->show();
}

