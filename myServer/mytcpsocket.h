#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class mytcpsocket:public QTcpSocket
{
    Q_OBJECT
public:
    explicit mytcpsocket(qintptr socketDescriptor, QObject *parent = nullptr);
    ~mytcpsocket();

signals:
    void ReadData(QByteArray,qintptr);
    void sockDisconnect(qintptr socketDescriptor);

private:
    qintptr socketID;

private slots:
    void thisreaddata();
    void thisdisconnected();
};

#endif // MYTCPSOCKET_H
