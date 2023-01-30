#include "frmabrircerrarcaja.h"
#include "ui_frmabrircerrarcaja.h"

frmAbrirCerrarCaja::frmAbrirCerrarCaja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmAbrirCerrarCaja)
{
    ui->setupUi(this);
}

frmAbrirCerrarCaja::~frmAbrirCerrarCaja()
{
    delete ui;
}
