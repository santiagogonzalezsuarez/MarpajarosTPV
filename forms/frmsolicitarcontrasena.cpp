#include "frmsolicitarcontrasena.h"
#include "ui_frmsolicitarcontrasena.h"
#include "../util/util.h"

frmSolicitarContrasena::frmSolicitarContrasena(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSolicitarContrasena)
{
    ui->setupUi(this);
    this->ui->txtPassword->setFocus();
}

frmSolicitarContrasena::~frmSolicitarContrasena()
{
    delete ui;
}

void frmSolicitarContrasena::SetLabelTitle(QString text)
{
    this->ui->lblRequest->setText(text);
}

void frmSolicitarContrasena::ValidatePassword()
{
    this->setDisabled(true);
    QJsonObject loginRequest;
    loginRequest["Username"] = this->username;
    loginRequest["Password"] = this->ui->txtPassword->text();

    Util::PerformWebPost(this, "/login/login", loginRequest, [=](QJsonObject response) {
        this->setDisabled(false);
        this->accept();
    }, [=](QString errorMessage){
        Util::ErrorAlert("Iniciar sesión", errorMessage);
        this->setDisabled(false);
        this->ui->txtPassword->setFocus();
    });
}
