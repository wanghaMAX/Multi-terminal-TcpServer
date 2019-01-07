#include "mytcpserver.h"

extern int port;

mytcpserver::mytcpserver(){
    if(port != 0){
        this->listen(QHostAddress::Any,port);
        qDebug() << "now, "+QString::number(port)+" is listen";
    }
}

void mytcpserver::incomingConnection(qintptr socketDescriptor){
    mytcpsocket *socket = new mytcpsocket(socketDescriptor);
    socketList.append(socket);
    connect(socket,&mytcpsocket::ReadData,this,&mytcpserver::ReadDataSlot);
    connect(socket,&mytcpsocket::sockDisconnect,this,&mytcpserver::socketDisSlot);
    qDebug() << socket->peerAddress().toString();
    qDebug() << "in mytcpserver::incomingConnection";
    emit connectClient(socketDescriptor,socket->peerAddress().toString(),socket->peerPort());
}

void mytcpserver::socketDisSlot(qintptr socketDescriptor){
    for(int i=0;i<socketList.size();i++){
        if(socketList[i]->socketDescriptor() == socketDescriptor){
            socketList.removeAt(i);
            emit socketIDtoui(socketDescriptor);
            qDebug() << QString::number(i);
            qDebug() << "had been remove in mytcpserver::socketDisSlot";
        }
    }
}

void mytcpserver::ReadDataSlot(QByteArray data,qintptr from){
    qDebug() << data;
    qDebug() << from;
    qDebug() << "in mytcpserver::ReadDataSlot";
    emit sendtoui(data,from);
}

