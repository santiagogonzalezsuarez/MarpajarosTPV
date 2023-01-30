#include "frmconfiguracion.h"
#include "ui_frmconfiguracion.h"
#include "../util/util.h"

frmConfiguracion::frmConfiguracion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmConfiguracion)
{
    ui->setupUi(this);
    this->ui->txtServiceUrl->setFocus();

    this->LoadData();

}

frmConfiguracion::~frmConfiguracion()
{
    delete ui;
}

void frmConfiguracion::LoadData()
{
    this->ui->txtServiceUrl->setText(Util::GetConfigString("API.URL"));
    this->ui->txtNumCaja->setValue(Util::GetConfigInt("Caja.CajaActiva", 1));
}

void frmConfiguracion::SaveData()
{
    if (this->ui->txtServiceUrl->text() == "") {
        Util::ErrorAlert("Configuración", "Debe especificar una URL para la API.");
        return;
    }
    if (this->ui->txtNumCaja->value() < 1) {
        Util::ErrorAlert("Configuración", "El número de caja debe ser un número entre 1 y 99");
        return;
    }
    Util::SetConfigString("API.URL", this->ui->txtServiceUrl->text());
    Util::SetConfigInt("Caja.CajaActiva", this->ui->txtNumCaja->value());
    Util::SaveConfig();
    this->accept();
}
