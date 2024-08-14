/*
	拼接得到完整的http请求，然后使用post方法发送给阿里云服务器
*/
void MainWindow::get_car_number()
{
	//ui->camera->pixmap()获取标签中显示的图片
	//我自己改写的例子代码：直接把jpg图片的路径名作为QImage构造函数的参数，也是可以的
    QImage myImage(ui->camera->pixmap()->toImage());
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

/*
	摄像头camera继承QThread，多线程任务函数中拍照保存
*/
void camera::run()
{
    uchar RGB_data[Camera_wide*Camera_height*3]={0};
    struct v4l2_buffer getBuffer;
    while (1) {
        if(stop_flag){
            sleep(1);
            continue;
        }
        for(int i=0;i<BUFFER_SIZE;i++){
            bzero(&getBuffer,sizeof(getBuffer));
            getBuffer.index=i;
            getBuffer.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
            getBuffer.memory=V4L2_MEMORY_MMAP;
            if(ioctl(camerafd,VIDIOC_DQBUF,&getBuffer)==-1){
                printf("VIDIOC_DQBUF failed\n");
                return;
            }

            bzero(&RGB_data,Camera_wide*Camera_height*3);
            yuyvDataTorgbData(MB[i].mmapHead,RGB_data,Camera_wide,Camera_height);
			//把RGB数据保存成QImage的对象
            QImage image(RGB_data,Camera_wide,Camera_height,QImage::Format_RGB888);
			//把QImage转换成QPixmap，然后在标签上显示，这样子就不需要打开lcd的驱动了
            label_camera->setPixmap(QPixmap::fromImage(image));

            if(ioctl(camerafd,VIDIOC_QBUF,&getBuffer)==-1){
                printf("VIDIOC_QBUF failed\n");
                return;
            }
        }
    }
}
