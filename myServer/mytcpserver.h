#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QString>
#include <QList>
#include "mytcpsocket.h"

class mytcpserver:public QTcpServer
{
    Q_OBJECT
public:
    mytcpserver();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<mytcpsocket *> socketList;

private slots:
    void socketDisSlot(qintptr socketDescriptor);
    void ReadDataSlot(QByteArray,qintptr);

signals:
    void connectClient(qintptr,QString,quint16);
    void sendtoui(QByteArray,qintptr);
    void socketIDtoui(qintptr);
};

#endif // MYTCPSERVER_H
