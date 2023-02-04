#include "frmabrircerrarcaja.h"
#include "ui_frmabrircerrarcaja.h"
#include <QSpinBox>
#include "../util/util.h"
#include <QLocale>

frmAbrirCerrarCaja::frmAbrirCerrarCaja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmAbrirCerrarCaja)
{
    ui->setupUi(this);
    this->ui->numTotal->setFocus();
    this->ui->numTotal->selectAll();

    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    for (QList<QSpinBox*>::Iterator i = spinBoxes.begin(); i != spinBoxes.end(); ++i) {
        QSpinBox *spinBox = *i;
        if (!spinBox->property("cashValue").isNull()) {
            connect(spinBox, &QSpinBox::valueChanged, this, &frmAbrirCerrarCaja::CashValuesChanged);
        }
    }
}

frmAbrirCerrarCaja::~frmAbrirCerrarCaja()
{
    delete ui;
}

void frmAbrirCerrarCaja::CashValuesChanged()
{
    double cashCount = 0;
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    for (QList<QSpinBox*>::Iterator i = spinBoxes.begin(); i != spinBoxes.end(); ++i) {
        QSpinBox *spinBox = *i;
        if (!spinBox->property("cashValue").isNull()) {
            cashCount += spinBox->property("cashValue").toDouble() * (double)spinBox->value();
        }
    }
    this->ui->numTotal->setValue(cashCount);
}

void frmAbrirCerrarCaja::CalcularImportes()
{
    if (this->ultimaAperturaCaja["CajaAbierta"].toBool(false)) {
        this->ui->lblImporteInicialLabel->setHidden(false);
        this->ui->lblImporteInicial->setHidden(false);
        this->ui->lblVentasLabel->setHidden(false);
        this->ui->lblVentas->setHidden(false);
        this->ui->lblDeberiaHaberLabel->setHidden(false);
        this->ui->lblDeberiaHaber->setHidden(false);
        this->ui->lblDescuadreLabel->setHidden(false);
        this->ui->lblDescuadre->setHidden(false);
        QLocale curLocale;
        this->ui->lblImporteInicial->setText(curLocale.toString(this->ultimaAperturaCaja["ImporteApertura"].toDouble(0), 'f', 2) + " €");
        this->ui->lblVentas->setText(curLocale.toString(this->ultimaAperturaCaja["ImporteVendido"].toDouble(0), 'f', 2) + " €");
        this->ui->lblDeberiaHaber->setText(curLocale.toString(this->ultimaAperturaCaja["ImporteApertura"].toDouble(0) + this->ultimaAperturaCaja["ImporteVendido"].toDouble(0), 'f', 2) + " €");
        double importeCaja = this->ui->numTotal->value();
        this->ui->lblDescuadre->setText(curLocale.toString(importeCaja - (this->ultimaAperturaCaja["ImporteApertura"].toDouble(0) + this->ultimaAperturaCaja["ImporteVendido"].toDouble(0)), 'f', 2) + " €");
    } else {
        this->ui->lblImporteInicialLabel->setHidden(true);
        this->ui->lblImporteInicial->setHidden(true);
        this->ui->lblVentasLabel->setHidden(true);
        this->ui->lblVentas->setHidden(true);
        this->ui->lblDeberiaHaberLabel->setHidden(true);
        this->ui->lblDeberiaHaber->setHidden(true);
        this->ui->lblDescuadreLabel->setHidden(true);
        this->ui->lblDescuadre->setHidden(true);
    }
}

void frmAbrirCerrarCaja::SaveCuadreCaja()
{
    if (this->ultimaAperturaCaja["CajaAbierta"].toBool(false)) {
        double descuadre = this->ui->numTotal->value() - (this->ultimaAperturaCaja["ImporteApertura"].toDouble(0) + this->ultimaAperturaCaja["ImporteVendido"].toDouble(0));
        descuadre = Util::FixDoubleForCurrency(descuadre);
        QLocale curLocale;
        QString message;
        if (descuadre < 0) {
            double positivo = 0 - descuadre;
            positivo = Util::FixDoubleForCurrency(positivo);
            message = "Se va a cerrar la caja registrando una pérdida de " + curLocale.toString(positivo, 'f', 2) + " €. ¿Es correcto?";
        } else if (descuadre > 0) {
            message = "Se va a cerrar la caja con un descuadre positivo de " + curLocale.toString(descuadre, 'f', 2) + " €. ¿Es correcto?";
        } else {
            message = "Se va a cerrar la caja sin ningún descuadre. ¿Es correcto?";
        }
        if (Util::InfoConfirm("Cierre de caja", message)) {
            // Aplicamos redondeo a 2 decimales con los importes para evitar problemas a la hora de operar con valores de coma flotante.
            double importeVendido = Util::FixDoubleForCurrency(this->ultimaAperturaCaja["ImporteVendido"].toDouble(0));
            double importeCierre = Util::FixDoubleForCurrency(this->ui->numTotal->value());
            QJsonObject cerrarCajaRequest;
            cerrarCajaRequest["CajaId"] = Util::GetConfigInt("Caja.CajaActiva");
            cerrarCajaRequest["ImporteVendido"] = importeVendido;
            cerrarCajaRequest["ImporteCierre"] = importeCierre;
            Util::PerformWebPost(this, "/caja/cerrarCaja", cerrarCajaRequest, [=](QJsonObject result) {
                if (result["Correcto"].toBool(false)) {
                    this->accept();
                } else {
                    Util::ErrorAlert("Cierre de caja", "Error desconocido al cerrar la caja.");
                }
            }, [](QString errorMessage) {
                Util::ErrorAlert("Cierre de caja", errorMessage);
            });
        }
    } else {
        QLocale curLocale;
        if (Util::InfoConfirm("Apertura de caja", "Se va a abrir la caja con " + curLocale.toString(this->ui->numTotal->value(), 'f', 2) + " €. ¿Es correcto?")) {
            // Aplicamos redondeo a 2 decimales con los importes para evitar problemas a la hora de operar con valores de coma flotante.
            double importeInicial = Util::FixDoubleForCurrency(this->ui->numTotal->value());
            QJsonObject abrirCajaRequest;
            abrirCajaRequest["CajaId"] = Util::GetConfigInt("Caja.CajaActiva");
            abrirCajaRequest["ImporteInicial"] = importeInicial;
            Util::PerformWebPost(this, "/caja/abrirCaja", abrirCajaRequest, [=](QJsonObject result) {
                if (result["Correcto"].toBool(false)) {
                    this->accept();
                } else {
                    Util::ErrorAlert("Apertura de caja", "Error desconocido al abrir la caja.");
                }
            }, [](QString errorMessage) {
                Util::ErrorAlert("Apertura de caja", errorMessage);
            });
        }
    }
}

void frmAbrirCerrarCaja::CuadrePredeterminado()
{
    double totalCaja = this->ultimaAperturaCaja["ImporteApertura"].toDouble(0) + this->ultimaAperturaCaja["ImporteVendido"].toDouble(0);
    this->ui->numTotal->setValue(totalCaja);
}
