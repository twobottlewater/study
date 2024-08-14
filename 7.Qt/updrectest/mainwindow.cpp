#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , udpReceiver(new UdpReceiver(this))
{
    ui->setupUi(this);
    connect(udpReceiver, &UdpReceiver::jsonDataReceived, this, &MainWindow::onJsonDataReceived);

    // 开始监听 UDP 数据包
    udpReceiver->startListening(8080);  // 替换为您希望监听的端口
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onJsonDataReceived(const QString &jsonData)
{
    ui->textEdit->append(jsonData);
}
