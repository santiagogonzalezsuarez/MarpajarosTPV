#ifndef FRMPROVEEDORESFORM_H
#define FRMPROVEEDORESFORM_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class frmProveedoresForm;
}

class frmProveedoresForm : public QDialog
{
    Q_OBJECT

public:
    explicit frmProveedoresForm(QWidget *parent = nullptr);
    ~frmProveedoresForm();
    QJsonObject proveedor;
    void LoadProveedor(QJsonObject proveedor);

public slots:
    void SaveProveedor();

signals:
    void UpdateListadoProveedores();

private slots:
    void closeParent();

private:
    Ui::frmProveedoresForm *ui;
};

#endif // FRMPROVEEDORESFORM_H
