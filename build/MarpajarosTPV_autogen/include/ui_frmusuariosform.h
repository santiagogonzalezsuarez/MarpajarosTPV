/********************************************************************************
** Form generated from reading UI file 'frmusuariosform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMUSUARIOSFORM_H
#define UI_FRMUSUARIOSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_frmUsuariosForm
{
public:
    QGridLayout *gridLayout;
    QLabel *lblNombre;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancelar;
    QPushButton *btnAceptar;
    QLabel *lblApellidos;
    QLabel *lblContrasena;
    QLineEdit *txtUsuario;
    QLabel *lblRol;
    QLabel *lblUsuario;
    QLineEdit *txtContrasena;
    QLineEdit *txtNombre;
    QLineEdit *txtApellidos;
    QComboBox *cmbRol;

    void setupUi(QDialog *frmUsuariosForm)
    {
        if (frmUsuariosForm->objectName().isEmpty())
            frmUsuariosForm->setObjectName(QString::fromUtf8("frmUsuariosForm"));
        frmUsuariosForm->resize(363, 206);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        frmUsuariosForm->setWindowIcon(icon);
        gridLayout = new QGridLayout(frmUsuariosForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblNombre = new QLabel(frmUsuariosForm);
        lblNombre->setObjectName(QString::fromUtf8("lblNombre"));

        gridLayout->addWidget(lblNombre, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCancelar = new QPushButton(frmUsuariosForm);
        btnCancelar->setObjectName(QString::fromUtf8("btnCancelar"));

        horizontalLayout->addWidget(btnCancelar);

        btnAceptar = new QPushButton(frmUsuariosForm);
        btnAceptar->setObjectName(QString::fromUtf8("btnAceptar"));

        horizontalLayout->addWidget(btnAceptar);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 3);

        lblApellidos = new QLabel(frmUsuariosForm);
        lblApellidos->setObjectName(QString::fromUtf8("lblApellidos"));

        gridLayout->addWidget(lblApellidos, 3, 0, 1, 1);

        lblContrasena = new QLabel(frmUsuariosForm);
        lblContrasena->setObjectName(QString::fromUtf8("lblContrasena"));

        gridLayout->addWidget(lblContrasena, 1, 0, 1, 1);

        txtUsuario = new QLineEdit(frmUsuariosForm);
        txtUsuario->setObjectName(QString::fromUtf8("txtUsuario"));

        gridLayout->addWidget(txtUsuario, 0, 2, 1, 1);

        lblRol = new QLabel(frmUsuariosForm);
        lblRol->setObjectName(QString::fromUtf8("lblRol"));

        gridLayout->addWidget(lblRol, 4, 0, 1, 1);

        lblUsuario = new QLabel(frmUsuariosForm);
        lblUsuario->setObjectName(QString::fromUtf8("lblUsuario"));

        gridLayout->addWidget(lblUsuario, 0, 0, 1, 1);

        txtContrasena = new QLineEdit(frmUsuariosForm);
        txtContrasena->setObjectName(QString::fromUtf8("txtContrasena"));
        txtContrasena->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(txtContrasena, 1, 2, 1, 1);

        txtNombre = new QLineEdit(frmUsuariosForm);
        txtNombre->setObjectName(QString::fromUtf8("txtNombre"));

        gridLayout->addWidget(txtNombre, 2, 2, 1, 1);

        txtApellidos = new QLineEdit(frmUsuariosForm);
        txtApellidos->setObjectName(QString::fromUtf8("txtApellidos"));

        gridLayout->addWidget(txtApellidos, 3, 2, 1, 1);

        cmbRol = new QComboBox(frmUsuariosForm);
        cmbRol->setObjectName(QString::fromUtf8("cmbRol"));

        gridLayout->addWidget(cmbRol, 4, 2, 1, 1);

        QWidget::setTabOrder(txtUsuario, txtContrasena);
        QWidget::setTabOrder(txtContrasena, txtNombre);
        QWidget::setTabOrder(txtNombre, txtApellidos);
        QWidget::setTabOrder(txtApellidos, cmbRol);
        QWidget::setTabOrder(cmbRol, btnAceptar);
        QWidget::setTabOrder(btnAceptar, btnCancelar);

        retranslateUi(frmUsuariosForm);
        QObject::connect(btnCancelar, SIGNAL(clicked()), frmUsuariosForm, SLOT(reject()));
        QObject::connect(frmUsuariosForm, SIGNAL(rejected()), frmUsuariosForm, SLOT(closeParent()));
        QObject::connect(btnAceptar, SIGNAL(clicked()), frmUsuariosForm, SLOT(SaveUsuario()));

        btnAceptar->setDefault(true);


        QMetaObject::connectSlotsByName(frmUsuariosForm);
    } // setupUi

    void retranslateUi(QDialog *frmUsuariosForm)
    {
        frmUsuariosForm->setWindowTitle(QCoreApplication::translate("frmUsuariosForm", "Nuevo usuario", nullptr));
        lblNombre->setText(QCoreApplication::translate("frmUsuariosForm", "Nombre:", nullptr));
        btnCancelar->setText(QCoreApplication::translate("frmUsuariosForm", "&Cancelar", nullptr));
        btnAceptar->setText(QCoreApplication::translate("frmUsuariosForm", "&Aceptar", nullptr));
        lblApellidos->setText(QCoreApplication::translate("frmUsuariosForm", "Apellidos:", nullptr));
        lblContrasena->setText(QCoreApplication::translate("frmUsuariosForm", "Contrase\303\261a:", nullptr));
        lblRol->setText(QCoreApplication::translate("frmUsuariosForm", "Rol:", nullptr));
        lblUsuario->setText(QCoreApplication::translate("frmUsuariosForm", "Nombre de usuario:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmUsuariosForm: public Ui_frmUsuariosForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMUSUARIOSFORM_H
