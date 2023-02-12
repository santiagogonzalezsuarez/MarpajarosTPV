#ifndef PRODUCTOPROVEEDORCONTROL_H
#define PRODUCTOPROVEEDORCONTROL_H

#include <QWidget>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QJsonObject>

namespace Ui {
class ProductoProveedorControl;
}

class ProductoProveedorControl : public QWidget
{
    Q_OBJECT

public:
    explicit ProductoProveedorControl(QWidget *parent = nullptr);
    ~ProductoProveedorControl();
    void LoadProveedores(QJsonArray proveedores);
    QJsonObject productoProveedor;
    void SetIVA(double IVA);
    void LoadProductoProveedor(QJsonObject productoProveedor);

signals:
    void ProveedorSelected();
    void SetPrecioVenta(double precioRecomendado);
    void QuitarProveedor(ProductoProveedorControl *proveedor);

private slots:
    void btnSetPrecioVentaClicked();
    void btnQuitarProveedorClicked();

private:
    Ui::ProductoProveedorControl *ui;
    QStandardItemModel *proveedoresComboModel;
    void cmbProveedorCurrentIndexChanged(int index);
    void UpdatePrecioRecomendado();
    double IVA;
};

#endif // PRODUCTOPROVEEDORCONTROL_H
