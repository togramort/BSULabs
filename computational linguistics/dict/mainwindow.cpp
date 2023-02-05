#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->radioButton,SIGNAL(clicked()), this, SLOT(on_radioButton_clicked()));

    std::map<std::string, int> dict;
    std::ifstream in("input.txt");
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
        if (check_correct(word)) {
          dict.insert(std::pair<std::string, int>(word, 0));
          ++dict[word];
        }
      }
    }

    for (auto& i : dict) {
        area->addItem(i.first);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_clicked()
{
    std::cout << "yfbis";
}

