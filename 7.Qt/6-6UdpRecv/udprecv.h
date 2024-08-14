#ifndef UDPRECV_H
#define UDPRECV_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class UdpRecv; }
QT_END_NAMESPACE

class UdpRecv : public QWidget
{
    Q_OBJECT

public:
    UdpRecv(QWidget *parent = nullptr);
    ~UdpRecv();

private slots:
    void on_bindBt_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::UdpRecv *ui;
    QUdpSocket msocket;
};
#endif // UDPRECV_H
