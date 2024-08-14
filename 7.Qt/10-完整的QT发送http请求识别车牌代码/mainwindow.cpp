#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //手动关联了finished(QNetworkReply *)
    connect(&myManager,SIGNAL(finished(QNetworkReply *)),this,SLOT(fun(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//识别车牌
void MainWindow::on_pushButton_clicked()
{
    //弹出文件对话框
    QString filepath=QFileDialog::getOpenFileName(this);

    //准备好你要识别的车牌照片
    QImage myImage(filepath);
    //定义字节数组存放等一会转换得到的base64格式的图片数据
    QByteArray byteAr;
    //定义一个缓冲区,跟字节数组绑定在一起
    QBuffer buf(&byteAr);
    //把刚才我的车牌图片按照jpg格式，存放到buf中
    myImage.save(&buf,"JPG");


    //第一步：准备好http请求
    //准备好车牌识别的api网址
    QUrl myUrl("http://ocrcp.market.alicloudapi.com/rest/160601/ocr/ocr_vehicle_plate.json");
    //新建请求对象
    QNetworkRequest myRequest(myUrl);
    //彭老师申请得到appcode
    QString appCode="APPCODE 6d919d4ae2a8425583b75daa7658e6c3";
    //服务器主机域名
    QString host="ocrcp.market.alicloudapi.com";
    //把appcode和服务器主机域名添加到请求对象中
    myRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    myRequest.setRawHeader("Authorization",appCode.toLocal8Bit());
    myRequest.setRawHeader("Host",host.toLocal8Bit());

    //第二步：把车牌照片转换成base64格式，然后封装到json数据里面发送出去
    //创建json对象
    QJsonObject jsonObj;
    //往对象里面插入两组键值对
    jsonObj.insert("image",byteAr.toBase64().data());  //把图片转换成base64格式toBase64().data()
    jsonObj.insert("configure","{\"multi_crop\":true}");  //true识别率高，false识别率要求低
    //创建jsondocument对象把刚才的json数据保存起来
    QJsonDocument jsonDoc = QJsonDocument(jsonObj);

    //把json数据转换成post函数需要的QByteArray
    QByteArray post_data = jsonDoc.toJson(QJsonDocument::Compact);
    myManager.post(myRequest,post_data);
}

//槽函数接收应答信息
void MainWindow::fun(QNetworkReply *rep)
{
    //读取应答信息
    QByteArray buf=rep->readAll();
    //在文本编辑框中显示应答信息
    ui->textEdit->setText(buf);
}
