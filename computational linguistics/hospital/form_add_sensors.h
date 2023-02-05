#ifndef FORM_ADD_SENSORS_H
#define FORM_ADD_SENSORS_H

#include <QDialog>

namespace Ui {
class form_add_sensors;
}

class form_add_sensors : public QDialog
{
    Q_OBJECT

public:
    explicit form_add_sensors(QWidget *parent = nullptr);
    ~form_add_sensors();

private:
    Ui::form_add_sensors *ui;

signals:
    void signalForm(int id, double state);

private slots:
    void on_pushButton_clicked();
};

#endif // FORM_ADD_SENSORS_H
