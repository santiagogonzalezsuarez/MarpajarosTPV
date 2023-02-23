#include "frmproductosform.h"
#include <QJsonDocument>
#include "ui_frmproductosform.h"
#include "../util/util.h"
#include "../controls/treemodel.h"
#include "../util/crelaxeddoublespinbox.h"

frmProductosForm::frmProductosForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmProductosForm)
{
    ui->setupUi(this);

    this->categoriasTree = new TreeViewAutoHideable(this);
    this->categoriasTree->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->categoriasTree->setModel(&this->categoriasModel);
    this->categoriasModel.update(this->categorias);
    this->categoriasTree->hideColumn(1);
    this->categoriasTree->setHeaderHidden(true);

    connect(this->categoriasTree, &TreeViewAutoHideable::ItemSelected, this, &frmProductosForm::CategoriaSelected);

    // Botón categorías
    connect(this->ui->btnCategoria, &QPushButton::clicked, this, [=]() {
        this->categoriasTree->setVisible(!this->categoriasTree->isVisible());
        if (this->categoriasTree->isVisible()) {
            this->categoriasTree->show();
            this->categoriasTree->raise();
            this->categoriasTree->setFocus();
        }
        adjustCategoriasPopup();
    });

    // IVA
    QStandardItem *item;
    item = new QStandardItem("21 %"); item->setData(Util::FixDoubleForCurrency(26.2f)); this->ivaModel.appendRow(item);
    item = new QStandardItem("10 %"); item->setData(Util::FixDoubleForCurrency(11.4f)); this->ivaModel.appendRow(item);
    item = new QStandardItem("4 %"); item->setData(Util::FixDoubleForCurrency(4.5f)); this->ivaModel.appendRow(item);
    item = new QStandardItem("Sin IVA"); item->setData(Util::FixDoubleForCurrency(0.f)); this->ivaModel.appendRow(item);
    this->ui->cmbIVA->setModel(&this->ivaModel);
    this->ui->cmbIVA->setCurrentIndex(0);

    // Eventos para actualizar valores.
    connect(this->ui->cmbIVA, SIGNAL(currentIndexChanged(int)), this, SLOT(IVAChanged(int)));
    connect(this->ui->txtProducto, &QLineEdit::textChanged, this, [=](){ this->producto["Producto"] = this->ui->txtProducto->text(); });
    connect(this->ui->txtCodigoBarras, &QLineEdit::textChanged, this, [=](){ this->producto["CodigoBarras"] = this->ui->txtCodigoBarras->text(); });
    connect(this->ui->numPrecioVenta, &CRelaxedDoubleSpinBox::valueChanged, this, [=](double value){ this->producto["PrecioVenta"] = Util::FixDoubleForCurrency(value); });
    connect(this->ui->txtMarca, &QLineEdit::textChanged, this, [=](){ this->producto["Marca"] = this->ui->txtMarca->text(); });
    connect(this->ui->txtAnimales, &QLineEdit::textChanged, this, [=](){ this->producto["Animales"] = this->ui->txtAnimales->text(); });
    connect(this->ui->numStockMinimo, &QSpinBox::valueChanged, this, [=](int value){ this->producto["StockMinimo"] = value; });

}

frmProductosForm::~frmProductosForm()
{
    delete this->categoriasTree;
    delete ui;
}

void frmProductosForm::IVAChanged(int index) {
    this->producto["IVA"] = Util::FixDoubleForCurrency(this->ivaModel.item(index)->data().toFloat());
    this->UpdateProveedores();
}

void frmProductosForm::CategoriaSelected(int CategoriaId, QString TextoCategoria)
{
    this->categoriasTree->setVisible(false);
    this->producto["CategoriaId"] = CategoriaId;
    this->ui->btnCategoria->setText(TextoCategoria);
}

void frmProductosForm::adjustCategoriasPopup()
{
    if (!this->categoriasTree->isVisible()) {
        return;
    }
    QRect rect = this->ui->btnCategoria->geometry();
    QPoint bottomLeft = this->mapToGlobal(rect.bottomLeft());
    bottomLeft += QPoint(9, 9);
    this->categoriasTree->setGeometry(QRect(bottomLeft, QSize(rect.width(), 200)));
}

void frmProductosForm::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->adjustCategoriasPopup();
}

void frmProductosForm::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);
    this->adjustCategoriasPopup();
}

void frmProductosForm::closeParent()
{
    this->parentWidget()->close();
}

void frmProductosForm::LoadCategorias(QJsonArray categorias)
{
    this->categorias = categorias;
    this->categoriasModel.update(this->categorias);
    this->categoriasTree->setModel(&this->categoriasModel);
}

void frmProductosForm::LoadProveedores(QJsonArray proveedores)
{
    this->proveedores = proveedores;
}

