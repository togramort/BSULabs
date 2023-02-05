#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <map>
#include <boost/algorithm/string.hpp>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QMessageBox>

std::map<std::string, int> dict;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_dict();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_correct(const std::string& word) {
    for (auto i : word) {
        if (i == '.' || i == ')' || i == '(' || i == '/' || i == '"' || i == ',' || i == '!' || i == '?') {
            return false;
        }
    }
  return true;
}

void save_dictionary() {
    std::ofstream out;
    out.open("D:\\program etc\\projects3\\f_dict\\output.txt");
    for(auto& i : dict) {
        out << i.first << "\n";
    }
}

void MainWindow::create_dict() {
    std::ifstream in;
    in.open("D:\\program etc\\projects3\\f_dict\\input4.txt");
    std::string word;
    if (in.is_open()) {
      while (in >> word) {
        boost::to_lower(word);
        while ((word[0] < 97 || word[0] > 122) && word[0] != 0) {
          word.erase(word.begin());
        }
        while ((word[word.size() - 1] < 97 || word[word.size() - 1] > 122) && !word.empty() && word[word.size() - 1] != 39) {
          word.erase(word.size() - 1);
        }
        if (check_correct(word) && word.size() != 0) {
          dict.insert(std::pair<std::string, int>(word, 0));
          ++dict[word];
        }
      }
    }
    in.close();
    save_dictionary();
}

void MainWindow::clear_listWidget() {
    while(ui->listWidget->count()>0) {
        ui->listWidget->takeItem(0);
    }
}

void MainWindow::on_radioButton_clicked() {
    clear_listWidget();

    if (ui->lineEdit->isModified()) {
        for (auto& i : dict) {
            if (i.first.find((ui->lineEdit->text()).toStdString()) != std::string::npos && i.first.find((ui->lineEdit->text()).toStdString()) == 0) {
                ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t" + QString::number(i.second));
            }
        }
    } else {
        for (auto& i : dict) {
            ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t" + QString::number(i.second));
        }
    }
}

void MainWindow::on_radioButton_2_clicked() {
    clear_listWidget();
    for (auto i = dict.rbegin(); i != dict.rend(); ++i) {
        ui->listWidget->addItem(QString::fromStdString(i->first) + "\t\t:\t" + QString::number(i->second));
    }
}

bool cmp_min_max(std::pair<std::string, int>& a, std::pair<std::string,int>& b) {
    return a.second != b.second ? a.second < b.second : a.first < b.first;
}

bool cmp_max_min(std::pair<std::string, int>& a, std::pair<std::string,int>& b) {
    return a.second != b.second ? a.second > b.second : a.first < b.first;
}

void MainWindow::sort_min_max(std::map<std::string, int>& map) {
    std::vector<std::pair<std::string, int>> vec;

    for (auto& i : map) {
        vec.push_back(i);
    }

    std::sort(vec.begin(), vec.end(), cmp_min_max);

    if (ui->lineEdit->isModified()) {
        for (auto& i : vec) {
            if (i.first.find((ui->lineEdit->text()).toStdString()) != std::string::npos && i.first.find((ui->lineEdit->text()).toStdString()) == 0) {
                ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t " + QString::number(i.second));
            }
        }
    } else {
        for (auto& i : vec) {
            ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t " + QString::number(i.second));
        }
    }
}

void MainWindow::sort_max_min(std::map<std::string, int>& map) {
    std::vector<std::pair<std::string, int>> vec;

    for (auto& i : map) {
        vec.push_back(i);
    }

    std::ofstream out;
    out.open("D:\\program etc\\projects3\\f_dict\\output_freq.txt");
    int temp;
    //temp = (i.second);
    //out << temp << "\n";

    std::sort(vec.begin(), vec.end(), cmp_max_min);
    if (ui->lineEdit->isModified()) {
        for (auto& i : vec) {
            if (i.first.find((ui->lineEdit->text()).toStdString()) != std::string::npos && i.first.find((ui->lineEdit->text()).toStdString()) == 0) {
                ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t" + QString::number(i.second));
            }
        }
    } else {
        for (auto& i : vec) {
            ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t" + QString::number(i.second));
        }
    }
}

void MainWindow::on_radioButton_3_clicked() {
    clear_listWidget();
    sort_min_max(dict);
}

void MainWindow::on_radioButton_4_clicked() {
    clear_listWidget();
    sort_max_min(dict);
}

void MainWindow::on_lineEdit_editingFinished() {
    clear_listWidget();
    for (auto& i : dict) {
        if (i.first.find((ui->lineEdit->text()).toStdString()) != std::string::npos) {
         ui->listWidget->addItem(QString::fromStdString(i.first) + "\t\t:\t" + QString::number(i.second));
        }
      }
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
}

void MainWindow::on_pushButton_clicked() {
    std::string temp;
    QString input = QInputDialog::getText(this, "Add word", "Enter");
    temp = input.toStdString();

    if (dict.find(temp) != dict.end()) {
        QMessageBox::critical(this, "nonono", "please notice, this word is already in the dictionary");
    } else {
        dict.insert(std::pair<std::string, int>(temp, 0));
        std::ofstream in;
        in.open("D:\\program etc\\projects3\\f_dict\\input.txt", std::ios::app);
        in << "\n" << temp;
    }
    save_dictionary();
}

void MainWindow::on_pushButton_2_clicked() {
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Editor"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QString label = QString("Word to edit").arg(0);
    form.addRow(label, lineEdit);
    fields << lineEdit;

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    QString label2 = QString("New word").arg(0);
    form.addRow(label2, lineEdit2);
    fields << lineEdit2;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        foreach(QLineEdit * lineEdit, fields) {
            qDebug() << lineEdit->text();
        }
    }
    std::string word_change, new_word;
    word_change = (lineEdit->text()).toStdString();
    new_word = (lineEdit2->text()).toStdString();
    auto it = dict.find(word_change);
    if (it == dict.end()) {
         QMessageBox::critical(this, "oopsie!", "please notice, there is no such word in the dictionary");
    }
    else if (it != dict.end()) {
        dict.emplace(new_word, it->second);
        dict.erase(it);
    }
    save_dictionary();
}


void MainWindow::on_pushButton_3_clicked() {
    std::string temp;
    QString input = QInputDialog::getText(this, "Delete word", "Enter");
    temp = input.toStdString();
    auto it = dict.find(temp);
    if (it == dict.end()) {
        QMessageBox::critical(this, "nonono", "please notice, there is no such word in the dictionary");
    } else if (it != dict.end()) {
        QMessageBox::warning(this, "ATTENTION!", "You sure tou want to delete this?", QMessageBox::Yes | QMessageBox::No);
            if (QMessageBox::Yes) {
               dict.erase(it);
            } else if (QMessageBox::No) {
                this->close();
            }
    }
    save_dictionary();
}
