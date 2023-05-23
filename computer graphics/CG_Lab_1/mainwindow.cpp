#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QColorDialog>
#include <QMessageBox>
#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(550, 350);
    ui->setupUi(this);

    cd_pick_color.setOptions(cd_pick_color.options() | QColorDialog::DontUseNativeDialog);

//    for(QObject* const pChild : cd_pick_color.children()) {
//        if (!pChild->isWidgetType()) {
//            continue;
//        }
//        QWidget* const pWid = (QWidget* const)pChild;
//        std::string cName = pWid->metaObject()->className();

//        if (cName != "QColorPicker" && cName != "QColorLuminancePicker") {
//            pWid->hide();
//        }

//    }

    XYZw.X = 95.047;
    XYZw.Y = 100;
    XYZw.Z = 108.883;

    QObject::connect(&this->cd_pick_color, SIGNAL(currentColorChanged(const QColor &)), this, SLOT(on_colorChanged(const QColor &)));
    QObject::connect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::connect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
    QObject::connect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);
    const QColor backgroundColor(255, 255, 255);
    painter.fillRect(event->rect(), backgroundColor);
    QColor c;
    c.setHsv(ui->sb_hsv_h->value(), ui->sb_hsv_s->value() * 2.55, ui->sb_hsv_v->value() * 2.55);
    QBrush brush(c);
    painter.setBrush(brush);
    painter.drawRect(QRect(50, 180, 230, 120));
}

double MainWindow::RGB_to_XYZ_func(double x) {
    if (x >= 0.04045) {
        return std::pow((x+0.055)/1.055, 2.4);
    }
    else {
        return x / 12.92;
    }
}

double MainWindow::XYZ_to_RGB_func(double x) {
    if (x >= 0.0031308) {
        return 1.055 * std::pow(x, 1/2.4) - 0.055;
    }
    else {
        return x * 12.92;
    }
}

double MainWindow::XYZ_to_Lab_func(double x) {
    if (x >= 0.008856) {
        return std::pow(x, 1./3);
    }
    else {
        return 7.787 * x + 16./116;
    }
}

double MainWindow::Lab_to_XYZ_func(double x) {
    if (std::pow(x, 3) >= 0.008856) {
        return std::pow(x, 3);
    }
    else {
        return (x - 16./116) / 7.787;
    }
}


Color MainWindow::RGB_to_Lab(const QColor &color) {
    Color RGBn;
    RGBn.X = RGB_to_XYZ_func(color.redF()) * 100;
    RGBn.Y = RGB_to_XYZ_func(color.greenF()) * 100;
    RGBn.Z = RGB_to_XYZ_func(color.blueF()) * 100;

    Color XYZc;
    XYZc.X = 0.412453 * RGBn.X + 0.35758 * RGBn.Y + 0.180423 * RGBn.Z;
    XYZc.Y = 0.212671 * RGBn.X + 0.71516 * RGBn.Y + 0.072169 * RGBn.Z;
    XYZc.Z = 0.019334 * RGBn.X + 0.119193 * RGBn.Y + 0.950227 * RGBn.Z;

    Color Lab;
    Lab.X = 116 * XYZ_to_Lab_func(XYZc.Y / XYZw.Y) - 16;
    Lab.Y = 500 * (XYZ_to_Lab_func(XYZc.X / XYZw.X) - XYZ_to_Lab_func(XYZc.Y / XYZw.Y));
    Lab.Z = 200 * (XYZ_to_Lab_func(XYZc.Y / XYZw.Y) - XYZ_to_Lab_func(XYZc.Z / XYZw.Z));

    return Lab;
}

QColor MainWindow::Lab_to_RGB(const Color &color) {
    Color XYZc;
    XYZc.Y = Lab_to_XYZ_func((color.X + 16)/116) * XYZw.X / 100;
    XYZc.X = Lab_to_XYZ_func(color.Y / 500 + (color.X + 16) / 116) * XYZw.Y / 100;
    XYZc.Z = Lab_to_XYZ_func((color.X + 16) / 116 - color.Z / 200) * XYZw.Z / 100;

    Color RGBn;
    RGBn.X = 3.2406 * XYZc.X - 1.5372 * XYZc.Y - 0.4986 * XYZc.Z;
    RGBn.Y = -0.9689 * XYZc.X + 1.8758 * XYZc.Y + 0.0415 * XYZc.Z;
    RGBn.Z = 0.0557 * XYZc.X - 0.2040 * XYZc.Y + 1.0570 * XYZc.Z;

    QColor RGB (XYZ_to_RGB_func(RGBn.X) * 255,
               XYZ_to_RGB_func(RGBn.Y) * 255,
               XYZ_to_RGB_func(RGBn.Z) * 255
               );

    return RGB;
}

void MainWindow::on_colorChanged(const QColor &color) {
    QObject::disconnect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::disconnect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
    QObject::disconnect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));

    ui->sb_hsv_h->setValue(color.hue());
    ui->sb_hsv_s->setValue(color.saturation());
    ui->sb_hsv_v->setValue(color.value());

    ui->sb_cmyk_c->setValue(color.cyan());
    ui->sb_cmyk_m->setValue(color.magenta());
    ui->sb_cmyk_y->setValue(color.yellow());
    ui->sb_cmyk_k->setValue(color.black());

    Color c = RGB_to_Lab(color);
    ui->sb_lab_l->setValue(c.X);
    ui->sb_lab_a->setValue(c.Y);
    ui->sb_lab_b->setValue(c.Z);

    this->update();

    QObject::connect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::connect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
    QObject::connect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));
}

