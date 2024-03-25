#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QSslSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpSocket TCPsocket_;
    QSslSocket SSLsocket_;
    //QUdpSocket socket_;
    bool checkpoint= false;
public slots:
    void doConnected();
    void doDisconnected();
    void doReadyRead();
    void check_dissconnection();

private slots:
    void on_pbConnect_clicked();

    void on_pbDisconnect_clicked();

    void on_pbSend_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
