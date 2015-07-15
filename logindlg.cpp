#include "logindlg.h"
#include "ui_logindlg.h"
#include "helpdlg.h"
#include "qpainter.h"
#include "rank.h"
#include <QIcon>
#include <QTextEdit>
#include <QDateTime>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QMessageBox>

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    // 设置背景图片
    this->setWindowFlags(Qt::FramelessWindowHint);
    pix = new QPixmap;
    pix->load(":/images/LogInBackground.png", 0, Qt::AvoidDither|Qt::ThresholdAlphaDither|Qt::ThresholdDither);
    resize(pix->size());
    this->setMask(pix->mask());
    // 设置按钮透明
    ui->pushButton_exit->setFlat(true);
    ui->pushButton_About->setFlat(true);
    ui->pushButton_help->setFlat(true);
    ui->pushButton_start->setFlat(true);
    ui->pushButton_ShowRank->setFlat(true);
    //初始化玩家信息
    qsrand(QDateTime::currentDateTime().utcOffset());
    ui->lineEdit->setText(QString("玩家%1").arg(qrand()));
}

LogInDlg::~LogInDlg()
{
    delete ui;
}

void LogInDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)//拦截左键
    {
        move(event->globalPos() - this->dragPosition);//定位窗口新位置
        event->accept();//默认处理过程
    }
}

void LogInDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)//拦截点击左键动作
    {
        this->dragPosition = event->globalPos() - this->frameGeometry().topLeft(); //计算窗口起始位置并保存
        event->accept();//默认处理过程
    }
}

void LogInDlg::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, *pix);//重绘图片
}

void LogInDlg::on_pushButton_start_clicked()
{
    loadmode = false;
    saveBackGroundType();
    saveBackGroundLoop();
    saveLoadMode();
    saveDifficulty();
    savePlayerName();
    accept();
}

void LogInDlg::on_pushButton_help_clicked()
{
    HelpDlg *dlg = new HelpDlg(this);
    dlg->setModal(true);
    dlg->show();
}

void LogInDlg::on_pushButton_About_clicked()
{
    QMessageBox::about(this, tr("关于作者"), tr("山东科技大学信息学院\n软件工程张正锟\n网址:WWW.ZZKUN.COM"));
}

void LogInDlg::saveBackGroundType()
{
    QString str = ui->comboBox->currentText();
    if(str == tr("星际迷航")) backgroundName = tr(":/images/background.png");
    else if(str == tr("死亡峡谷")) backgroundName = tr(":/images/bg2.jpg");
    else if(str == tr("天空之城")) backgroundName = tr(":/images/bg3.jpg");
    else if(str == tr("死神沙漠")) backgroundName = tr(":/images/bg4.jpg");
}

void LogInDlg::saveBackGroundLoop()
{
     QString str = ui->comboBox_2->currentText();
     if(str == "开启") backgroundLoop = true;
     else backgroundLoop = false;
}

void LogInDlg::saveLoadMode()
{
    QString str = ui->comboBox_3->currentText();
    if(str == "开启") loadmode = true;
    else loadmode = false;
}

void LogInDlg::saveDifficulty()
{
    QString str = ui->comboBox_4->currentText();
    if(str == "简单") difficulty = 1;
    else if(str == "中等") difficulty = 2;
    else difficulty = 3;
}

void LogInDlg::savePlayerName()
{
    playerName = ui->lineEdit->text();
}

void LogInDlg::on_pushButton_ShowRank_clicked()
{
    Rank rank;
    rank.show();
}
