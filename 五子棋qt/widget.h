#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QPoint>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *p);
    void keyPressEvent(QKeyEvent *k);
    void selectPos();
    bool checkIsPos(QPoint );
    bool checkWin(QPoint,QList<QPoint>);

private:
    Ui::Widget *ui;
    QList <QPoint> playWhiteList;
    QList <QPoint> playBlackList;
    bool playNext=true;     //true 黑棋  false 白棋
    QPoint nextWhite;       //白棋next 位置
    QPoint nextBlack;
};

#endif // WIDGET_H
