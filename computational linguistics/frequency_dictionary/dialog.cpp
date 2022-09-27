#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include<QDebug>
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked_dial() {
    std::string temp;
    temp = (ui->lineEdit->text()).toStdString();
    std::cout << "in dialog \n";
    std::cout << temp << "\n";
    QTextStream out(stdout);
    out << ui->lineEdit->text() << "\n";
    //return temp;
}
