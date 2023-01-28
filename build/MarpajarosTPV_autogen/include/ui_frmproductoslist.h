/********************************************************************************
** Form generated from reading UI file 'frmproductoslist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMPRODUCTOSLIST_H
#define UI_FRMPRODUCTOSLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
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

class Ui_frmProductosList
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *btnNuevo;
    QPushButton *btnModificar;
    QPushButton *btnEliminar;
    QSpacerItem *verticalSpacer;
    QGraphicsView *grImagen;
    QTableWidget *tblProductos;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtFiltroSearch;

    void setupUi(QDialog *frmProductosList)
    {
        if (frmProductosList->objectName().isEmpty())
            frmProductosList->setObjectName(QString::fromUtf8("frmProductosList"));
        frmProductosList->resize(980, 580);
        frmProductosList->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/productos.png"), QSize(), QIcon::Normal, QIcon::Off);
        frmProductosList->setWindowIcon(icon);
        gridLayout = new QGridLayout(frmProductosList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnNuevo = new QPushButton(frmProductosList);
        btnNuevo->setObjectName(QString::fromUtf8("btnNuevo"));

        verticalLayout->addWidget(btnNuevo);

        btnModificar = new QPushButton(frmProductosList);
        btnModificar->setObjectName(QString::fromUtf8("btnModificar"));

        verticalLayout->addWidget(btnModificar);

        btnEliminar = new QPushButton(frmProductosList);
        btnEliminar->setObjectName(QString::fromUtf8("btnEliminar"));

        verticalLayout->addWidget(btnEliminar);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        grImagen = new QGraphicsView(frmProductosList);
        grImagen->setObjectName(QString::fromUtf8("grImagen"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grImagen->sizePolicy().hasHeightForWidth());
        grImagen->setSizePolicy(sizePolicy);
        grImagen->setMaximumSize(QSize(150, 250));

        verticalLayout->addWidget(grImagen);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        tblProductos = new QTableWidget(frmProductosList);
        if (tblProductos->columnCount() < 8)
            tblProductos->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblProductos->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tblProductos->setObjectName(QString::fromUtf8("tblProductos"));
        tblProductos->setLineWidth(1);
        tblProductos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tblProductos->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblProductos->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblProductos->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblProductos->setShowGrid(true);
        tblProductos->setSortingEnabled(false);
        tblProductos->horizontalHeader()->setMinimumSectionSize(38);
        tblProductos->horizontalHeader()->setStretchLastSection(true);
        tblProductos->verticalHeader()->setVisible(false);
        tblProductos->verticalHeader()->setMinimumSectionSize(21);
        tblProductos->verticalHeader()->setDefaultSectionSize(30);

        gridLayout->addWidget(tblProductos, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frmProductosList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(24, 24));
        label->setStyleSheet(QString::fromUtf8("image: url(:/assets/search.png);"));

        horizontalLayout->addWidget(label);

        txtFiltroSearch = new QLineEdit(frmProductosList);
        txtFiltroSearch->setObjectName(QString::fromUtf8("txtFiltroSearch"));

        horizontalLayout->addWidget(txtFiltroSearch);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);


        retranslateUi(frmProductosList);
        QObject::connect(frmProductosList, SIGNAL(rejected()), frmProductosList, SLOT(closeParent()));
        QObject::connect(txtFiltroSearch, SIGNAL(textChanged(QString)), frmProductosList, SLOT(SearchChanged()));

        QMetaObject::connectSlotsByName(frmProductosList);
    } // setupUi

    void retranslateUi(QDialog *frmProductosList)
    {
        frmProductosList->setWindowTitle(QCoreApplication::translate("frmProductosList", "Listado de productos", nullptr));
        btnNuevo->setText(QCoreApplication::translate("frmProductosList", "&Nuevo", nullptr));
        btnModificar->setText(QCoreApplication::translate("frmProductosList", "&Modificar", nullptr));
        btnEliminar->setText(QCoreApplication::translate("frmProductosList", "&Eliminar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblProductos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("frmProductosList", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblProductos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("frmProductosList", "Categor\303\255as", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblProductos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("frmProductosList", "Nombre del producto", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblProductos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("frmProductosList", "Stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblProductos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("frmProductosList", "Marca", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblProductos->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("frmProductosList", "Referencia", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblProductos->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("frmProductosList", "P. Compra", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tblProductos->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("frmProductosList", "PVP", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmProductosList: public Ui_frmProductosList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMPRODUCTOSLIST_H
