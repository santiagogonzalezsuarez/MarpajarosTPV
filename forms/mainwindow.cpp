#include "mainwindow.h"
#include "forms/ui_mainwindow.h"
#include "frmsplash.h"
#include "frmlogin.h"
#include <QJsonDocument>
#include "frmproductoslist.h"
#include "frmusuarioslist.h"
#include "frmusuariosform.h"
#include "frmroleslist.h"
#include "frmrolesform.h"
#include "frmconfiguracion.h"
#include "frmsolicitarcontrasena.h"
#include "frmabrircerrarcaja.h"
#include "frmproductosform.h"
#include "frmproveedoreslist.h"
#include "frmproveedoresform.h"
#include "../util/util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->isBeingDestroyed = false;
    this->cajaAbierta = false;
    ui->setupUi(this);

    this->ui->mdiArea->cascadeSubWindows();
    this->WindowTilingCurrentIteration = 0;

    QJsonArray sinPermisos;
    this->SetPermisos(sinPermisos);

    frmSplash *frSplash = new class frmSplash(this);
    frSplash->setModal(true);
    connect(frSplash, &frmSplash::accepted, this, &MainWindow::CheckConfig);

    frSplash->show();
    this->statusBar()->hide();
}

MainWindow::~MainWindow()
{
    this->isBeingDestroyed = true;
    delete ui;
}

