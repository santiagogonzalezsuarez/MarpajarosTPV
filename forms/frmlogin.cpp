#include "frmlogin.h"
#include "ui_frmlogin.h"
#include "../util/util.h"
#include <QTimer>

frmLogin::frmLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmLogin)
{
    ui->setupUi(this);

    QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

    this->ui->txtNombreUsuario->setFocus();

}

frmLogin::~frmLogin()
{
    delete ui;
}

void frmLogin::doLogin()
{
    this->setDisabled(true);
    QJsonObject loginRequest;
    loginRequest["Username"] = this->ui->txtNombreUsuario->text();
    loginRequest["Password"] = this->ui->txtContrasena->text();

    Util::PerformWebPost(this, "/login/login", loginRequest, [=](QJsonObject response) {
        Util::accessToken = response["Token"].toString(nullptr);
        this->setDisabled(false);
        emit this->successfulLogin(response);
        this->close();
    }, [=](QString errorMessage){
        Util::ErrorAlert("Iniciar sesión", errorMessage);
        this->setDisabled(false);
    });
}
