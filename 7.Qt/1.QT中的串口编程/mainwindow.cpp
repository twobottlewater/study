#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //获取系统中所有可以使用的串口信息
    auto ret=QSerialPortInfo::availablePorts();

    //遍历容器，打印显示串口信息
    for(int i=0; i<ret.size(); i++)
    {
        qDebug()<<"串口名字: "<<ret.at(i).portName();
        qDebug()<<"串口描述信息: "<<ret.at(i).description();
    }

    //新建串口对象
    QSerialPort serialport(ret.at(1).portName());

    //设置串口的参数
    serialport.setBaudRate(QSerialPort::Baud115200); //波特率
    serialport.setDataBits(QSerialPort::Data8); //8位数据位
    serialport.setStopBits(QSerialPort::OneStop); //1位停止位
    serialport.setParity(QSerialPort::NoParity); //无奇偶校验
    serialport.setFlowControl(QSerialPort::NoFlowControl); //无流控

    //打开串口
    serialport.open(QIODevice::ReadWrite);

    //后面的代码就是通过串口read(接收)和write(发送)数据了

}

MainWindow::~MainWindow()
{
    delete ui;
}

