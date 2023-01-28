/********************************************************************************
** Form generated from reading UI file 'frmsplash.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSPLASH_H
#define UI_FRMSPLASH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmSplash
{
public:
    QLabel *label;
    QWidget *widget;

    void setupUi(QDialog *frmSplash)
    {
        if (frmSplash->objectName().isEmpty())
            frmSplash->setObjectName(QString::fromUtf8("frmSplash"));
        frmSplash->resize(650, 390);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frmSplash->sizePolicy().hasHeightForWidth());
        frmSplash->setSizePolicy(sizePolicy);
        frmSplash->setMinimumSize(QSize(650, 390));
        frmSplash->setMaximumSize(QSize(650, 390));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/marpajaros.ico"), QSize(), QIcon::Normal, QIcon::Off);
        frmSplash->setWindowIcon(icon);
        label = new QLabel(frmSplash);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(219, 236, 431, 71));
        label->setStyleSheet(QString::fromUtf8("color: rgb(118, 0, 58);\n"
"font: italic 42pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);
        widget = new QWidget(frmSplash);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 650, 390));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/assets/LoginMarpajaros_650.png);"));
        widget->raise();
        label->raise();

        retranslateUi(frmSplash);

        QMetaObject::connectSlotsByName(frmSplash);
    } // setupUi

    void retranslateUi(QDialog *frmSplash)
    {
        frmSplash->setWindowTitle(QCoreApplication::translate("frmSplash", "Mar p\303\241jaros TPV - Splash", nullptr));
        label->setText(QCoreApplication::translate("frmSplash", "Mar p\303\241jaros TPV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmSplash: public Ui_frmSplash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSPLASH_H