void MainWindow::CheckConfig()
{
    if ((Util::GetConfigString("API.URL") == nullptr || Util::GetConfigString("API.URL") == "") || Util::GetConfigInt("Caja.CajaActiva") == 0) {
        frmConfiguracion *frConfiguracion = new class frmConfiguracion(this);
        frConfiguracion->setModal(true);
        frConfiguracion->show();
        connect(frConfiguracion, &frmConfiguracion::accepted, this, &MainWindow::ShowLogin);
    } else {
        this->ShowLogin();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Cuando se cierra la venana primero se está destruyendo la MainWindow y luego el resto de SubWindows. Esto me da problemas porque tengo conectada
    // la señal Destroy de las Subwindows para actualizar la lista de ventanas, así que obligo a cerrar primero las Subwindows.
    if (this->ui->mdiArea->subWindowList().count() > 0) {
        event->ignore();
        this->ui->mdiArea->closeAllSubWindows();
        QTimer::singleShot(0, this, [=]() {
            this->close();
        });
    }
}

void MainWindow::AddSubWindow(QWidget *window, QString windowType) { // Similar to Windows MDI Forms, so we don't get the windows to show offscreen
    this->ui->mdiArea->addSubWindow(window);
    this->UpdateWindowList();
    connect(window->parentWidget(), &QWidget::destroyed, this, &MainWindow::UpdateWindowList);
    connect(window->parentWidget(), &QWidget::windowTitleChanged, this, &MainWindow::UpdateWindowList);
    window->parentWidget()->setProperty("MPwindowType", windowType);
    if (this->ui->mdiArea->currentSubWindow() != nullptr && this->ui->mdiArea->currentSubWindow()->isMaximized()) {
        return;
    }
    window->parentWidget()->move(this->WindowTilingCurrentIteration * MainWindow::WindowTilingHorizontalIncrease, this->WindowTilingCurrentIteration * MainWindow::WindowTilingVerticalIncrease);
    this->WindowTilingCurrentIteration++;
    this->WindowTilingCurrentIteration %= MainWindow::WindowTilingMaximumIterations;
}

void MainWindow::ShowLogin() {
    frmLogin *frLogin = new class frmLogin(this);
    connect(frLogin, &frmLogin::successfulLogin, this, &MainWindow::SetUser);
    frLogin->setModal(true);
    frLogin->show();
}

void MainWindow::SetUser(QJsonObject user) {
    this->currentUser = user;
    if (!user["Token"].isNull()) {
        this->ui->action_Iniciar_sesion->setText("Cambiar de usuario...");
    } else {
        this->ui->action_Iniciar_sesion->setText("Iniciar sesión...");
    }
    this->setWindowTitle("Mar pájaros TPV - " + user["Nombre"].toString() + " " + user["Apellidos"].toString());
    this->SetPermisos(user["Permisos"].toArray());
    this->ui->mdiArea->closeAllSubWindows();

    this->CheckCajaAbierta();
}

void MainWindow::CheckCajaAbierta()
{
    // Obtenemos el estado de la caja para establecer el nombre de la opción del menú.
    QJsonObject isCajaAbiertaRequest;
    isCajaAbiertaRequest["CajaId"] = Util::GetConfigInt("Caja.CajaActiva");
    Util::PerformWebPost(this, "/caja/getIsCajaAbierta", isCajaAbiertaRequest, [=](QJsonObject result) {
        if (result["CajaAbierta"].toBool(false)) {
            this->ui->action_Abrir_Cerrar_caja->setText("&Cerrar caja");
            this->cajaAbierta = true;
        } else {
            this->ui->action_Abrir_Cerrar_caja->setText("&Abrir caja");
            this->cajaAbierta = false;
        }
    }, [](QString errorMessage) {
        Util::ErrorAlert("Mar pájaros TPV", "No se ha podido obtener el estado de la caja.");
    });
}

void MainWindow::SetPermisos(QJsonArray permisos) {

    this->ui->actionGestion_de_roles->setVisible(permisos.contains(110));
    this->ui->actionGestion_de_usuarios->setVisible(permisos.contains(210));
    this->ui->menu_Administracion->menuAction()->setVisible(permisos.contains(110) || permisos.contains(210));
    this->ui->actionListado_de_proveedores->setVisible(permisos.contains(310));
    this->ui->actionListado_de_categorias->setVisible(permisos.contains(410));
    this->ui->actionListado_de_productos->setVisible(permisos.contains(420));
    this->ui->menu_Productos->menuAction()->setVisible(permisos.contains(310) || permisos.contains(410) || permisos.contains(420));
    this->ui->action_Nueva_compra_al_proveedor->setVisible(permisos.contains(510));
    this->ui->action_Listado_de_compras->setVisible(permisos.contains(510) || permisos.contains(520));
    this->ui->menu_Compras->menuAction()->setVisible(permisos.contains(510) || permisos.contains(520));
    this->ui->action_Nueva_venta->setVisible(permisos.contains(610));
    this->ui->action_Listado_de_ventas->setVisible(permisos.contains(620));
    this->ui->menu_Ventas->menuAction()->setVisible(permisos.contains(610) || permisos.contains(620));
    this->ui->action_Abrir_Cerrar_caja->setVisible(permisos.contains(610) || permisos.contains(620));
    this->ui->actionControl_de_stock->setVisible(permisos.contains(610) || permisos.contains(620));

    this->FixSeparators();

}

void MainWindow::FixSeparators()
{
    bool lastItemIsSeparator = false;
    QList<QAction*> actions = this->ui->toolBar->actions();
    for (QList<QAction*>::Iterator i = actions.begin(); i != actions.end(); ++i) {
        QAction *item = (QAction*)*i;
        if (item->isSeparator() && lastItemIsSeparator) {
            item->setVisible(false);
        }
        if (item->isSeparator() && (!lastItemIsSeparator)) {
            item->setVisible(true);
        }
        if (item->isSeparator()) {
            lastItemIsSeparator = true;
        }
        if (!item->isSeparator()) {
            if (item->isVisible()) {
                lastItemIsSeparator = false;
            }
        }
    }

}

// Acciones del menú
void MainWindow::AbrirConfiguracion()
{
    frmConfiguracion *frConfiguracion = new class frmConfiguracion();
    frConfiguracion->setModal(true);
    frConfiguracion->show();
}

void MainWindow::AbrirListadoProductos() {
    frmProductosList *frProductosList = new class frmProductosList();
    this->AddSubWindow(frProductosList, "frmProductosList");
    connect(frProductosList, &frmProductosList::AbrirProducto, this, &MainWindow::AbrirProducto);
    connect(frProductosList, &frmProductosList::UpdateListadoProductos, this, &MainWindow::UpdateListadoProductos);
    connect(frProductosList, &frmProductosList::DisableMainWindow, this, [=](){this->setDisabled(true);});
    connect(frProductosList, &frmProductosList::EnableMainWindow, this, [=](){this->setDisabled(false);});
    frProductosList->parentWidget()->setWindowIcon(frProductosList->windowIcon());
    frProductosList->show();
    frProductosList->parentWidget()->setMinimumSize(1150, 650);
}

void MainWindow::AbrirListadoProveedores() {
    frmProveedoresList *frProveedoresList = new class frmProveedoresList();
    this->AddSubWindow(frProveedoresList, "frmProveedoresList");
    connect(frProveedoresList, &frmProveedoresList::AbrirProveedor, this, &MainWindow::AbrirProveedor);
    connect(frProveedoresList, &frmProveedoresList::UpdateListadoProveedores, this, &MainWindow::UpdateListadoProveedores);
    frProveedoresList->parentWidget()->setWindowIcon(frProveedoresList->windowIcon());
    frProveedoresList->show();
    frProveedoresList->parentWidget()->setMinimumSize(1150, 650);
}

void MainWindow::AbrirListadoUsuarios() {
    frmUsuariosList *frUsuariosList = new class frmUsuariosList();
    this->AddSubWindow(frUsuariosList, "frmUsuariosList");
    connect(frUsuariosList, &frmUsuariosList::AbrirUsuario, this, &MainWindow::AbrirUsuario);
    connect(frUsuariosList, &frmUsuariosList::UpdateListadoUsuarios, this, &MainWindow::UpdateListadoUsuarios);
    frUsuariosList->parentWidget()->setWindowIcon(frUsuariosList->windowIcon());
    frUsuariosList->show();
    frUsuariosList->parentWidget()->setMinimumSize(740, 520);
}

void MainWindow::AbrirListadoRoles() {
    frmRolesList *frRolesList = new class frmRolesList();
    this->AddSubWindow(frRolesList, "frmRolesList");
    connect(frRolesList, &frmRolesList::AbrirRol, this, &MainWindow::AbrirRol);
    connect(frRolesList, &frmRolesList::UpdateListadoRoles, this, &MainWindow::UpdateListadoRoles);
    frRolesList->parentWidget()->setWindowIcon(frRolesList->windowIcon());
    frRolesList->show();
    frRolesList->parentWidget()->setMinimumSize(727, 505);
}

void MainWindow::Cascada()
{
    this->ui->mdiArea->cascadeSubWindows();
}

void MainWindow::DividirHorizontalmente()
{
    this->ui->mdiArea->tileSubWindows();
}

void MainWindow::CerrarTodo()
{
    this->ui->mdiArea->closeAllSubWindows();
}

void MainWindow::AbrirProducto(int ProductoId)
{
    QJsonObject getAllCategoriasRequest;
    Util::PerformWebPost(this, "/categorias/getAllCategorias", getAllCategoriasRequest, [=](QJsonObject categoriasResult) {
        QJsonArray categorias = categoriasResult["Categorias"].toArray();
        QJsonObject getProveedoresComboRequest;
        Util::PerformWebPost(this, "/proveedores/getProveedoresCombo", getProveedoresComboRequest, [=](QJsonArray proveedores) {
            if (ProductoId == 0) {
                QJsonObject producto;
                producto["Id"] = 0;
                producto["CategoriaId"] = 0;
                producto["CodigoBarras"] = "";
                producto["Producto"] = "";
                producto["IVA"] = Util::FixDoubleForCurrency(26.2f);
                producto["Marca"] = "";
                producto["PrecioVenta"] = 0;
                producto["StockMinimo"] = 0;
                this->AbrirProductoJson(producto, categorias, proveedores);
            } else {
                QJsonObject getProductoRequest;
                getProductoRequest["Id"] = ProductoId;
                Util::PerformWebPost(this, "/productos/getProducto", getProductoRequest, [=](QJsonObject producto) {
                    this->AbrirProductoJson(producto, categorias, proveedores);
                }, [=](QString errorMessage) {
                    Util::ErrorAlert("Modificar producto", errorMessage);
                });
            }
        }, [=](QString errorMessage) {
            QString title = "Modificar producto";
            if (ProductoId == 0) {
                title = "Nuevo producto";
            }
            Util::ErrorAlert(title, errorMessage);
        });
    }, [=](QString errorMessage) {
        QString title = "Modificar producto";
        if (ProductoId == 0) {
            title = "Nuevo producto";
        }
        Util::ErrorAlert(title, errorMessage);
    });
}

void MainWindow::AbrirProductoJson(QJsonObject producto, QJsonArray categorias, QJsonArray proveedores) {
    frmProductosForm *frProductosForm = new class frmProductosForm();
    this->AddSubWindow(frProductosForm, "frmProductosForm");
    connect(frProductosForm, &frmProductosForm::UpdateListadoProductos, this, &MainWindow::UpdateListadoProductos);
    frProductosForm->LoadCategorias(categorias);
    frProductosForm->LoadProveedores(proveedores);
    frProductosForm->LoadProducto(producto);
    frProductosForm->parentWidget()->setWindowIcon(frProductosForm->windowIcon());
    frProductosForm->show();
    if (producto["Id"].toInt(0) == 0) {
        frProductosForm->parentWidget()->setWindowTitle("Nuevo producto");
    } else {
        frProductosForm->parentWidget()->setWindowTitle("Modificar producto - " + producto["Producto"].toString(""));
    }
    frProductosForm->parentWidget()->setMinimumSize(800, 450);
    if (!frProductosForm->parentWidget()->isMaximized()) {
        frProductosForm->parentWidget()->resize(850, 620);
    }
}

void MainWindow::AbrirProveedor(int ProveedorId)
{
    if (ProveedorId == 0) {
        QJsonObject proveedor;
        proveedor["Id"] = 0;
        proveedor["Nombre"] = "";
        proveedor["Telefono"] = "";
        proveedor["Email"] = "";
        proveedor["PaginaWeb"] = "";
        proveedor["Direccion"] = "";
        proveedor["Horarios"] = "";
        proveedor["Observaciones"] = "";
        proveedor["MostrarEnInformeVentas"] = false;
        this->AbrirProveedorJson(proveedor);
    } else {
        QJsonObject getProveedorRequest;
        getProveedorRequest["Id"] = ProveedorId;
        Util::PerformWebPost(this, "/proveedores/getProveedor", getProveedorRequest, [=](QJsonObject proveedor) {
            this->AbrirProveedorJson(proveedor);
        }, [=](QString errorMessage) {
            Util::ErrorAlert("Modificar proveedor", errorMessage);
        });
    }
}

void MainWindow::AbrirProveedorJson(QJsonObject proveedor)
{
    frmProveedoresForm *frProveedoresForm = new class frmProveedoresForm();
    this->AddSubWindow(frProveedoresForm, "frmProveedoresForm");
    connect(frProveedoresForm, &frmProveedoresForm::UpdateListadoProveedores, this, &MainWindow::UpdateListadoProveedores);
    frProveedoresForm->LoadProveedor(proveedor);
    frProveedoresForm->parentWidget()->setWindowIcon(frProveedoresForm->windowIcon());
    frProveedoresForm->show();
    if (proveedor["Id"].toInt(0) == 0) {
        frProveedoresForm->parentWidget()->setWindowTitle("Nuevo proveedor");
    } else {
        frProveedoresForm->parentWidget()->setWindowTitle("Modificar proveedor - " + proveedor["Nombre"].toString(""));
    }
    frProveedoresForm->parentWidget()->setMinimumSize(760, 500);
    if (!frProveedoresForm->parentWidget()->isMaximized()) {
        frProveedoresForm->parentWidget()->resize(760, 500);
    }
}

void MainWindow::AbrirUsuario(int UsuarioId)
{
    // Cargamos los roles
    QJsonObject getRolesComboRequest;
    Util::PerformWebPost(this, "/roles/getRolesCombo", getRolesComboRequest, [=](QJsonArray roles) {
        if (UsuarioId == 0) {
            QJsonObject usuario;
            usuario["Id"] = 0;
            usuario["Username"] = "";
            usuario["Password"] = "";
            usuario["Nombre"] = "";
            usuario["Apellidos"] = "";
            usuario["RolId"] = 0;
            this->AbrirUsuarioJson(usuario, roles);
        } else {
            QJsonObject getUsuarioRequest;
            getUsuarioRequest["Id"] = UsuarioId;
            Util::PerformWebPost(this, "/usuarios/getUsuario", getUsuarioRequest, [=](QJsonObject usuario) {
                usuario["Password"] = "-DoNotChange-";
                this->AbrirUsuarioJson(usuario, roles);
            }, [](QString errorMessage) {
                Util::ErrorAlert("Modificar usuario", errorMessage);
            });
        }
    }, [=](QString errorMessage) {
        QString title = "Modificar usuario";
        if (UsuarioId == 0) {
            title = "Nuevo usuario";
        }
        Util::ErrorAlert(title, errorMessage);
    });
}

void MainWindow::AbrirUsuarioJson(QJsonObject usuario, QJsonArray roles) {
    frmUsuariosForm *frUsuariosForm = new class frmUsuariosForm();
    this->AddSubWindow(frUsuariosForm, "frmUsuariosForm");
    connect(frUsuariosForm, &frmUsuariosForm::UpdateListadoUsuarios, this, &MainWindow::UpdateListadoUsuarios);
    frUsuariosForm->LoadRoles(roles);
    frUsuariosForm->LoadUsuario(usuario);
    frUsuariosForm->parentWidget()->setWindowIcon(frUsuariosForm->windowIcon());
    frUsuariosForm->show();
    if (usuario["Id"].toInt(0) == 0) {
        frUsuariosForm->parentWidget()->setWindowTitle("Nuevo usuario");
    } else {
        frUsuariosForm->parentWidget()->setWindowTitle("Modificar usuario - " + usuario["Nombre"].toString("") + " " + usuario["Apellidos"].toString(""));
    }
    frUsuariosForm->parentWidget()->setMinimumSize(363, 250);
    if (!frUsuariosForm->parentWidget()->isMaximized()) {
        frUsuariosForm->parentWidget()->resize(363, 250);
    }
}

void MainWindow::AbrirRol(int RolId)
{
    // Cargamos los módulos y permisos
    QJsonObject getModulosRequest;
    Util::PerformWebPost(this, "/modulos/getAllModulos", getModulosRequest, [=](QJsonArray modulos) {
        if (RolId == 0) {
            QJsonObject rol;
            rol["Id"] = 0;
            rol["Rol"] = "";
            QJsonArray permisosIds;
            rol["PermisosIds"] = permisosIds;
            this->AbrirRolJson(rol, modulos);
        } else {
            QJsonObject getRolRequest;
            getRolRequest["Id"] = RolId;
            Util::PerformWebPost(this, "/roles/getRol", getRolRequest, [=](QJsonObject rol) {
                this->AbrirRolJson(rol, modulos);
            }, [](QString errorMessage) {
                Util::ErrorAlert("Modificar rol", errorMessage);
            });
        }
    }, [=](QString errorMessage) {
        QString title = "Modificar rol";
        if (RolId == 0) {
            title = "Nuevo rol";
        }
        Util::ErrorAlert(title, errorMessage);
    });
}

void MainWindow::AbrirRolJson(QJsonObject rol, QJsonArray modulos)
{
    frmRolesForm *frRolesForm = new class frmRolesForm();
    this->AddSubWindow(frRolesForm, "frmRolesForm");
    connect(frRolesForm, &frmRolesForm::UpdateListadoRoles, this, &MainWindow::UpdateListadoRoles);
    frRolesForm->LoadModulos(modulos);
    frRolesForm->LoadRol(rol);
    frRolesForm->parentWidget()->setWindowIcon(frRolesForm->windowIcon());
    frRolesForm->show();
    if (rol["Id"].toInt(0) == 0) {
        frRolesForm->parentWidget()->setWindowTitle("Nuevo rol");
    } else {
        frRolesForm->parentWidget()->setWindowTitle("Modificar rol - " + rol["Rol"].toString(""));
    }
    frRolesForm->parentWidget()->setMinimumSize(363, 250);
    if (!frRolesForm->parentWidget()->isMaximized()) {
        frRolesForm->parentWidget()->resize(880, 700);
    }
}

void MainWindow::AbrirCerrarCaja()
{
    frmSolicitarContrasena *frSolicitarContrasena = new class frmSolicitarContrasena(this);
    frSolicitarContrasena->username = this->currentUser["Username"].toString("");
    frSolicitarContrasena->setModal(true);
    if (this->cajaAbierta) {
        frSolicitarContrasena->SetLabelTitle("Escriba su contraseña para cerrar caja:");
    } else {
        frSolicitarContrasena->SetLabelTitle("Escriba su contraseña para abrir caja:");
    }
    connect(frSolicitarContrasena, &frmSolicitarContrasena::accepted, this, [=]() {
        QJsonObject getUltimaAperturaCajaRequest;
        getUltimaAperturaCajaRequest["CajaId"] = Util::GetConfigInt("Caja.CajaActiva");
        Util::PerformWebPost(this, "/caja/getUltimaAperturaCaja", getUltimaAperturaCajaRequest, [=](QJsonObject result) {
            frmAbrirCerrarCaja *frAbrirCerrarCaja = new class frmAbrirCerrarCaja(this);
            frAbrirCerrarCaja->setModal(true);
            if (this->cajaAbierta) {
                frAbrirCerrarCaja->setWindowTitle("Cerrar caja");
            } else {
                frAbrirCerrarCaja->setWindowTitle("Abrir caja");
            }
            frAbrirCerrarCaja->ultimaAperturaCaja = result;
            frAbrirCerrarCaja->CalcularImportes();
            frAbrirCerrarCaja->CuadrePredeterminado();
            connect(frAbrirCerrarCaja, &frmAbrirCerrarCaja::accepted, this, [=]() {
                this->CheckCajaAbierta();
            });
            frAbrirCerrarCaja->show();
        }, [=](QString errorMessage) {
            QString windowTitle;
            if (this->cajaAbierta) {
                windowTitle = "Cerrar caja";
            } else {
                windowTitle = "Abrir caja";
            }
            Util::ErrorAlert(windowTitle, "No se ha podido cargar la información del último cuadre de caja.");
        });
    });
    frSolicitarContrasena->show();
}

// Recargar ventanas
void MainWindow::UpdateListadoProductos()
{
    QList<QMdiSubWindow*> windowList = this->ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
    for (QList<QMdiSubWindow*>::Iterator i = windowList.begin(); i != windowList.end(); ++i) {
        QMdiSubWindow *window = *i;
        if (!window->property("MPwindowType").isNull() && window->property("MPwindowType") == "frmProductosList") {
            frmProductosList *frProductosList = (frmProductosList*)window->widget();
            frProductosList->ActualizarListado();
        }
    }
}

void MainWindow::UpdateListadoProveedores()
{
    QList<QMdiSubWindow*> windowList = this->ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
    for (QList<QMdiSubWindow*>::Iterator i = windowList.begin(); i != windowList.end(); ++i) {
        QMdiSubWindow *window = *i;
        if (!window->property("MPwindowType").isNull() && window->property("MPwindowType") == "frmProveedoresList") {
            frmProveedoresList *frProveedoresList = (frmProveedoresList*)window->widget();
            frProveedoresList->ActualizarListado();
        }
    }
}

void MainWindow::UpdateListadoUsuarios()
{
    QList<QMdiSubWindow*> windowList = this->ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
    for (QList<QMdiSubWindow*>::Iterator i = windowList.begin(); i != windowList.end(); ++i) {
        QMdiSubWindow *window = *i;
        if (!window->property("MPwindowType").isNull() && window->property("MPwindowType") == "frmUsuariosList") {
            frmUsuariosList *frUsuariosList = (frmUsuariosList*)window->widget();
            frUsuariosList->ActualizarListado();
        }
    }
}

void MainWindow::UpdateListadoRoles()
{
    QList<QMdiSubWindow*> windowList = this->ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
    for (QList<QMdiSubWindow*>::Iterator i = windowList.begin(); i != windowList.end(); ++i) {
        QMdiSubWindow *window = *i;
        if (!window->property("MPwindowType").isNull() && window->property("MPwindowType") == "frmRolesList") {
            frmRolesList *frRolesList = (frmRolesList*)window->widget();
            frRolesList->ActualizarListado();
        }
    }
}

// Extra
void MainWindow::UpdateWindowList()
{
    if (!this->isBeingDestroyed) {
        QList<QAction*> actionList = this->ui->menu_Ventana->actions();
        for (QList<QAction*>::Iterator i = actionList.end(); i != actionList.begin();) {
            --i;
            QAction *action = *i;
            if ((!action->property("isMPWindow").isNull()) && action->property("isMPWindow").toBool()) {
                this->ui->menu_Ventana->removeAction(action);
                delete action;
            }
        }

        QList<QMdiSubWindow*> windowList = this->ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
        int count = 0;
        for (QList<QMdiSubWindow*>::Iterator i = windowList.begin(); i != windowList.end(); ++i) {
            QMdiSubWindow *window = *i;
            QAction *action = new QAction(this);
            count++;
            action->setText(QString::number(count) + " - " + window->windowTitle());
            action->setProperty("isMPWindow", true);
            action->setProperty("windowIndex", i - windowList.begin()); // Solo funcionará porque estamos creando la lista en el orden de creación.
            connect(action, &QAction::triggered, this, [=]() {
                this->OpenWindow(window);
            });
            this->ui->menu_Ventana->addAction(action);
        }
    }
}

void MainWindow::OpenWindow(QMdiSubWindow *window) {
    this->ui->mdiArea->setActiveSubWindow(window);
}
