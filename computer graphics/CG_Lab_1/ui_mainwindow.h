/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *l_rgb_r;
    QSpinBox *sb_hsv_h;
    QLabel *l_rgb_g;
    QSpinBox *sb_hsv_s;
    QLabel *l_rgb_b;
    QSpinBox *sb_hsv_v;
    QWidget *layoutWidget_3;
    QFormLayout *formLayout_3;
    QSpinBox *sb_lab_l;
    QSpinBox *sb_lab_a;
    QLabel *l_lab_b;
    QSpinBox *sb_lab_b;
    QLabel *l_lab_l;
    QLabel *l_lab_a;
    QWidget *layoutWidget_4;
    QFormLayout *formLayout_4;
    QLabel *l_cmyk_c;
    QSpinBox *sb_cmyk_c;
    QLabel *l_cmyk_m;
    QSpinBox *sb_cmyk_m;
    QLabel *l_cmyk_y;
    QSpinBox *sb_cmyk_y;
    QLabel *l_cmyk_k;
    QSpinBox *sb_cmyk_k;
    QPushButton *b_pick_color;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(516, 346);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(40, 40, 141, 136));
        formLayout_2 = new QFormLayout(layoutWidget_2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        l_rgb_r = new QLabel(layoutWidget_2);
        l_rgb_r->setObjectName("l_rgb_r");
        QFont font;
        font.setPointSize(14);
        l_rgb_r->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, l_rgb_r);

        sb_hsv_h = new QSpinBox(layoutWidget_2);
        sb_hsv_h->setObjectName("sb_hsv_h");
        sb_hsv_h->setFont(font);
        sb_hsv_h->setMaximum(360);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, sb_hsv_h);

        l_rgb_g = new QLabel(layoutWidget_2);
        l_rgb_g->setObjectName("l_rgb_g");
        l_rgb_g->setFont(font);
        l_rgb_g->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, l_rgb_g);

        sb_hsv_s = new QSpinBox(layoutWidget_2);
        sb_hsv_s->setObjectName("sb_hsv_s");
        sb_hsv_s->setFont(font);
        sb_hsv_s->setMaximum(100);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, sb_hsv_s);

        l_rgb_b = new QLabel(layoutWidget_2);
        l_rgb_b->setObjectName("l_rgb_b");
        l_rgb_b->setFont(font);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, l_rgb_b);

        sb_hsv_v = new QSpinBox(layoutWidget_2);
        sb_hsv_v->setObjectName("sb_hsv_v");
        sb_hsv_v->setFont(font);
        sb_hsv_v->setMaximum(100);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, sb_hsv_v);

        layoutWidget_3 = new QWidget(centralwidget);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(200, 40, 141, 136));
        formLayout_3 = new QFormLayout(layoutWidget_3);
        formLayout_3->setObjectName("formLayout_3");
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        sb_lab_l = new QSpinBox(layoutWidget_3);
        sb_lab_l->setObjectName("sb_lab_l");
        sb_lab_l->setFont(font);
        sb_lab_l->setMaximum(100);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, sb_lab_l);

        sb_lab_a = new QSpinBox(layoutWidget_3);
        sb_lab_a->setObjectName("sb_lab_a");
        sb_lab_a->setFont(font);
        sb_lab_a->setMinimum(-128);
        sb_lab_a->setMaximum(128);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, sb_lab_a);

        l_lab_b = new QLabel(layoutWidget_3);
        l_lab_b->setObjectName("l_lab_b");
        l_lab_b->setFont(font);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, l_lab_b);

        sb_lab_b = new QSpinBox(layoutWidget_3);
        sb_lab_b->setObjectName("sb_lab_b");
        sb_lab_b->setFont(font);
        sb_lab_b->setMinimum(-128);
        sb_lab_b->setMaximum(128);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, sb_lab_b);

        l_lab_l = new QLabel(layoutWidget_3);
        l_lab_l->setObjectName("l_lab_l");
        l_lab_l->setFont(font);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, l_lab_l);

        l_lab_a = new QLabel(layoutWidget_3);
        l_lab_a->setObjectName("l_lab_a");
        l_lab_a->setFont(font);
        l_lab_a->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, l_lab_a);

        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(360, 40, 141, 183));
        formLayout_4 = new QFormLayout(layoutWidget_4);
        formLayout_4->setObjectName("formLayout_4");
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        l_cmyk_c = new QLabel(layoutWidget_4);
        l_cmyk_c->setObjectName("l_cmyk_c");
        l_cmyk_c->setFont(font);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, l_cmyk_c);

        sb_cmyk_c = new QSpinBox(layoutWidget_4);
        sb_cmyk_c->setObjectName("sb_cmyk_c");
        sb_cmyk_c->setFont(font);
        sb_cmyk_c->setMaximum(100);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, sb_cmyk_c);

        l_cmyk_m = new QLabel(layoutWidget_4);
        l_cmyk_m->setObjectName("l_cmyk_m");
        l_cmyk_m->setFont(font);
        l_cmyk_m->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_4->setWidget(1, QFormLayout::LabelRole, l_cmyk_m);

        sb_cmyk_m = new QSpinBox(layoutWidget_4);
        sb_cmyk_m->setObjectName("sb_cmyk_m");
        sb_cmyk_m->setFont(font);
        sb_cmyk_m->setMaximum(100);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, sb_cmyk_m);

        l_cmyk_y = new QLabel(layoutWidget_4);
        l_cmyk_y->setObjectName("l_cmyk_y");
        l_cmyk_y->setFont(font);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, l_cmyk_y);

        sb_cmyk_y = new QSpinBox(layoutWidget_4);
        sb_cmyk_y->setObjectName("sb_cmyk_y");
        sb_cmyk_y->setFont(font);
        sb_cmyk_y->setMaximum(100);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, sb_cmyk_y);

        l_cmyk_k = new QLabel(layoutWidget_4);
        l_cmyk_k->setObjectName("l_cmyk_k");
        l_cmyk_k->setFont(font);

        formLayout_4->setWidget(3, QFormLayout::LabelRole, l_cmyk_k);

        sb_cmyk_k = new QSpinBox(layoutWidget_4);
        sb_cmyk_k->setObjectName("sb_cmyk_k");
        sb_cmyk_k->setFont(font);
        sb_cmyk_k->setMaximum(100);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, sb_cmyk_k);

        b_pick_color = new QPushButton(centralwidget);
        b_pick_color->setObjectName("b_pick_color");
        b_pick_color->setGeometry(QRect(360, 220, 141, 81));
        b_pick_color->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 516, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setEnabled(false);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        l_rgb_r->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        l_rgb_g->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        l_rgb_b->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        l_lab_b->setText(QCoreApplication::translate("MainWindow", "b", nullptr));
        l_lab_l->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        l_lab_a->setText(QCoreApplication::translate("MainWindow", "a", nullptr));
        l_cmyk_c->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        l_cmyk_m->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        l_cmyk_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        l_cmyk_k->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
        b_pick_color->setText(QCoreApplication::translate("MainWindow", "Pick color", nullptr));
    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
