#include "udprecv.h"
#include "ui_udprecv.h"

UdpRecv::UdpRecv(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UdpRecv)
{
    ui->setupUi(this);

    //lambda函数   [捕获对象](参数列表)->返回值类型{函数体}
    int a =123;
    int b =321;
    auto fun = [=,&b]()->void{
        qDebug()<<"lambda"<<a<<b;
    };
    fun();

    //关联数据信号
    connect(&msocket, &QUdpSocket::readyRead, this , [&](){
        char buffer[msocket.bytesAvailable()];
        msocket.readDatagram(buffer, sizeof(buffer), NULL, NULL);
        ui->listWidget->addItem(buffer);
    });

}

UdpRecv::~UdpRecv()
{
    delete ui;
}


void UdpRecv::on_bindBt_clicked()
{
    msocket.bind(QHostAddress::AnyIPv4, ui->portEdit->text().toUShort());
}

void UdpRecv::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        //加入组播
        msocket.joinMulticastGroup(QHostAddress(ui->ipEdit->text()));
    }else
    {
        msocket.leaveMulticastGroup(QHostAddress(ui->ipEdit->text()));
    }
}
