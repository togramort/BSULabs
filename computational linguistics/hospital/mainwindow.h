#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <form_edit.h>
#include <form_add.h>
#include <form_delete.h>
#include <form_add_sensors.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_radioButton_doctor_clicked();

    void on_radioButton_nurse_clicked();

    void on_radioButton_state_up_clicked();

    void on_radioButton_state_down_clicked();

    void on_radioButton_a_z_clicked();

    void on_radioButton_z_a_clicked();

    void on_radioButton_both_clicked();

    void on_edit_clicked();

    void on_delete_2_clicked();

    void on_add_sensors_clicked();

    void on_radioButton_urgent_clicked();

private:
    Ui::MainWindow *ui;
    form_edit *form_edit;
    form_add *form_add;
    form_delete *form_delete;
    form_add_sensors *form_add_sensors;

public slots:
    void slotFormEdit(QVector<QString> vec);
    void slotFormAdd(QVector<QString> vec);
    void slotFormDelete(int id);
    void slotFormAddSensors(int id, double state);
};
#endif // MAINWINDOW_H
