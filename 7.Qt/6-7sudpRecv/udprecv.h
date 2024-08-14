#ifndef UDPRECV_H
#define UDPRECV_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class udpRecv; }
QT_END_NAMESPACE

class udpRecv : public QWidget
{
    Q_OBJECT

public:
    udpRecv(QWidget *parent = nullptr);
    ~udpRecv();

private:
    Ui::udpRecv *ui;
};
#endif // UDPRECV_H
