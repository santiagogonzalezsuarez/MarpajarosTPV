#ifndef FRMROLESFORM_H
#define FRMROLESFORM_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class frmRolesForm;
}

class frmRolesForm : public QDialog
{
    Q_OBJECT

public:
    explicit frmRolesForm(QWidget *parent = nullptr);
    ~frmRolesForm();
    QJsonObject rol;
    void LoadModulos(QJsonArray modulos);
    void LoadRol(QJsonObject rol);

public slots:
    void SaveRol();

signals:
    void UpdateListadoRoles();

private slots:
    void closeParent();

private:
    Ui::frmRolesForm *ui;
};

#endif // FRMROLESFORM_H
