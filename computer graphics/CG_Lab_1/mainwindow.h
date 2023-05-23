#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcolordialog.h"
#include <QMainWindow>

struct Color {
    double X;
    double Y;
    double Z;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    Color RGB_to_Lab(const QColor &color);
    QColor Lab_to_RGB(const Color &color);
private slots:
    void on_b_pick_color_clicked();
    void on_colorChanged(const QColor &color);
    void on_hsvChanged(const QColor &color);
    void on_cmykChanged(const QColor &color);
    void on_labChanged(const Color &color);
    void on_sb_cmyk_c_valueChanged(int arg1);
    void on_sb_cmyk_m_valueChanged(int arg1);
    void on_sb_cmyk_y_valueChanged(int arg1);
    void on_sb_cmyk_k_valueChanged(int arg1);
    void on_sb_lab_l_valueChanged(int arg1);
    void on_sb_lab_a_valueChanged(int arg1);
    void on_sb_lab_b_valueChanged(int arg1);
    void on_sb_hsv_h_valueChanged(int arg1);
    void on_sb_hsv_s_valueChanged(int arg1);
    void on_sb_hsv_v_valueChanged(int arg1);

signals:
    void hsv_changed(const QColor &color);
    void cmyk_changed(const QColor &color);
    void lab_changed(const Color &color);
private:
    Color XYZw;
    double RGB_to_XYZ_func(double x);
    double XYZ_to_Lab_func(double x);
    double Lab_to_XYZ_func(double x);
    double XYZ_to_RGB_func(double x);
    Ui::MainWindow *ui;
    QColorDialog cd_pick_color;
};
#endif // MAINWINDOW_H
