#ifndef UDPSEND_H
#define UDPSEND_H

#include <QUdpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class UdpSend; }
QT_END_NAMESPACE

class UdpSend : public QWidget
{
    Q_OBJECT

public:
    UdpSend(QWidget *parent = nullptr);
    ~UdpSend();

private slots:
    void on_sendBt_clicked();

private:
    Ui::UdpSend *ui;
    QUdpSocket msocket;
};
#endif // UDPSEND_H
