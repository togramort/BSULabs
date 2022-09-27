#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    bool check_correct(const std::string &word);
    void create_dict();
    void sort_min_max(std::map<std::string, int> &map);
    void sort_max_min(std::map<std::string, int> &map);
    void clear_listWidget();



private slots:

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *dialog;

};
#endif // MAINWINDOW_H
