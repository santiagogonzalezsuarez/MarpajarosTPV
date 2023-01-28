/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Iniciar_sesion;
    QAction *action_Salir;
    QAction *action_Nueva_venta;
    QAction *action_Listado_de_ventas;
    QAction *action_Abrir_Cerrar_caja;
    QAction *action_Nueva_compra_al_proveedor;
    QAction *action_Listado_de_compras;
    QAction *actionListado_de_proveedores;
    QAction *actionListado_de_categorias;
    QAction *actionListado_de_productos;
    QAction *actionControl_de_stock;
    QAction *actionGestion_de_roles;
    QAction *actionGestion_de_usuarios;
    QAction *actionDividir_horizontalmente;
    QAction *actionCascada;
    QAction *actionCerrar_todo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menu_Programa;
    QMenu *menu_Ventas;
    QMenu *menu_Compras;
    QMenu *menu_Productos;
    QMenu *menu_Administracion;
    QMenu *menu_Ventana;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/marpajaros.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_Iniciar_sesion = new QAction(MainWindow);
        action_Iniciar_sesion->setObjectName(QString::fromUtf8("action_Iniciar_sesion"));
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("system-lock-screen");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        action_Iniciar_sesion->setIcon(icon1);
        action_Salir = new QAction(MainWindow);
        action_Salir->setObjectName(QString::fromUtf8("action_Salir"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        action_Salir->setIcon(icon2);
        action_Nueva_venta = new QAction(MainWindow);
        action_Nueva_venta->setObjectName(QString::fromUtf8("action_Nueva_venta"));
        action_Listado_de_ventas = new QAction(MainWindow);
        action_Listado_de_ventas->setObjectName(QString::fromUtf8("action_Listado_de_ventas"));
        action_Abrir_Cerrar_caja = new QAction(MainWindow);
        action_Abrir_Cerrar_caja->setObjectName(QString::fromUtf8("action_Abrir_Cerrar_caja"));
        action_Nueva_compra_al_proveedor = new QAction(MainWindow);
        action_Nueva_compra_al_proveedor->setObjectName(QString::fromUtf8("action_Nueva_compra_al_proveedor"));
        action_Listado_de_compras = new QAction(MainWindow);
        action_Listado_de_compras->setObjectName(QString::fromUtf8("action_Listado_de_compras"));
        actionListado_de_proveedores = new QAction(MainWindow);
        actionListado_de_proveedores->setObjectName(QString::fromUtf8("actionListado_de_proveedores"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/assets/proveedores.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListado_de_proveedores->setIcon(icon3);
        actionListado_de_categorias = new QAction(MainWindow);
        actionListado_de_categorias->setObjectName(QString::fromUtf8("actionListado_de_categorias"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/assets/categorias.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListado_de_categorias->setIcon(icon4);
        actionListado_de_productos = new QAction(MainWindow);
        actionListado_de_productos->setObjectName(QString::fromUtf8("actionListado_de_productos"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/assets/productos.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListado_de_productos->setIcon(icon5);
        actionControl_de_stock = new QAction(MainWindow);
        actionControl_de_stock->setObjectName(QString::fromUtf8("actionControl_de_stock"));
        actionGestion_de_roles = new QAction(MainWindow);
        actionGestion_de_roles->setObjectName(QString::fromUtf8("actionGestion_de_roles"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/assets/users.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGestion_de_roles->setIcon(icon6);
        actionGestion_de_roles->setVisible(true);
        actionGestion_de_usuarios = new QAction(MainWindow);
        actionGestion_de_usuarios->setObjectName(QString::fromUtf8("actionGestion_de_usuarios"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/assets/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGestion_de_usuarios->setIcon(icon7);
        actionDividir_horizontalmente = new QAction(MainWindow);
        actionDividir_horizontalmente->setObjectName(QString::fromUtf8("actionDividir_horizontalmente"));
        actionCascada = new QAction(MainWindow);
        actionCascada->setObjectName(QString::fromUtf8("actionCascada"));
        actionCerrar_todo = new QAction(MainWindow);
        actionCerrar_todo->setObjectName(QString::fromUtf8("actionCerrar_todo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdiArea->setViewMode(QMdiArea::SubWindowView);
        mdiArea->setDocumentMode(false);
        mdiArea->setTabsClosable(false);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu_Programa = new QMenu(menubar);
        menu_Programa->setObjectName(QString::fromUtf8("menu_Programa"));
        menu_Ventas = new QMenu(menubar);
        menu_Ventas->setObjectName(QString::fromUtf8("menu_Ventas"));
        menu_Compras = new QMenu(menubar);
        menu_Compras->setObjectName(QString::fromUtf8("menu_Compras"));
        menu_Productos = new QMenu(menubar);
        menu_Productos->setObjectName(QString::fromUtf8("menu_Productos"));
        menu_Administracion = new QMenu(menubar);
        menu_Administracion->setObjectName(QString::fromUtf8("menu_Administracion"));
        menu_Administracion->setEnabled(true);
        menu_Administracion->setToolTipsVisible(false);
        menu_Ventana = new QMenu(menubar);
        menu_Ventana->setObjectName(QString::fromUtf8("menu_Ventana"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_Programa->menuAction());
        menubar->addAction(menu_Ventas->menuAction());
        menubar->addAction(menu_Compras->menuAction());
        menubar->addAction(menu_Productos->menuAction());
        menubar->addAction(menu_Administracion->menuAction());
        menubar->addAction(menu_Ventana->menuAction());
        menu_Programa->addAction(action_Iniciar_sesion);
        menu_Programa->addSeparator();
        menu_Programa->addAction(action_Salir);
        menu_Ventas->addAction(action_Nueva_venta);
        menu_Ventas->addAction(action_Listado_de_ventas);
        menu_Ventas->addSeparator();
        menu_Ventas->addAction(action_Abrir_Cerrar_caja);
        menu_Compras->addAction(action_Nueva_compra_al_proveedor);
        menu_Compras->addAction(action_Listado_de_compras);
        menu_Productos->addAction(actionListado_de_proveedores);
        menu_Productos->addAction(actionListado_de_categorias);
        menu_Productos->addAction(actionListado_de_productos);
        menu_Productos->addSeparator();
        menu_Productos->addAction(actionControl_de_stock);
        menu_Administracion->addAction(actionGestion_de_roles);
        menu_Administracion->addAction(actionGestion_de_usuarios);
        menu_Ventana->addAction(actionCascada);
        menu_Ventana->addAction(actionDividir_horizontalmente);
        menu_Ventana->addSeparator();
        menu_Ventana->addAction(actionCerrar_todo);
        menu_Ventana->addSeparator();
        toolBar->addAction(action_Iniciar_sesion);
        toolBar->addAction(action_Salir);
        toolBar->addSeparator();
        toolBar->addAction(actionGestion_de_usuarios);
        toolBar->addAction(actionGestion_de_roles);
        toolBar->addSeparator();
        toolBar->addAction(actionListado_de_proveedores);
        toolBar->addAction(actionListado_de_categorias);
        toolBar->addAction(actionListado_de_productos);

        retranslateUi(MainWindow);
        QObject::connect(action_Salir, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(action_Iniciar_sesion, SIGNAL(triggered()), MainWindow, SLOT(ShowLogin()));
        QObject::connect(actionListado_de_productos, SIGNAL(triggered()), MainWindow, SLOT(AbrirListadoProductos()));
        QObject::connect(actionCascada, SIGNAL(triggered()), MainWindow, SLOT(Cascada()));
        QObject::connect(actionDividir_horizontalmente, SIGNAL(triggered()), MainWindow, SLOT(DividirHorizontalmente()));
        QObject::connect(actionCerrar_todo, SIGNAL(triggered()), MainWindow, SLOT(CerrarTodo()));
        QObject::connect(actionGestion_de_usuarios, SIGNAL(triggered()), MainWindow, SLOT(AbrirListadoUsuarios()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mar p\303\241jaros TPV", nullptr));
        action_Iniciar_sesion->setText(QCoreApplication::translate("MainWindow", "&Iniciar sesi\303\263n...", nullptr));
#if QT_CONFIG(shortcut)
        action_Iniciar_sesion->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Salir->setText(QCoreApplication::translate("MainWindow", "&Salir", nullptr));
#if QT_CONFIG(shortcut)
        action_Salir->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Nueva_venta->setText(QCoreApplication::translate("MainWindow", "&Nueva venta", nullptr));
        action_Listado_de_ventas->setText(QCoreApplication::translate("MainWindow", "&Listado de ventas", nullptr));
        action_Abrir_Cerrar_caja->setText(QCoreApplication::translate("MainWindow", "&Abrir caja", nullptr));
        action_Nueva_compra_al_proveedor->setText(QCoreApplication::translate("MainWindow", "&Nueva compra al proveedor", nullptr));
        action_Listado_de_compras->setText(QCoreApplication::translate("MainWindow", "&Listado de compras", nullptr));
        actionListado_de_proveedores->setText(QCoreApplication::translate("MainWindow", "Listado de &proveedores", nullptr));
        actionListado_de_categorias->setText(QCoreApplication::translate("MainWindow", "Listado de &categor\303\255as", nullptr));
        actionListado_de_productos->setText(QCoreApplication::translate("MainWindow", "Listado de p&roductos", nullptr));
        actionControl_de_stock->setText(QCoreApplication::translate("MainWindow", "Control de &stock", nullptr));
        actionGestion_de_roles->setText(QCoreApplication::translate("MainWindow", "Gesti\303\263n de &roles", nullptr));
        actionGestion_de_usuarios->setText(QCoreApplication::translate("MainWindow", "Gesti\303\263n de &usuarios", nullptr));
        actionDividir_horizontalmente->setText(QCoreApplication::translate("MainWindow", "&Mosaico", nullptr));
        actionCascada->setText(QCoreApplication::translate("MainWindow", "&Cascada", nullptr));
        actionCerrar_todo->setText(QCoreApplication::translate("MainWindow", "Cerrar &todo", nullptr));
        menu_Programa->setTitle(QCoreApplication::translate("MainWindow", "P&rograma", nullptr));
        menu_Ventas->setTitle(QCoreApplication::translate("MainWindow", "&Ventas", nullptr));
        menu_Compras->setTitle(QCoreApplication::translate("MainWindow", "C&ompras", nullptr));
        menu_Productos->setTitle(QCoreApplication::translate("MainWindow", "&Productos", nullptr));
        menu_Administracion->setTitle(QCoreApplication::translate("MainWindow", "A&dministraci\303\263n", nullptr));
        menu_Ventana->setTitle(QCoreApplication::translate("MainWindow", "Ven&tana", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
