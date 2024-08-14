#include "udpreceiver.h"
#include <QDebug>


UdpReceiver::UdpReceiver(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
     connect(udpSocket, &QUdpSocket::readyRead, this, &UdpReceiver::onReadyRead);
}


void UdpReceiver::startListening(quint16 port)
{
    if (!udpSocket->bind(port)) {
        qDebug() << "Failed to bind to port:" << port;
    } else {
        qDebug() << "Listening on port:" << port;
    }
}



void UdpReceiver::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString jsonData = QString::fromUtf8(datagram);
        emit jsonDataReceived(jsonData);
    }
}
