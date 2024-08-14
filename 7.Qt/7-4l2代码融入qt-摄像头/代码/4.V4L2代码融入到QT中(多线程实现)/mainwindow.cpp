#include "mainwindow.h"
#include "ui_mainwindow.h"
extern volatile int flag;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

//启动摄像头--》启动线程
void MainWindow::on_pushButton_clicked()
{
    flag=1;
    camera->start(); //启动线程
}
//关闭摄像头--》关闭线程
void MainWindow::on_pushButton_2_clicked()
{
    flag=0;
    camera->wait(); //回收线程
}

