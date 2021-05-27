#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include<QNetworkInterface>
#include<QTcpSocket>
#include<QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class tcpserver; }
QT_END_NAMESPACE

class tcpserver : public QMainWindow
{
    Q_OBJECT

public:
    tcpserver(QWidget *parent = nullptr);
    ~tcpserver();

private:
    Ui::tcpserver *ui;
    QTcpServer *qTcpServer=nullptr;
    QVector<QString> randomMessages;

    void initServer();

   private slots:
    void sendRandomMessage();
};
#endif // TCPSERVER_H
