#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <QDebug>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fd = ::open("/dev/led_drv",O_RDWR);
    if(fd == -1)
        {
          qDebug()<<"open";
            return ;
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    char buf[2];
    buf[0] = 0; //关灯
    buf[1] = 8;
    ::write(fd,buf,sizeof(buf));

}

void MainWindow::on_pushButton_2_clicked()
{
    char buf[2];
    buf[0] = 1; //关灯
    buf[1] = 8;
    ::write(fd,buf,sizeof(buf));

}
