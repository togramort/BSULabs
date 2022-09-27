#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <iostream>
#include <fstream>
#include <map>
#include <boost/algorithm/string.hpp>

std::map<std::string, int> dict;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->radioButton,SIGNAL(clicked()), this, SLOT(on_radioButton_clicked()));
//    connect(ui->radioButton_2,SIGNAL(clicked()), this, SLOT(on_radioButton_2_clicked()));

    create_dict();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_correct(const std::string& word) {
  if (word.size() > 7) {
    for (auto i : word) {
      if (i == '.' || i == ')' || i == '(' || i == '/') {
        return false;
      }
    }
  }
  return true;
}

void MainWindow::create_dict() {
    std::ifstream in;
    in.open("D:\\program etc\\projects3\\f_dict\\input.txt");
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

//    for (auto& i : dict) {
//        ui->listWidget->addItem(QString::fromStdString(i.first) + "    :    " + QString::number(i.second));
//    }
}

void MainWindow::clear_listWidget() {
    while(ui->listWidget->count()>0) {
        ui->listWidget->takeItem(0);
    }
}

void MainWindow::on_radioButton_clicked() {
    clear_listWidget();
    for (auto& i : dict) {
        ui->listWidget->addItem(QString::fromStdString(i.first) + "\t:\t" + QString::number(i.second));
    }
}

void MainWindow::on_radioButton_2_clicked() {
    clear_listWidget();
    for (auto i = dict.rbegin(); i != dict.rend(); ++i) {
        ui->listWidget->addItem(QString::fromStdString(i->first) + "\t:\t" + QString::number(i->second));
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

    for (auto& i : vec) {
        ui->listWidget->addItem(QString::fromStdString(i.first) + "\t:\t " + QString::number(i.second));
    }
}

void MainWindow::sort_max_min(std::map<std::string, int>& map) {
    std::vector<std::pair<std::string, int>> vec;

    for (auto& i : map) {
        vec.push_back(i);
    }

    std::sort(vec.begin(), vec.end(), cmp_max_min);

    for (auto& i : vec) {
        ui->listWidget->addItem(QString::fromStdString(i.first) + "\t:\t" + QString::number(i.second));
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
        if (i.first.find((ui->lineEdit->text()).toStdString()) != std::string::npos && i.first.find((ui->lineEdit->text()).toStdString()) == 0) {
         ui->listWidget->addItem(QString::fromStdString(i.first) + "\t:\t" + QString::number(i.second));
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
    dialog = new Dialog(this);
    dialog->show();
    std::string temp = "qwe";
   // temp = dialog->on_pushButton_clicked_dial();
    std::cout << "dial show \n";
    std::cout << temp;

}

