#include "form_add_sensors.h"
#include "ui_form_add_sensors.h"

form_add_sensors::form_add_sensors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_add_sensors)
{
    ui->setupUi(this);
}

form_add_sensors::~form_add_sensors()
{
    delete ui;
}

void form_add_sensors::on_pushButton_clicked()
{
    double temp, pressure, saturation, pulse, state = 0;
    int id = ui->lineEdit_5->text().toInt();
    temp = ui->lineEdit->text().toDouble();
    pressure = ui->lineEdit_2->text().toDouble();
    saturation = ui->lineEdit_3->text().toDouble();
    pulse = ui->lineEdit_4->text().toDouble();

    bool is_high_temp = false, is_high_pressure = false, is_low_saturation = false, is_high_pulse = false;
    int counter = 0;

    if (temp >= 37.5 || temp <= 35) {
        is_high_temp = true;
        ++counter;
    }
    if (pressure >= 1.53 || pressure <= 1) {
        is_high_pressure = true;
        ++counter;
    }
    if (saturation <= 95 || saturation >= 100) {
        is_low_saturation = true;
        ++counter;
    }
    if (pulse >= 120 || pulse <= 60) {
        is_high_pulse = true;
        ++counter;
    }

    if (counter == 1) {
        state = 0.5;
    } else if (counter == 2) {
        state = 1.0;
    } else if (counter == 3) {
        state == 2;
    } else if (counter == 4) {
        state = 3;
    }

    emit signalForm(id, state);
}

