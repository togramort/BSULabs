#include "form_add.h"
#include "ui_form_add.h"

form_add::form_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_add)
{
    ui->setupUi(this);
}

form_add::~form_add()
{
    delete ui;
}

void form_add::on_pushButton_done_clicked()
{
    QVector<QString> vec (7);
    vec[0] = ui->lineEdit_surname->text();
    vec[1] = ui->lineEdit_name->text();
    vec[2] = ui->lineEdit_patronymic->text();
    vec[3] = ui->lineEdit_age->text();
    vec[4] = ui->lineEdit_ward->text();
    vec[5] = ui->lineEdit_disease->text();
    vec[6] = ui->lineEdit_state->text();


    emit signalForm(vec);
}
void form_add::on_pushButton_cancel_clicked()
{
    this->close();
}

