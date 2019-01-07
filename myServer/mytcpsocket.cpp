#include "mytcpsocket.h"
#include <QString>

mytcpsocket::mytcpsocket(qintptr socketDescriptor,QObject *parent):
    QTcpSocket (parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);
    connect(this,SIGNAL(readyRead()),this,SLOT(thisreaddata()));
    connect(this,SIGNAL(disconnected()),this,SLOT(thisdisconnected()));
}

mytcpsocket::~mytcpsocket(){

}

void mytcpsocket::thisdisconnected(){
    emit sockDisconnect(this->socketID);
    qDebug() << this->socketID;
    qDebug() << "mytcpsocket::thisdisconnected";
    this->disconnectFromHost();
}

void mytcpsocket::thisreaddata(){
    QByteArray data = this->readAll();
    qDebug() << data;
    qDebug() << "in mytcpsocket::thisreaddata";
    emit ReadData(data,socketID);
}

