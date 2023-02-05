#ifndef FORM_EDIT_H
#define FORM_EDIT_H

#include <QDialog>

namespace Ui {
class form_edit;
}

class form_edit : public QDialog
{
    Q_OBJECT

public:
    explicit form_edit(QWidget *parent = nullptr);
    ~form_edit();

private:
    Ui::form_edit *ui;

signals:
    void signalForm(QVector<QString> vec);
private slots:
    void on_pushButton_done_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // FORM_EDIT_H
