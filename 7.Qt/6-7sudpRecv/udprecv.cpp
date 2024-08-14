#include "udprecv.h"
#include "ui_udprecv.h"

udpRecv::udpRecv(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::udpRecv)
{
    ui->setupUi(this);
}

udpRecv::~udpRecv()
{
    delete ui;
}

