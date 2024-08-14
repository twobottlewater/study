#include "udpsend.h"
#include "ui_udpsend.h"

UdpSend::UdpSend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UdpSend)
{
    ui->setupUi(this);
}

UdpSend::~UdpSend()
{
    delete ui;
}


void UdpSend::on_sendBt_clicked()
{
    QString data = ui->textEdit->toPlainText();
    msocket.writeDatagram(data.toUtf8(), QHostAddress(ui->ipEdit->text()),ui->portEdit->text().toUShort());
}
