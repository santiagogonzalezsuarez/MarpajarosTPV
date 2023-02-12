#ifndef FRMPRODUCTOSFORM_H
#define FRMPRODUCTOSFORM_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeView>
#include "../controls/treemodel.h"
#include "../controls/treeviewautohideable.h"
#include "../controls/productoproveedorcontrol.h"
#include <QStandardItemModel>

namespace Ui {
class frmProductosForm;
}

class frmProductosForm : public QDialog
{
    Q_OBJECT

public:
    explicit frmProductosForm(QWidget *parent = nullptr);
    ~frmProductosForm();
    QJsonObject producto;
    void LoadCategorias(QJsonArray categorias);
    void LoadProveedores(QJsonArray proveedores);
    void LoadProducto(QJsonObject producto);

public slots:
    void SaveProducto();

signals:
    void UpdateListadoProductos();

private slots:
    void closeParent();
    void CategoriaSelected(int CategoriaId, QString TextoCategoria);
    void IVAChanged(int index);
    void UpdateProveedores();
    void QuitarProveedor(ProductoProveedorControl *proveedor);

protected:
    TreeViewAutoHideable *categoriasTree;
    void adjustCategoriasPopup();
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *event);

private:
    Ui::frmProductosForm *ui;
    QJsonArray categorias;
    TreeModel categoriasModel = TreeModel(categorias);
    QJsonArray proveedores;
    QStandardItemModel ivaModel;
};

#endif // FRMPRODUCTOSFORM_H
