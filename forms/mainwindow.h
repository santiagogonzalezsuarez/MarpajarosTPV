#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <QMdiSubWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetPermisos(QJsonArray permisos);

public slots:
    void ShowLogin();
    void SetUser(QJsonObject user);
    void UpdateWindowList();
    void OpenWindow(QMdiSubWindow *window);

    // Menu Actions
    void AbrirListadoProductos();
    void AbrirProducto(int ProductoId);
    void AbrirProductoJson(QJsonObject producto, QJsonArray categorias, QJsonArray proveedores);
    void AbrirListadoProveedores();
    void AbrirProveedor(int ProveedorId);
    void AbrirProveedorJson(QJsonObject proveedor);
    void AbrirListadoUsuarios();
    void AbrirUsuario(int UsuarioId);
    void AbrirUsuarioJson(QJsonObject usuario, QJsonArray roles);
    void AbrirListadoRoles();
    void AbrirRol(int RolId);
    void AbrirRolJson(QJsonObject rol, QJsonArray modulos);
    void AbrirCerrarCaja();
    void Cascada();
    void DividirHorizontalmente();
    void CerrarTodo();
    void AbrirConfiguracion();

    // Extra
    void UpdateListadoProductos();
    void UpdateListadoProveedores();
    void UpdateListadoUsuarios();
    void UpdateListadoRoles();

private slots:
    void CheckConfig();

private:
    Ui::MainWindow *ui;
    void AddSubWindow(QWidget *window, QString windowType);
    void closeEvent(QCloseEvent *event);
    static const int WindowTilingHorizontalIncrease = 24;
    static const int WindowTilingVerticalIncrease = 24;
    static const int WindowTilingMaximumIterations = 10;
    int WindowTilingCurrentIteration;
    bool isBeingDestroyed;
    inline static QJsonObject currentUser;
    bool cajaAbierta;
    void CheckCajaAbierta();
    void FixSeparators();
};
#endif // MAINWINDOW_H
