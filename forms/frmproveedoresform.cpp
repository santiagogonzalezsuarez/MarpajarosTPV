#include "frmproveedoresform.h"
#include "ui_frmproveedoresform.h"
#include "../util/util.h"

frmProveedoresForm::frmProveedoresForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmProveedoresForm)
{
    ui->setupUi(this);

    // Eventos para actualizar valores
    connect(this->ui->txtNombre, &QLineEdit::textChanged, this, [=](){ this->proveedor["Nombre"] = this->ui->txtNombre->text(); });
    connect(this->ui->txtTelefono, &QLineEdit::textChanged, this, [=](){ this->proveedor["Telefono"] = this->ui->txtTelefono->text(); });
    connect(this->ui->txtEmail, &QLineEdit::textChanged, this, [=](){ this->proveedor["Email"] = this->ui->txtEmail->text(); });
    connect(this->ui->txtPaginaWeb, &QLineEdit::textChanged, this, [=](){ this->proveedor["PaginaWeb"] = this->ui->txtPaginaWeb->text(); });
    connect(this->ui->txtDireccion, &QPlainTextEdit::textChanged, this, [=](){ this->proveedor["Direccion"] = this->ui->txtDireccion->toPlainText(); });
    connect(this->ui->txtHorarios, &QPlainTextEdit::textChanged, this, [=](){ this->proveedor["Horarios"] = this->ui->txtHorarios->toPlainText(); });
    connect(this->ui->txtObservaciones, &QPlainTextEdit::textChanged, this, [=](){ this->proveedor["Observaciones"] = this->ui->txtObservaciones->toPlainText(); });
    connect(this->ui->chkMostrarEnInformeVentas, &QCheckBox::stateChanged, this, [=]() { this->proveedor["MostrarEnInformeVentas"] = this->ui->chkMostrarEnInformeVentas->isChecked(); });

}

frmProveedoresForm::~frmProveedoresForm()
{
    delete ui;
}

void frmProveedoresForm::closeParent()
{
    this->parentWidget()->close();
}

void frmProveedoresForm::LoadProveedor(QJsonObject proveedor)
{
    this->proveedor = proveedor;

    this->ui->txtNombre->setText(proveedor["Nombre"].toString(""));
    this->ui->txtTelefono->setText(proveedor["Telefono"].toString(""));
    this->ui->txtEmail->setText(proveedor["Email"].toString(""));
    this->ui->txtPaginaWeb->setText(proveedor["PaginaWeb"].toString(""));
    this->ui->txtDireccion->setPlainText(proveedor["Direccion"].toString(""));
    this->ui->txtHorarios->setPlainText(proveedor["Horarios"].toString(""));
    this->ui->txtObservaciones->setPlainText(proveedor["Observaciones"].toString(""));
    this->ui->chkMostrarEnInformeVentas->setChecked(proveedor["MostrarEnInformeVentas"].toBool(false));
}

void frmProveedoresForm::SaveProveedor()
{
    Util::PerformWebPost(this, "/proveedores/saveProveedor", this->proveedor, [=](QJsonObject result) {
        emit this->UpdateListadoProveedores();
        this->close();
    }, [=](QString errorMessage) {
        Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
    });
}
