#ifndef RANK_H
#define RANK_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QDateTime>
#include <QDebug>


struct Record{
    QString name;
    int score;
    QDateTime time;
    bool operator < (const Record & rhs) const {
        return score == rhs.score ? time < rhs.time : score > rhs.score;
    }
};

class Rank : public QObject
{
    Q_OBJECT
public:
    explicit Rank(QObject *parent = 0);
    ~Rank();
    void read();
    void write();
    void add(Record rhs);
    void show();
signals:
public slots:
private:
    QFile file;
    QList<Record> list;
};

#endif // RANK_H
