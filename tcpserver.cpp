#include "tcpserver.h"
#include "ui_tcpserver.h"

tcpserver::tcpserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpserver)
{
    ui->setupUi(this);
}

tcpserver::~tcpserver()
{
    delete ui;
}

