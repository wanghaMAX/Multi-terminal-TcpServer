#include "widget.h"
#include "ui_widget.h"

int port = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //init Axis Y
    for(int i=0;i<5;i++)
        for(int j=0;j<10;j++){
            data1[i][j] = 200;
            data2[i][j] = 200;
            data3[i][j] = 200;
        }
}

Widget::~Widget()
{
    delete ui;
    delete myTcpServer;
}

void Widget::on_pushButton_clicked()
{
    port = ui->lineEdit->text().toInt();
    myTcpServer = new mytcpserver;
    connect(myTcpServer,SIGNAL(connectClient(qintptr,QString,quint16)),this,SLOT(shows(qintptr,QString,quint16)));
    connect(myTcpServer,&mytcpserver::sendtoui,this,&Widget::showd);
    connect(myTcpServer,&mytcpserver::socketIDtoui,this,&Widget::ptr_resize);
}

void Widget::shows(qintptr des,QString ip,quint16 port){
    qDebug() << des;
    qDebug() << ip;
    qDebug() << port;
    qDebug() << "in show";
    ptr.append(des);
}

void Widget::showd(QByteArray str,qintptr num){
    int i=0;
    for(i=0;i<ptr.size();i++){
        if(ptr[i]==num) break;
    }
    QJsonDocument doc = QJsonDocument::fromJson(str);
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        data1[i][key[i]] = obj.value("tem").toVariant().toInt() + 200;
        data2[i][key[i]] = obj.value("wet").toVariant().toInt() + 200;
        data3[i][key[i]] = obj.value("v").toVariant().toInt() + 200;
        qDebug() << data1[i][key[i]];
        QString data = "tem:"+QString::number(data1[i][key[i]])
                +"wet:"+QString::number(data2[i][key[i]])
                +"v:"+QString::number(data3[i][key[i]])
                +"from:"+QString::number(i);
        ui->textBrowser->append(data);
        key[i]++;
        if(key[i]==9){
            for(int s=0;s<8;s++)
                data1[i][s] = data1[i][s+1];
            data1[i][9] = 200;
            key[i] = 8;
//            for(int st=0;st<5;st++){
//                for(int s=0;s<9;s++){
//                    data1[st][s] = data1[st][s+1];
//                }
//                data1[st][9] = 200;
//                key[i] = 8;
//            }
        }
    }
    QWidget::update();
}

void Widget::ptr_resize(qintptr num){
    int i=0;
    for(i=0;i<ptr.size();i++){
        if(ptr[i]==num) break;
    }
    ptr.removeAt(i);
}

void Widget::paintEvent(QPaintEvent *paint){
    QPen pen;
    pen.setWidth(4);
    QPainter painter(this);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(30,320,400,320);
    painter.drawLine(30,320,30,220);
    for(int i=0;i<ptr.size();i++){
        pen.setColor(color[i]);
        painter.setPen(pen);
        int y = 520-data1[i][0];
        for(int ii=1;ii<8;ii++){
            if(data1[i][ii] != 200){
                painter.drawLine(x[i],y,x[i]+50,520-data1[i][ii]);
                x[i] = x[i] + 50;
                y = 520-data1[i][ii];
            }else{
                break;
            }
        }
        x[i] = 30;
    }
}