void MainWindow::on_hsvChanged(const QColor &color) {
    QObject::disconnect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
    QObject::disconnect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));

    ui->sb_cmyk_c->setValue(color.cyan());
    ui->sb_cmyk_m->setValue(color.magenta());
    ui->sb_cmyk_y->setValue(color.yellow());
    ui->sb_cmyk_k->setValue(color.black());

    Color c = RGB_to_Lab(color);
    ui->sb_lab_l->setValue(c.X);
    ui->sb_lab_a->setValue(c.Y);
    ui->sb_lab_b->setValue(c.Z);

    this->update();

    QObject::connect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
    QObject::connect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));
}

void MainWindow::on_cmykChanged(const QColor &color) {
    QObject::disconnect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::disconnect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));

    ui->sb_hsv_h->setValue(color.hue());
    ui->sb_hsv_s->setValue(color.saturation());
    ui->sb_hsv_v->setValue(color.value());

    Color c = RGB_to_Lab(color);
    ui->sb_lab_l->setValue(c.X);
    ui->sb_lab_a->setValue(c.Y);
    ui->sb_lab_b->setValue(c.Z);

    this->update();

    QObject::connect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::connect(this, SIGNAL(lab_changed(const Color &)), this, SLOT(on_labChanged(const Color &)));
}

void MainWindow::on_labChanged(const Color &color) {
    QObject::disconnect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::disconnect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));

    QColor c = Lab_to_RGB(color);
    ui->sb_hsv_h->setValue(c.hue());
    ui->sb_hsv_s->setValue(c.saturation());
    ui->sb_hsv_v->setValue(c.value());

    ui->sb_cmyk_c->setValue(c.cyan());
    ui->sb_cmyk_m->setValue(c.magenta());
    ui->sb_cmyk_y->setValue(c.yellow());
    ui->sb_cmyk_k->setValue(c.black());

    this->update();

    QObject::connect(this, SIGNAL(hsv_changed(const QColor &)), this, SLOT(on_hsvChanged(const QColor &)));
    QObject::connect(this, SIGNAL(cmyk_changed(const QColor &)), this, SLOT(on_cmykChanged(const QColor &)));
}

void MainWindow::on_b_pick_color_clicked()
{
    this->cd_pick_color.show();
}


void MainWindow::on_sb_cmyk_c_valueChanged(int arg1)
{
    emit cmyk_changed(QColor::fromCmyk(arg1, ui->sb_cmyk_m->value(), ui->sb_cmyk_y->value(), ui->sb_cmyk_k->value()));
}


void MainWindow::on_sb_cmyk_m_valueChanged(int arg1)
{
    emit cmyk_changed(QColor::fromCmyk(ui->sb_cmyk_c->value(), arg1, ui->sb_cmyk_y->value(), ui->sb_cmyk_k->value()));
}


void MainWindow::on_sb_cmyk_y_valueChanged(int arg1)
{
    emit cmyk_changed(QColor::fromCmyk(ui->sb_cmyk_c->value(), ui->sb_cmyk_m->value(), arg1, ui->sb_cmyk_k->value()));
}


void MainWindow::on_sb_cmyk_k_valueChanged(int arg1)
{
    emit cmyk_changed(QColor::fromCmyk(ui->sb_cmyk_c->value(), ui->sb_cmyk_m->value(), ui->sb_cmyk_y->value(), arg1));
}


void MainWindow::on_sb_lab_l_valueChanged(int arg1)
{
    Color c;
    c.X = arg1;
    c.Y = ui->sb_lab_a->value();
    c.Z = ui->sb_lab_b->value();
    emit lab_changed(c);
}


void MainWindow::on_sb_lab_a_valueChanged(int arg1)
{
    Color c;
    c.X = ui->sb_lab_l->value();
    c.Y = arg1;
    c.Z = ui->sb_lab_b->value();
    emit lab_changed(c);
}


void MainWindow::on_sb_lab_b_valueChanged(int arg1)
{
    Color c;
    c.X = ui->sb_lab_l->value();
    c.Y = ui->sb_lab_a->value();
    c.Z = arg1;
    emit lab_changed(c);
}


void MainWindow::on_sb_hsv_h_valueChanged(int arg1)
{
    emit hsv_changed(QColor(arg1, ui->sb_hsv_s->value(), ui->sb_hsv_v->value()));
}


void MainWindow::on_sb_hsv_s_valueChanged(int arg1)
{
    emit hsv_changed(QColor(ui->sb_hsv_h->value(), arg1, ui->sb_hsv_v->value()));
}


void MainWindow::on_sb_hsv_v_valueChanged(int arg1)
{
    emit hsv_changed(QColor(ui->sb_hsv_h->value(), ui->sb_hsv_s->value(), arg1));
}
