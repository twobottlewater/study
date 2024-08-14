#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //安装数据库驱动
    base1=QSqlDatabase::addDatabase("QSQLITE");

    //设置数据库的名字
    base1.setDatabaseName("./new.db");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insertBt_clicked()
{

}
