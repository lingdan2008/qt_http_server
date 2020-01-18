#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    qDebug() << __FUNCTION__;

    ui->setupUi(this);
    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
}

Dialog::~Dialog()
{
    qDebug() << __FUNCTION__;

    delete ui;
}

void Dialog::on_pushButton_Start_clicked()
{
    qDebug() << __FUNCTION__;

    HttpServer::instance().start();

    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
}

void Dialog::on_pushButton_Stop_clicked()
{
    qDebug() << __FUNCTION__;

    HttpServer::instance().stop();

    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
}
