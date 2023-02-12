#include "productoproveedorcontrol.h"
#include "ui_productoproveedorcontrol.h"
#include "../util/crelaxeddoublespinbox.h"
#include "../util/util.h"

ProductoProveedorControl::ProductoProveedorControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductoProveedorControl)
{
    ui->setupUi(this);
    this->proveedoresComboModel = nullptr;

    // Enlazamos eventos para modificar JSON:
    this->productoProveedor["PorcentajeGanancia"] = 33.0f;
    this->ui->numPorcentajeGanancia->setValue(this->productoProveedor["PorcentajeGanancia"].toDouble(0));

    connect(this->ui->txtReferencia, &QLineEdit::textChanged, this, [=](){ this->productoProveedor["Referencia"] = this->ui->txtReferencia->text(); emit this->ProveedorSelected(); });
    connect(this->ui->numPorcentajeGanancia, &CRelaxedDoubleSpinBox::valueChanged, this, [=](double value){ this->productoProveedor["PorcentajeGanancia"] = Util::FixDoubleForCurrency(value); this->UpdatePrecioRecomendado(); emit this->ProveedorSelected(); });
    connect(this->ui->numPrecioCompra, &CRelaxedDoubleSpinBox::valueChanged, this, [=](double value){ this->productoProveedor["PrecioCompra"] = Util::FixDoubleForCurrency(value); this->UpdatePrecioRecomendado(); emit this->ProveedorSelected(); });
    connect(this->ui->txtObservaciones, &QPlainTextEdit::textChanged, this, [=](){ this->productoProveedor["Observaciones"] = this->ui->txtObservaciones->toPlainText(); emit this->ProveedorSelected(); });

}

ProductoProveedorControl::~ProductoProveedorControl()
{
    delete ui;
    if (this->proveedoresComboModel != nullptr)
    {
        delete this->proveedoresComboModel;
    }
}

void ProductoProveedorControl::UpdatePrecioRecomendado()
{
    double precioCompra = this->ui->numPrecioCompra->value();
    double porcentajeGanancia = this->ui->numPorcentajeGanancia->value();
    double precioRecomendado = Util::FixDoubleForCurrency(precioCompra * (1.f + (this->IVA / 100.f)) * (1.f + (porcentajeGanancia / 100.f)));
    double precioConIVA = Util::FixDoubleForCurrency(precioCompra * (1.f + (this->IVA / 100.f)));
    QLocale curLocale;
    this->ui->txtPrecioRecomendado->setText(curLocale.toString(precioRecomendado, 'f', 2) + " €");
    this->ui->txtPrecioConIVA->setText(curLocale.toString(precioConIVA, 'f', 2) + " €");
}

void ProductoProveedorControl::SetIVA(double IVA)
{
    this->IVA = IVA;
    this->UpdatePrecioRecomendado();
}

void ProductoProveedorControl::LoadProveedores(QJsonArray proveedores)
{
    if (this->proveedoresComboModel != nullptr) {
        this->ui->cmbProveedor->setModel(nullptr); // Liberamos el modelo.
        delete this->proveedoresComboModel;
    }
    this->proveedoresComboModel = new QStandardItemModel();
    QJsonArray::Iterator i;
    for (i = proveedores.begin(); i != proveedores.end(); ++i) {
        QJsonObject proveedor = (*i).toObject();
        QStandardItem *item = new QStandardItem(proveedor["Proveedor"].toString(""));
        QVariant value = QVariant(proveedor["Id"].toInt());
        item->setData(value);
        this->proveedoresComboModel->appendRow(item);
    }
    this->ui->cmbProveedor->setModel(this->proveedoresComboModel);
    this->ui->cmbProveedor->setCurrentIndex(-1);
    connect(this->ui->cmbProveedor, &QComboBox::currentIndexChanged, this, &ProductoProveedorControl::cmbProveedorCurrentIndexChanged);
}

void ProductoProveedorControl::cmbProveedorCurrentIndexChanged(int index)
{
    this->productoProveedor["ProveedorId"] = this->proveedoresComboModel->item(index)->data().toInt();
    if (index != -1) {
        this->ui->txtReferencia->setEnabled(true);
        this->ui->numPrecioCompra->setEnabled(true);
        this->ui->numPorcentajeGanancia->setEnabled(true);
        this->ui->btnEstablecerPrecioVenta->setEnabled(true);
        this->ui->txtObservaciones->setEnabled(true);
        this->ui->btnQuitarProveedor->setEnabled(true);
        emit this->ProveedorSelected();
    }
}

void ProductoProveedorControl::btnSetPrecioVentaClicked()
{
    double precioCompra = this->ui->numPrecioCompra->value();
    double porcentajeGanancia = this->ui->numPorcentajeGanancia->value();
    double precioRecomendado = Util::FixDoubleForCurrency(precioCompra * (1.f + (this->IVA / 100.f)) * (1.f + (porcentajeGanancia / 100.f)));
    emit this->SetPrecioVenta(precioRecomendado);
}

void ProductoProveedorControl::LoadProductoProveedor(QJsonObject productoProveedor)
{
    this->productoProveedor = productoProveedor;
    this->ui->cmbProveedor->setCurrentIndex(Util::FindInModel(this->proveedoresComboModel, productoProveedor["ProveedorId"].toInt(0)));
    this->ui->txtReferencia->setText(productoProveedor["Referencia"].toString(""));
    this->ui->numPrecioCompra->setValue(productoProveedor["PrecioCompra"].toDouble(0));
    this->ui->numPorcentajeGanancia->setValue(productoProveedor["PorcentajeGanancia"].toDouble(0));
    this->ui->txtObservaciones->setPlainText(productoProveedor["Observaciones"].toString(""));
}

void ProductoProveedorControl::btnQuitarProveedorClicked()
{
    if (Util::WarningConfirm("Quitar proveedor", "¿Desea quitar este proveedor del producto?")) {
        emit this->QuitarProveedor(this);
    }
}
