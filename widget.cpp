#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //socket_.connected();
    //socket_.readyRead();
    //socket_.state();
    QObject::connect(&TCPsocket_, &QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&TCPsocket_, &QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&TCPsocket_, &QAbstractSocket::readyRead,this,&Widget::doReadyRead);
    QObject::connect(&SSLsocket_, &QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&SSLsocket_, &QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&SSLsocket_, &QAbstractSocket::readyRead,this,&Widget::doReadyRead);
        check_dissconnection();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){
    ui->pteMessage->insertPlainText("Connected\r\n");
    check_dissconnection();
}

void Widget::doDisconnected(){
    ui->pteMessage->insertPlainText("Disconnected\r\n");
    check_dissconnection();
}

void Widget::doReadyRead(){
    if (ui->cb_http->isChecked()){
        ui->pteMessage->insertPlainText(TCPsocket_.readAll());
    }
    else{
        ui->pteMessage->insertPlainText(SSLsocket_.readAll());
    }
}

void Widget::on_pbConnect_clicked()
{
    if (ui->cb_http->isChecked()){
        TCPsocket_.connectToHost(ui->leHost->text(),ui->lePort->text().toUShort());
    }
    else{
        SSLsocket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort());
    }
    check_dissconnection();
}


void Widget::on_pbDisconnect_clicked()
{
    if(ui->cb_http->isChecked()){
        TCPsocket_.close();
    }
    else{
        SSLsocket_.close();
    }
    check_dissconnection();
}


void Widget::on_pbSend_clicked()
{
    if(ui->cb_http->isChecked()){
        TCPsocket_.write(ui->pteSend->toPlainText().toUtf8());
    }
    else{
        SSLsocket_.write(ui->pteSend->toPlainText().toUtf8());
    }
    check_dissconnection();
}

void Widget::check_dissconnection(){
    if(ui->cb_http->isChecked()){
        ui->pbDisconnect->setEnabled(TCPsocket_.state() == QTcpSocket::ConnectedState);
    }
    else{
        ui->pbDisconnect->setEnabled(SSLsocket_.state() == QSslSocket::ConnectedState);
    }
}


