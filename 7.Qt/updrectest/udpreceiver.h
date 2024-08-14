#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H


#include <QObject>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>


class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(QObject *parent = nullptr);
     void startListening(quint16 port);

signals:
     void jsonDataReceived(const QString &jsonData);

  private slots:
      void onReadyRead();

  private:
      QUdpSocket *udpSocket;

};

#endif // UDPRECEIVER_H
