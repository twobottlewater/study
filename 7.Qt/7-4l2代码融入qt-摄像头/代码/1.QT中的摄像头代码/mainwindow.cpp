#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //第一步：获取当前系统中所有可以使用的摄像头信息
    auto list=QCameraInfo::availableCameras();
    for(auto x:list)
    {
        //qDebug()<<"摄像头的设备名称是: "<<x.deviceName();
        //qDebug()<<"摄像头的描述信息是: "<<x.description();
        //在下拉框中显示设备名称
        ui->comboBox->addItem(x.deviceName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//启动摄像头
void MainWindow::on_pushButton_clicked()
{
    //获取你在下拉框中选择的那个摄像头设备名称
    QString str=ui->comboBox->currentText();
    //第二步：创建摄像头对象
    mycamera=new QCamera(str.toUtf8(),this);
    //第三步：创建QVideoWidget对象用于摄像头画面的显示
    QVideoWidget *win=new QVideoWidget(ui->widget);
    //调整窗口的大小
    win->resize(ui->widget->width(),ui->widget->height());
    //让摄像头跟窗口绑定(让QCamera的对象可以跟窗口形成对应关系，摄像头画面就在该窗口显示)
    mycamera->setViewfinder(win);
    //显示窗口
    win->show();
    //启动摄像头
    mycamera->start();
}
//关闭摄像头
void MainWindow::on_pushButton_2_clicked()
{
    //关闭摄像头
    mycamera->stop();
}
