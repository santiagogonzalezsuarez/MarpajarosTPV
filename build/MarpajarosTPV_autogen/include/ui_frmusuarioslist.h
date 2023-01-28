/********************************************************************************
** Form generated from reading UI file 'frmusuarioslist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMUSUARIOSLIST_H
#define UI_FRMUSUARIOSLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_frmUsuariosList
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tblUsuarios;
    QVBoxLayout *verticalLayout;
    QPushButton *btnNuevo;
    QPushButton *btnModificar;
    QPushButton *btnEliminar;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtFiltroSearch;

    void setupUi(QDialog *frmUsuariosList)
    {
        if (frmUsuariosList->objectName().isEmpty())
            frmUsuariosList->setObjectName(QString::fromUtf8("frmUsuariosList"));
        frmUsuariosList->resize(548, 389);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        frmUsuariosList->setWindowIcon(icon);
        gridLayout = new QGridLayout(frmUsuariosList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tblUsuarios = new QTableWidget(frmUsuariosList);
        if (tblUsuarios->columnCount() < 5)
            tblUsuarios->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblUsuarios->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblUsuarios->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblUsuarios->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblUsuarios->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblUsuarios->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tblUsuarios->setObjectName(QString::fromUtf8("tblUsuarios"));
        tblUsuarios->setLineWidth(1);
        tblUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblUsuarios->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblUsuarios->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblUsuarios->horizontalHeader()->setStretchLastSection(true);
        tblUsuarios->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tblUsuarios, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnNuevo = new QPushButton(frmUsuariosList);
        btnNuevo->setObjectName(QString::fromUtf8("btnNuevo"));

        verticalLayout->addWidget(btnNuevo);

        btnModificar = new QPushButton(frmUsuariosList);
        btnModificar->setObjectName(QString::fromUtf8("btnModificar"));

        verticalLayout->addWidget(btnModificar);

        btnEliminar = new QPushButton(frmUsuariosList);
        btnEliminar->setObjectName(QString::fromUtf8("btnEliminar"));

        verticalLayout->addWidget(btnEliminar);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frmUsuariosList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(24, 24));
        label->setMaximumSize(QSize(24, 24));
        label->setStyleSheet(QString::fromUtf8("image: url(:/assets/search.png);"));

        horizontalLayout->addWidget(label);

        txtFiltroSearch = new QLineEdit(frmUsuariosList);
        txtFiltroSearch->setObjectName(QString::fromUtf8("txtFiltroSearch"));

        horizontalLayout->addWidget(txtFiltroSearch);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);


        retranslateUi(frmUsuariosList);
        QObject::connect(txtFiltroSearch, SIGNAL(textChanged(QString)), frmUsuariosList, SLOT(SearchChanged()));
        QObject::connect(frmUsuariosList, SIGNAL(rejected()), frmUsuariosList, SLOT(closeParent()));
        QObject::connect(btnNuevo, SIGNAL(clicked()), frmUsuariosList, SLOT(NuevoUsuario()));
        QObject::connect(btnModificar, SIGNAL(clicked()), frmUsuariosList, SLOT(ModificarUsuario()));
        QObject::connect(tblUsuarios, SIGNAL(cellDoubleClicked(int,int)), frmUsuariosList, SLOT(ModificarUsuario()));
        QObject::connect(btnEliminar, SIGNAL(clicked()), frmUsuariosList, SLOT(DeleteUsuarios()));

        QMetaObject::connectSlotsByName(frmUsuariosList);
    } // setupUi

    void retranslateUi(QDialog *frmUsuariosList)
    {
        frmUsuariosList->setWindowTitle(QCoreApplication::translate("frmUsuariosList", "Gesti\303\263n de usuarios", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblUsuarios->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("frmUsuariosList", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblUsuarios->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("frmUsuariosList", "Nombre de usuario", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblUsuarios->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("frmUsuariosList", "Nombre", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblUsuarios->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("frmUsuariosList", "Apellidos", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblUsuarios->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("frmUsuariosList", "Rol", nullptr));
        btnNuevo->setText(QCoreApplication::translate("frmUsuariosList", "&Nuevo", nullptr));
        btnModificar->setText(QCoreApplication::translate("frmUsuariosList", "&Modificar", nullptr));
        btnEliminar->setText(QCoreApplication::translate("frmUsuariosList", "&Eliminar", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmUsuariosList: public Ui_frmUsuariosList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMUSUARIOSLIST_H
