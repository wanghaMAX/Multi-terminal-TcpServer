#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QTextBrowser>
#include "mytcpserver.h"
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    mytcpserver *myTcpServer;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();           //start listen
    void shows(qintptr,QString,quint16);    //show the socket info
    void showd(QByteArray,qintptr);         //show the socket data
    void ptr_resize(qintptr);               //socket disconnected

private:
    Ui::Widget *ui;
    QList<qintptr> ptr; //socketID
    int data1[5][10];   //tem
    int data2[5][10];   //wet
    int data3[5][10];   //v
    QColor color[5] = {Qt::red,Qt::blue,Qt::yellow,Qt::green,Qt::black};
    int key[5] = {0,0,0,0,0};   //store temp data
    int x[5] = {30,30,30,30,30};
    int q = 0;

protected:
    void paintEvent(QPaintEvent *paint);

};

#endif // WIDGET_H
