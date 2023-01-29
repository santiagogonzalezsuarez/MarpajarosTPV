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
    void AbrirListadoUsuarios();
    void Cascada();
    void DividirHorizontalmente();
    void CerrarTodo();
    void AbrirUsuario(int UsuarioId);
    void AbrirUsuarioJson(QJsonObject usuario, QJsonArray roles);
    void AbrirListadoRoles();
    void AbrirRol(int RolId);
    void AbrirRolJson(QJsonObject rol, QJsonArray modulos);

    // Extra
    void UpdateListadoUsuarios();
    void UpdateListadoRoles();

private:
    Ui::MainWindow *ui;
    void AddSubWindow(QWidget *window, QString windowType);
    void closeEvent(QCloseEvent *event);
    static const int WindowTilingHorizontalIncrease = 24;
    static const int WindowTilingVerticalIncrease = 24;
    static const int WindowTilingMaximumIterations = 10;
    int WindowTilingCurrentIteration;
    bool isBeingDestroyed;
};
#endif // MAINWINDOW_H