void frmProductosForm::LoadProducto(QJsonObject producto)
{
    this->producto = producto;

    QJsonArray productoProveedores = producto["Proveedores"].toArray();
    QList<ProductoProveedorControl*> controls;
    for (QJsonArray::Iterator i = productoProveedores.begin(); i != productoProveedores.end(); ++i) {
        QJsonObject productoProveedor = (*i).toObject();
        ProductoProveedorControl *productoProveedorControl = new class ProductoProveedorControl(this);
        productoProveedorControl->LoadProveedores(this->proveedores);
        this->ui->grpProveedores->layout()->addWidget(productoProveedorControl);
        productoProveedorControl->LoadProductoProveedor(productoProveedor);
        controls.append(productoProveedorControl);
    }
    for (QList<ProductoProveedorControl*>::Iterator i = controls.begin(); i != controls.end(); ++i) {
        ProductoProveedorControl* productoProveedorControl = *i;
        connect(productoProveedorControl, &ProductoProveedorControl::ProveedorSelected, this, &frmProductosForm::UpdateProveedores);
        connect(productoProveedorControl, &ProductoProveedorControl::SetPrecioVenta, this, [=](double precioRecomendado){ this->ui->numPrecioVenta->setValue(precioRecomendado); });
        connect(productoProveedorControl, &ProductoProveedorControl::QuitarProveedor, this, &frmProductosForm::QuitarProveedor);
    }

    this->ui->txtProducto->setText(producto["Producto"].toString(""));
    this->ui->txtCodigoBarras->setText(producto["CodigoBarras"].toString(""));
    this->ui->cmbIVA->setCurrentIndex(std::max(0, Util::FindInModel(&this->ivaModel, producto["IVA"].toDouble(0))));
    this->ui->numPrecioVenta->setValue(producto["PrecioVenta"].toDouble(0));
    this->categoriasTree->SelectItemByIndex(Util::FindInModel(&this->categoriasModel, producto["CategoriaId"].toInt(0)));
    this->ui->txtMarca->setText(producto["Marca"].toString(""));
    this->ui->txtAnimales->setText(producto["Animales"].toString(""));
    this->ui->numStockMinimo->setValue(producto["StockMinimo"].toInt(0));

    this->UpdateProveedores();
}

void frmProductosForm::QuitarProveedor(ProductoProveedorControl *proveedor)
{
    for (int i = 0; i < this->ui->grpProveedores->layout()->count(); ++i) {
        ProductoProveedorControl *productoProveedorControl = (ProductoProveedorControl*)this->ui->grpProveedores->layout()->itemAt(i)->widget();
        if (productoProveedorControl == proveedor) {
            this->ui->grpProveedores->layout()->removeItem(this->ui->grpProveedores->layout()->itemAt(i));
            delete productoProveedorControl;
            this->UpdateProveedores();
            this->setFocus();
            break;
        }
    }
}

void frmProductosForm::UpdateProveedores()
{

    bool hayProveedorVacio = false;
    QJsonArray productoProveedoresArray;
    for (int i = 0; i < this->ui->grpProveedores->layout()->count(); ++i) {
        ProductoProveedorControl *productoProveedorControl = (ProductoProveedorControl*)this->ui->grpProveedores->layout()->itemAt(i)->widget();
        productoProveedorControl->SetIVA(this->producto["IVA"].toDouble(0));
        if (productoProveedorControl->productoProveedor["ProveedorId"].toInt(0) < 1) {
            hayProveedorVacio = true;
        } else {
            QJsonObject productoProveedor = productoProveedorControl->productoProveedor;
            productoProveedoresArray.append(productoProveedor);
        }
    }
    if (!hayProveedorVacio) {
        ProductoProveedorControl *productoProveedorControl = new class ProductoProveedorControl(this);
        productoProveedorControl->LoadProveedores(this->proveedores);
        connect(productoProveedorControl, &ProductoProveedorControl::ProveedorSelected, this, &frmProductosForm::UpdateProveedores);
        connect(productoProveedorControl, &ProductoProveedorControl::SetPrecioVenta, this, [=](double precioRecomendado){ this->ui->numPrecioVenta->setValue(precioRecomendado); });
        connect(productoProveedorControl, &ProductoProveedorControl::QuitarProveedor, this, &frmProductosForm::QuitarProveedor);
        this->ui->grpProveedores->layout()->addWidget(productoProveedorControl);
    }
    this->producto["Proveedores"] = productoProveedoresArray;

}

void frmProductosForm::SaveProducto()
{
    Util::PerformWebPost(this, "/productos/saveProducto", this->producto, [=](QJsonObject result) {
        emit this->UpdateListadoProductos();
        this->close();
    }, [=](QString errorMessage) {
        Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
    });
}
