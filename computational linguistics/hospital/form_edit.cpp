#include "form_edit.h"
#include "ui_form_edit.h"

form_edit::form_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_edit)
{
    ui->setupUi(this);
}

form_edit::~form_edit()
{
    delete ui;
}

void form_edit::on_pushButton_done_clicked()
{
    QVector<QString> vec (8);
    vec[0] = ui->lineEdit_surname->text();
    vec[1] = ui->lineEdit_name->text();
    vec[2] = ui->lineEdit_patronymic->text();
    vec[3] = ui->lineEdit_age->text();
    vec[4] = ui->lineEdit_ward->text();
    vec[5] = ui->lineEdit_disease->text();
    vec[6] = ui->lineEdit_state->text();
    vec[7] = ui->lineEdit->text();

    emit signalForm(vec);
}


void form_edit::on_pushButton_cancel_clicked()
{
    this->close();
}
