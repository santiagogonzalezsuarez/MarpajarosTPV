#ifndef FRMUSUARIOSFORM_H
#define FRMUSUARIOSFORM_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>

namespace Ui {
class frmUsuariosForm;
}

class frmUsuariosForm : public QDialog
{
    Q_OBJECT

public:
    explicit frmUsuariosForm(QWidget *parent = nullptr);
    ~frmUsuariosForm();
    QJsonObject usuario;
    void LoadRoles(QJsonArray roles);
    void LoadUsuario(QJsonObject usuario);

signals:
    void UpdateListadoUsuarios();

private slots:
    void closeParent();
    void SaveUsuario();
    void RolChanged(int index);

private:
    Ui::frmUsuariosForm *ui;
    QStandardItemModel *rolesComboModel;
};

#endif // FRMUSUARIOSFORM_H
