#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化定时器
    mytimer=new QTimer(this);
    //设置超时时间
    mytimer->setInterval(50); //50ms
    //关联timeout信号
    connect(mytimer,SIGNAL(timeout()),this,SLOT(fun()));

    //初始化摄像头
    camera=new mycamera();
    camera->camera_init();
}

MainWindow::~MainWindow()
{
    //关闭摄像头
    camera->camera_uninit();
    delete ui;
}

//启动摄像头--》启动定时器
void MainWindow::on_pushButton_clicked()
{
    mytimer->start();
}
//关闭摄像头--》关闭定时器
void MainWindow::on_pushButton_2_clicked()
{
    mytimer->stop();
}
//跟定时器有关的槽函数
void MainWindow::fun()
{
    camera->camera_capture(); //显示画面
}
