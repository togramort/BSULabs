#ifndef FORM_ADD_H
#define FORM_ADD_H

#include <QDialog>

namespace Ui {
class form_add;
}

class form_add : public QDialog
{
    Q_OBJECT

public:
    explicit form_add(QWidget *parent = nullptr);
    ~form_add();

private:
    Ui::form_add *ui;

signals:
    void signalForm(QVector<QString> vec);
private slots:
    void on_pushButton_done_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // FORM_ADD_H
