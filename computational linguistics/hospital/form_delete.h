#ifndef FORM_DELETE_H
#define FORM_DELETE_H

#include <QDialog>

namespace Ui {
class form_delete;
}

class form_delete : public QDialog
{
    Q_OBJECT

public:
    explicit form_delete(QWidget *parent = nullptr);
    ~form_delete();

private:
    Ui::form_delete *ui;

signals:
    void signalForm(int id);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // FORM_DELETE_H
