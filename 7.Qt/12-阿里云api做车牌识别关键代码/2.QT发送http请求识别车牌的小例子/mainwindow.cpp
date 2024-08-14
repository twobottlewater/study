#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&myManager,SIGNAL(finished(QNetworkReply *)),this,SLOT(fun(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//识别车牌
void MainWindow::on_pushButton_clicked()
{
    QImage myImage("C:/Users/gzxw/Desktop/1.jpeg");
    QByteArray byteAr;
    QBuffer buf(&byteAr);
    myImage.save(&buf,"JPG");

    QUrl myUrl("http://ocrcp.market.alicloudapi.com/rest/160601/ocr/ocr_vehicle_plate.json");
    QNetworkRequest myRequest(myUrl);
    QString appCode="APPCODE 6d919d4ae2a8425583b75daa7658e6c3";
    QString host="ocrcp.market.alicloudapi.com";
    myRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    myRequest.setRawHeader("Authorization",appCode.toLocal8Bit());
    myRequest.setRawHeader("Host",host.toLocal8Bit());

    QJsonObject jsonObj;
    jsonObj.insert("image",byteAr.toBase64().data());
    jsonObj.insert("configure","{\"multi_crop\":true}");
    QJsonDocument jsonDoc = QJsonDocument(jsonObj);
    QByteArray post_data = jsonDoc.toJson(QJsonDocument::Compact);
    myManager.post(myRequest,post_data);
}

void MainWindow::fun(QNetworkReply *rep)
{
    //读取应答信息
    QByteArray buf=rep->readAll();
    ui->textEdit->setText(buf);
}
