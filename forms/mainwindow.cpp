#include "mainwindow.h"
#include "forms/ui_mainwindow.h"
#include "frmsplash.h"
#include "frmlogin.h"
#include <QJsonDocument>
#include "frmproductoslist.h"
#include "frmusuarioslist.h"
#include "frmusuariosform.h"
#include "frmroleslist.h"
#include "../util/util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->isBeingDestroyed = false;
    ui->setupUi(this);

    this->ui->mdiArea->cascadeSubWindows();
    this->WindowTilingCurrentIteration = 0;

    QJsonArray sinPermisos;
    this->SetPermisos(sinPermisos);

    frmSplash *frSplash = new class frmSplash(this);
    frSplash->setModal(true);
    connect(frSplash, &frmSplash::accepted, this, &MainWindow::ShowLogin);

    frSplash->show();
    this->statusBar()->hide();
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

MainWindow::~MainWindow()
{
    this->isBeingDestroyed = true;
    delete ui;
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
    if (!user["Token"].isNull()) {
        this->ui->action_Iniciar_sesion->setText("Cambiar de usuario...");
    } else {
        this->ui->action_Iniciar_sesion->setText("Iniciar sesión...");
    }
    this->setWindowTitle("Mar pájaros TPV - " + user["Nombre"].toString() + " " + user["Apellidos"].toString());
    this->SetPermisos(user["Permisos"].toArray());
    this->ui->mdiArea->closeAllSubWindows();
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

}

// Acciones del menú
void MainWindow::AbrirListadoProductos() {
    frmProductosList *frProductosList = new class frmProductosList();
    this->AddSubWindow(frProductosList, "frmProductosList");
    frProductosList->parentWidget()->setWindowIcon(frProductosList->windowIcon());
    frProductosList->show();
    frProductosList->parentWidget()->setMinimumSize(1150, 650);
}

void MainWindow::AbrirListadoUsuarios() {
    frmUsuariosList *frUsuariosList = new class frmUsuariosList();
    this->AddSubWindow(frUsuariosList, "frmUsuariosList");
    connect(frUsuariosList, &frmUsuariosList::AbrirUsuario, this, &MainWindow::AbrirUsuario);
    frUsuariosList->parentWidget()->setWindowIcon(frUsuariosList->windowIcon());
    frUsuariosList->show();
    frUsuariosList->parentWidget()->setMinimumSize(740, 520);
}

void MainWindow::AbrirListadoRoles() {
    frmRolesList *frRolesList = new class frmRolesList();
    this->AddSubWindow(frRolesList, "frmRolesList");
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

// Recargar ventanas
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
