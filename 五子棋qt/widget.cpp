#include "widget.h"
#include "ui_widget.h"
#include <qdebug.h>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 中心点 215,215
    nextBlack=QPoint(215,215);
    nextWhite=QPoint(215,215);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *p)
{
    QPainter painter(this);
    //绘制棋盘
    QPen pen;
    pen.setBrush(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=20;i<450;i+=30)
        painter.drawLine(20,i,440,i);
    for(int j=20;j<450;j+=30)
        painter.drawLine(j,20,j,440);


    if(playNext)
    {
        pen.setBrush(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(nextBlack.x(),nextBlack.y() ,30,30);
    }
    else
    {
        pen.setBrush(Qt::white);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(nextWhite.x(),nextWhite.y() ,30,30);
    }


    /***********绘制棋子***********/

    for(int i=0;i<playBlackList.size();i++)
    {        
        pen.setBrush(Qt::black);
        painter.setPen(pen);
        painter.setBrush(Qt::black);
        painter.drawEllipse(playBlackList[i].x(),playBlackList[i].y() ,30,30);
    }
    for(int i=0;i<playWhiteList.size();i++)
    {
        pen.setBrush(Qt::white);
        painter.setPen(pen);
        painter.setBrush(Qt::white);
        painter.drawEllipse(playWhiteList[i].x(),playWhiteList[i].y() ,30,30);
    }

}
void Widget::keyPressEvent(QKeyEvent *k)//键盘按键读取
{
    if(playNext==true)      //黑色
    switch (k->key())
    {

        case Qt::Key_W : nextBlack.ry()-=30; break;
        case Qt::Key_S : nextBlack.ry()+=30; break;
        case Qt::Key_A : nextBlack.rx()-=30; break;
        case Qt::Key_D : nextBlack.rx()+=30; break;
    }
    else
    switch (k->key())
    {
        case Qt::Key_Up: nextWhite.ry()-=30; break;
        case Qt::Key_Down : nextWhite.ry()+=30; break;
        case Qt::Key_Left : nextWhite.rx()-=30; break;
        case Qt::Key_Right : nextWhite.rx()+=30; break;
    }

/***********判断棋子是否出界**************/
    if(nextWhite.x()<0) nextWhite.rx()+=30;
    else
        if(nextWhite.x()>440) nextWhite.rx()-=30;
    else
        if(nextWhite.y()<0) nextWhite.ry()+=30;
    else
        if(nextWhite.y()>440) nextWhite.ry()-=30;

    if(nextBlack.x()<0) nextBlack.rx()+=30;
    else
        if(nextBlack.x()>440) nextBlack.rx()-=30;
    else
        if(nextBlack.y()<0) nextBlack.ry()+=30;
    else
        if(nextBlack.y()>440) nextBlack.ry()-=30;


    if(k->key()==Qt::Key_Space)
    {
        //判断是否可以下棋
        if(playNext)
        {
            QPoint p;
            p=nextBlack;
            if(checkIsPos(p)==true)
            {
                playBlackList.push_back(p);
                playNext=!playNext;
            }
        }
        else
        {
            QPoint p;
            p=nextWhite;
            if(checkIsPos(p))
            {
                playWhiteList.push_back(p);
                playNext=!playNext;
            }
        }
    }


    update();
    if(!playBlackList.isEmpty())
    if(checkWin(playBlackList.last(),playBlackList)==true)
    {
        QMessageBox msgBox;
        msgBox.setText("********黑棋获胜*******");
        msgBox.exec();
        this->close();
    }
    if(!playWhiteList.isEmpty())
    if(checkWin(playWhiteList.last(),playWhiteList)==true)
    {
        QMessageBox msgBox;
        msgBox.setText("********白棋获胜*******");
        msgBox.exec();
        this->close();
    }
}

void Widget::selectPos()
{

}

bool Widget::checkIsPos(QPoint a)
{
    for(int i=0;i<playBlackList.size();i++)
        if(playBlackList[i].x()==a.x()&&playBlackList[i].y()==a.y())
            return false;
    for(int i=0;i<playWhiteList.size();i++)
        if(playWhiteList[i].x()==a.x()&&playWhiteList[i].y()==a.y())
            return false;
    return true;
}

bool Widget::checkWin(QPoint pos,QList<QPoint> list)
{
    /********右向胜利判断*********/
    bool isCont=true;
    QPoint p=pos;
    for(int j=0;j<4;j++)  //横向判断
    {
        p.rx()+=30;
        for(int i=0;i<list.size();i++)
        {
            if(p.x()==list[i].x()&&p.y()==list[i].y()) break;
            if(i==list.size()-1) isCont=false;
        }
        if(j==3 && list.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********下向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //纵向判断
    {
        p.ry()+=30;
        for(int i=0;i<list.size();i++)
        {
            if(p.x()==list[i].x()&&p.y()==list[i].y()) break;
            if(i==list.size()-1) isCont=false;
        }
        if(j==3 && list.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********左向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //左横向判断
    {
        p.rx()-=30;
        for(int i=0;i<list.size();i++)
        {
            if(p.x()==list[i].x()&&p.y()==list[i].y()) break;
            if(i==list.size()-1) isCont=false;
        }
        if(j==3 && list.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********上方向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //上纵向判断
    {
        p.ry()-=30;
        for(int i=0;i<list.size();i++)
        {
            if(p.x()==list[i].x()&&p.y()==list[i].y()) break;
            if(i==list.size()-1) isCont=false;
        }
        if(j==3 && list.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********左上方向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //上纵向判断
    {
        p.rx()-=30;
        p.ry()-=30;
        for(int i=0;i<playBlackList.size();i++)
        {
            if(p.x()==playBlackList[i].x()&&p.y()==playBlackList[i].y()) break;
            if(i==playBlackList.size()-1) isCont=false;
        }
        if(j==3 && playBlackList.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********左下方向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //上纵向判断
    {
        p.rx()-=30;
        p.ry()+=30;
        for(int i=0;i<playBlackList.size();i++)
        {
            if(p.x()==playBlackList[i].x()&&p.y()==playBlackList[i].y()) break;
            if(i==playBlackList.size()-1) isCont=false;
        }
        if(j==3 && playBlackList.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********右上方向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //上纵向判断
    {
        p.rx()+=30;
        p.ry()-=30;
        for(int i=0;i<playBlackList.size();i++)
        {
            if(p.x()==playBlackList[i].x()&&p.y()==playBlackList[i].y()) break;
            if(i==playBlackList.size()-1) isCont=false;
        }
        if(j==3 && playBlackList.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }

    /********右下方向胜利判断*********/
    isCont=true;p=pos;
    for(int j=0;j<5;j++)  //上纵向判断
    {
        p.rx()+=30;
        p.ry()+=30;
        for(int i=0;i<playBlackList.size();i++)
        {
            if(p.x()==playBlackList[i].x()&&p.y()==playBlackList[i].y()) break;
            if(i==playBlackList.size()-1) isCont=false;
        }
        if(j==3 && playBlackList.size()>4 &&isCont==true)
        {
            qDebug()<<"shengli";
            return true;
        }
    }
}













