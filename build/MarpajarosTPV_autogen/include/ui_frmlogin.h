/********************************************************************************
** Form generated from reading UI file 'frmlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMLOGIN_H
#define UI_FRMLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmLogin
{
public:
    QLabel *lblNombreUsuario;
    QLabel *lblContrasena;
    QLineEdit *txtNombreUsuario;
    QLineEdit *txtContrasena;
    QPushButton *btnCancelar;
    QPushButton *btnAceptar;
    QWidget *widget;

    void setupUi(QDialog *frmLogin)
    {
        if (frmLogin->objectName().isEmpty())
            frmLogin->setObjectName(QString::fromUtf8("frmLogin"));
        frmLogin->resize(650, 390);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frmLogin->sizePolicy().hasHeightForWidth());
        frmLogin->setSizePolicy(sizePolicy);
        frmLogin->setMinimumSize(QSize(650, 390));
        frmLogin->setMaximumSize(QSize(650, 390));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/marpajaros.ico"), QSize(), QIcon::Normal, QIcon::Off);
        frmLogin->setWindowIcon(icon);
        frmLogin->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);\n"
""));
        lblNombreUsuario = new QLabel(frmLogin);
        lblNombreUsuario->setObjectName(QString::fromUtf8("lblNombreUsuario"));
        lblNombreUsuario->setGeometry(QRect(350, 50, 241, 17));
        lblNombreUsuario->setStyleSheet(QString::fromUtf8("font: 10pt \"Sans Serif\";"));
        lblContrasena = new QLabel(frmLogin);
        lblContrasena->setObjectName(QString::fromUtf8("lblContrasena"));
        lblContrasena->setGeometry(QRect(350, 110, 241, 17));
        lblContrasena->setStyleSheet(QString::fromUtf8("font: 10pt \"Sans Serif\";"));
        txtNombreUsuario = new QLineEdit(frmLogin);
        txtNombreUsuario->setObjectName(QString::fromUtf8("txtNombreUsuario"));
        txtNombreUsuario->setGeometry(QRect(350, 70, 241, 25));
        txtNombreUsuario->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit:disabled {\n"
"color: rgb(127,127,127);\n"
"}\n"
""));
        txtContrasena = new QLineEdit(frmLogin);
        txtContrasena->setObjectName(QString::fromUtf8("txtContrasena"));
        txtContrasena->setGeometry(QRect(350, 130, 241, 25));
        txtContrasena->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit:disabled {\n"
"color: rgb(127,127,127);\n"
"}\n"
""));
        txtContrasena->setEchoMode(QLineEdit::Password);
        btnCancelar = new QPushButton(frmLogin);
        btnCancelar->setObjectName(QString::fromUtf8("btnCancelar"));
        btnCancelar->setGeometry(QRect(350, 190, 111, 31));
        btnCancelar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(0, 0, 0);	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"QPushButton:disabled {\n"
"	color: rgb(127, 127, 127);\n"
"}\n"
""));
        btnAceptar = new QPushButton(frmLogin);
        btnAceptar->setObjectName(QString::fromUtf8("btnAceptar"));
        btnAceptar->setGeometry(QRect(480, 190, 111, 31));
        btnAceptar->setStyleSheet(QString::fromUtf8("QPushButton:disabled {\n"
"color: rgb(127, 127, 127);\n"
"}\n"
"QPushButton {\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
""));
        widget = new QWidget(frmLogin);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 650, 390));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/assets/LoginMarpajaros_650.png);"));
        widget->raise();
        lblNombreUsuario->raise();
        lblContrasena->raise();
        txtNombreUsuario->raise();
        txtContrasena->raise();
        btnCancelar->raise();
        btnAceptar->raise();
        QWidget::setTabOrder(txtNombreUsuario, txtContrasena);
        QWidget::setTabOrder(txtContrasena, btnAceptar);
        QWidget::setTabOrder(btnAceptar, btnCancelar);

        retranslateUi(frmLogin);
        QObject::connect(btnCancelar, SIGNAL(clicked()), frmLogin, SLOT(close()));
        QObject::connect(btnAceptar, SIGNAL(clicked()), frmLogin, SLOT(doLogin()));

        QMetaObject::connectSlotsByName(frmLogin);
    } // setupUi

    void retranslateUi(QDialog *frmLogin)
    {
        frmLogin->setWindowTitle(QCoreApplication::translate("frmLogin", "Mar p\303\241jaros TPV - Iniciar sesi\303\263n", nullptr));
        lblNombreUsuario->setText(QCoreApplication::translate("frmLogin", "Nombre de usuario:", nullptr));
        lblContrasena->setText(QCoreApplication::translate("frmLogin", "Contrase\303\261a:", nullptr));
        btnCancelar->setText(QCoreApplication::translate("frmLogin", "&Cancelar", nullptr));
        btnAceptar->setText(QCoreApplication::translate("frmLogin", "&Aceptar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmLogin: public Ui_frmLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMLOGIN_H
