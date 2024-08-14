#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
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

//抓拍画面
void MainWindow::on_pushButton_3_clicked()
{
    QCameraImageCapture *cap=new QCameraImageCapture(mycamera,this);
    //关联imageCaptured信号，在槽函数里面显示抓拍的画面
    connect(cap,SIGNAL(imageCaptured(int,QImage)),this,SLOT(fun(int,QImage)));
    //抓拍画面
    cap->capture("C:/Users/Administrator/Desktop/share/new.jpg");
}

void MainWindow::fun(int id, QImage img)
{
    //参数img存放的就是抓拍到的画面
    /*
        QT中跟图像有关的类：QPixmap  QImage
        QPixmap和QImage之间可以相互转换
        把QImage转换成QPixmap
              [static] QPixmap QPixmap::fromImage(const QImage &image)
        把QPixmap转换成QImage
              QImage QPixmap::toImage() const
    */
    QPixmap map=QPixmap::fromImage(img);
    map.scaled(ui->label->width(),ui->label->height());
    ui->label->setScaledContents(true);
    ui->label->setPixmap(map);
}
