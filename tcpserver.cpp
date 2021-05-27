#include "tcpserver.h"
#include "ui_tcpserver.h"

tcpserver::tcpserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpserver)
{
    ui->setupUi(this);
    initServer();
    //Random Messages
    for(int i=1;i<20;i++){
        randomMessages<<"Mensaje Aleatorio" + QString::number(i);
    }
    //connects
    connect(ui->btn_close, &QAbstractButton::clicked,this,&QWidget::close);

    connect(qTcpServer,&QTcpServer::newConnection,this,&tcpserver::sendRandomMessage);
}

tcpserver::~tcpserver()
{
    delete ui;
}

void tcpserver::initServer()
{
    qInfo()<<"init Server";
    qTcpServer=new QTcpServer(this);
    if(!qTcpServer->listen()){
        qInfo()<<"Server error: "+qTcpServer->errorString();
        return;
    }
    QString port=QString::number(qTcpServer->serverPort(),10);
    QString ipAddress;
    QList<QHostAddress> ipAddressList=QNetworkInterface::allAddresses();
    for(int i=0;ipAddressList.size();i++){
        if(ipAddressList.at(i)!=QHostAddress::LocalHost&& ipAddressList.at(i).toIPv4Address()){
            ipAddress=ipAddressList.at(i).toString();
            qInfo()<<"ip: "<<ipAddress+" ,puerto:"+port;
            break;
        }
    }
    if(ipAddress.isEmpty()){
        ipAddress=QHostAddress(QHostAddress::LocalHost).toString();
    }
    QString info="ip "+ipAddress+", puerto= "+port;
    ui->label_info->setText(info);
}

void tcpserver::sendRandomMessage()
{
    qInfo()<<"Send Random Message";
    QByteArray qByteArray;
    QDataStream qDataStream(&qByteArray,QIODevice::WriteOnly);
    QString randomMessage=randomMessages[QRandomGenerator::global()->bounded(randomMessages.size())];
    qDataStream<< randomMessage;
    QTcpSocket *clientConnection=qTcpServer->nextPendingConnection();
    connect(clientConnection,&QAbstractSocket::disconnected,clientConnection,&QObject::deleteLater);
    clientConnection->write(qByteArray);
    clientConnection->disconnectFromHost();
    ui->label_msg->setText(randomMessage);
}

