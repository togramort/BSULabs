#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    form_edit = new class form_edit;
    form_add = new class form_add;
    form_delete = new class form_delete;
    form_add_sensors = new class form_add_sensors;
    connect(form_edit, &form_edit::signalForm, this, &MainWindow::slotFormEdit);
    connect(form_add, &form_add::signalForm, this, &MainWindow::slotFormAdd);
    connect(form_delete, &form_delete::signalForm, this, &MainWindow::slotFormDelete);
    connect(form_add_sensors, &form_add_sensors::signalForm, this, &MainWindow::slotFormAddSensors);

    db.setHostName("localhost");
    db.setDatabaseName("hospital");
    db.setUserName("postgres");
    db.setPassword("power2020");
    if (!db.open()) {
        qDebug() << "Error\n" << db.lastError().text();
    } else {
        qDebug() << "OK\n" << "Successfull!\n";
    }
    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("update patients set who_call = 'nurse' where state between 0.1 and 0.9");
    query->setQuery("update patients set who_call = 'doctor' where state between 1.0 and 2");
    query->setQuery("update patients set who_call = 'URGENT' where state between 2.1 and 3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void update() {
    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("update patients set who_call = 'nurse' where state between 0.1 and 0.9");
    query->setQuery("update patients set who_call = 'doctor' where state between 1.0 and 2");
    query->setQuery("update patients set who_call = 'URGENT' where state between 2.1 and 3");
}

void MainWindow::on_radioButton_doctor_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("SELECT * FROM patients where state between 1 and 2");

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_nurse_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("SELECT * FROM patients where state<1");

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_state_up_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    if (ui->radioButton_doctor->isChecked()) {
        query->setQuery("SELECT * FROM patients where state between 1 and 2 order by state");
    } else if (ui->radioButton_nurse->isChecked()) {
        query->setQuery("SELECT * FROM patients where state<1 order by state");
    } else {
    query->setQuery("SELECT * FROM patients order by state");
    }

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_state_down_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    if (ui->radioButton_doctor->isChecked()) {
        query->setQuery("SELECT * FROM patients where state between 1 and 2 order by state desc");
    } else if (ui->radioButton_nurse->isChecked()) {
        query->setQuery("SELECT * FROM patients where state<1 order by state desc");
    } else {
        query->setQuery("SELECT * FROM patients order by state desc");
    }

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_a_z_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    if (ui->radioButton_doctor->isChecked()) {
        query->setQuery("SELECT * FROM patients where state between 1 and 2 order by surname");
    } else if (ui->radioButton_nurse->isChecked()) {
        query->setQuery("SELECT * FROM patients where state<1 order by surname");
    } else {
        query->setQuery("SELECT * FROM patients order by surname");
    }

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_z_a_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    if (ui->radioButton_doctor->isChecked()) {
        query->setQuery("SELECT * FROM patients where state between 1 and 2 order by surname desc");
    } else if (ui->radioButton_nurse->isChecked()) {
        query->setQuery("SELECT * FROM patients where state<1 order by surname desc");
    } else {
        query->setQuery("SELECT * FROM patients order by surname desc");
    }

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_radioButton_both_clicked()
{
    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("SELECT * FROM patients");

    ui->tableView->setModel(query);
    ui->tableView->show();
}


void MainWindow::on_add_clicked()
{
    form_add->show();
}


void MainWindow::on_edit_clicked()
{
    form_edit->show();
}


void MainWindow::on_delete_2_clicked()
{
    form_delete->show();
}

void MainWindow::slotFormEdit(QVector<QString> vec)
{
    QSqlQuery qry;
    if (vec[0] != "") {
        qry.prepare("update patients set surname=:surname where id=:id");
        qry.bindValue(":surname", vec[0]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[1] != "") {
        qry.prepare("update patients set name=:name where id=:id");
        qry.bindValue(":name", vec[1]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[2] != "") {
        qry.prepare("update patients set patronymic=:patronymic where id=:id");
        qry.bindValue(":patronymic", vec[2]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[3] != "") {
        qry.prepare("update patients set age=:age where id=:id");
        qry.bindValue(":age", vec[3]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[4] != "") {
        qry.prepare("update patients set ward=:ward where id=:id");
        qry.bindValue(":ward", vec[4]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[5] != "") {
        qry.prepare("update patients set disease=:disease where id=:id");
        qry.bindValue(":disease", vec[5]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }
    if (vec[6] != "") {
        qry.prepare("update patients set state=:state where id=:id");
        qry.bindValue(":state", vec[6]);
        qry.bindValue(":id", vec[7]);
        qry.exec();
    }

    if (!qry.exec()) {
        qDebug() << "Error\n" << qry.lastError().text();
    } else {
        qDebug() << "OK\n" << "Successfull!\n";
    }
    form_edit->close();
    update();
}

void MainWindow::slotFormAdd(QVector<QString> vec)
{
    QSqlQuery qry;
    qry.prepare("insert into patients (surname, name, patronymic, age, ward, disease, state) values (:surname, :name, :patronymic, :age, :ward, :disease, :state)");
    qry.bindValue(":surname", vec[0]);
    qry.bindValue(":name", vec[1]);
    qry.bindValue(":patronymic", vec[2]);
    qry.bindValue(":age", vec[3]);
    qry.bindValue(":ward", vec[4]);
    qry.bindValue(":disease", vec[5]);
    qry.bindValue(":state", vec[6]);

    if (!qry.exec()) {
        qDebug() << "Error\n" << qry.lastError().text();
    } else {
        qDebug() << "OK\n" << "Successfull!\n";
    }
    form_add->close();
    update();
}

void MainWindow::slotFormDelete(int id)
{
    QSqlQuery qry;
    qry.prepare("delete from patients where id=:id");
    qry.bindValue(":id", id);

    if (!qry.exec()) {
        qDebug() << "Error\n" << qry.lastError().text();
    } else {
        qDebug() << "OK\n" << "Successfull!\n";
    }
    form_delete->close();
}


void MainWindow::on_add_sensors_clicked()
{
    form_add_sensors->show();
}

void MainWindow::slotFormAddSensors(int id, double state) {
    QSqlQuery qry;
    qry.prepare("update patients set state=:state where id=:id");
    qry.bindValue(":state", state);
    qry.bindValue(":id", id);
    qry.exec();
    if (!qry.exec()) {
        qDebug() << "Error\n" << qry.lastError().text();
    } else {
        qDebug() << "OK\n" << "Successfull!\n";
    }
    form_add_sensors->close();
    update();
}

void MainWindow::on_radioButton_urgent_clicked()
{

    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("SELECT * FROM patients where state>2");

    ui->tableView->setModel(query);
    ui->tableView->show();

}

