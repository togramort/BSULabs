#include "form_delete.h"
#include "ui_form_delete.h"

#include <QMessageBox>

form_delete::form_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_delete)
{
    ui->setupUi(this);
}

form_delete::~form_delete()
{
    delete ui;
}

void form_delete::on_pushButton_clicked()
{
    QMessageBox::warning(this, "ATTENTION!", "You sure tou want to delete this?", QMessageBox::Yes | QMessageBox::No);
    if (QMessageBox::Yes) {
        int id;
        id = ui->lineEdit->text().toInt();
        emit signalForm(id);
    } else if (QMessageBox::No) {
        this->close();
    }
}


void form_delete::on_pushButton_2_clicked()
{
    this->close();
}
