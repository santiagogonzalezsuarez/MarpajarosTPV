#include "frmusuariosform.h"
#include "ui_frmusuariosform.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include "../util/util.h"
#include <QJsonDocument>
#include <QComboBox>

frmUsuariosForm::frmUsuariosForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmUsuariosForm)
{
    ui->setupUi(this);
    this->rolesComboModel = nullptr;
    ui->txtUsuario->setFocus();

    // Enlazamos los campos con el objeto Json
    connect(this->ui->txtUsuario, &QLineEdit::textChanged, this, [=](){ this->usuario["Username"] = this->ui->txtUsuario->text(); });
    connect(this->ui->txtContrasena, &QLineEdit::textChanged, this, [=](){ this->usuario["Password"] = this->ui->txtContrasena->text(); });
    connect(this->ui->txtNombre, &QLineEdit::textChanged, this, [=](){ this->usuario["Nombre"] = this->ui->txtNombre->text(); });
    connect(this->ui->txtApellidos, &QLineEdit::textChanged, this, [=](){ this->usuario["Apellidos"] = this->ui->txtApellidos->text(); });
    connect(this->ui->cmbRol, SIGNAL(currentIndexChanged(int)), this, SLOT(RolChanged(int)));
}

void frmUsuariosForm::RolChanged(int index) {
    this->usuario["RolId"] = this->rolesComboModel->item(index)->data().toInt();
}

frmUsuariosForm::~frmUsuariosForm()
{
    delete ui;
    if (this->rolesComboModel != nullptr)
    {
        delete this->rolesComboModel;
    }
}

void frmUsuariosForm::closeParent()
{
    this->parentWidget()->close();
}

void frmUsuariosForm::LoadRoles(QJsonArray roles)
{
    if (this->rolesComboModel != nullptr) {
        this->ui->cmbRol->setModel(nullptr); // Liberamos el modelo.
        delete this->rolesComboModel;
    }
    this->rolesComboModel = new QStandardItemModel();
    QJsonArray::Iterator i;
    for (i = roles.begin(); i != roles.end(); ++i) {
        QJsonObject rol = (*i).toObject();
        QStandardItem *item = new QStandardItem(rol["Rol"].toString(""));
        QVariant value = QVariant(rol["Id"].toInt());
        item->setData(value);
        this->rolesComboModel->appendRow(item);
    }
    this->ui->cmbRol->setModel(this->rolesComboModel);
}

void frmUsuariosForm::LoadUsuario(QJsonObject usuario)
{
    this->ui->txtUsuario->setText(usuario["Username"].toString(""));
    this->ui->txtContrasena->setText(usuario["Password"].toString(""));
    this->ui->txtNombre->setText(usuario["Nombre"].toString(""));
    this->ui->txtApellidos->setText(usuario["Apellidos"].toString(""));
    this->ui->cmbRol->setCurrentIndex(std::max(0, Util::FindInModel(this->rolesComboModel, usuario["RolId"].toInt(0))));
    this->usuario = usuario;

    // Si es un registro nuevo, establecemos el primer rol de la lista.
    this->usuario["RolId"] = this->rolesComboModel->item(this->ui->cmbRol->currentIndex())->data().toInt();
}

void frmUsuariosForm::SaveUsuario()
{
    if (this->usuario["Password"] == "-DoNotChange-") {
        QString nullPass = nullptr;
        this->usuario["Password"] = nullPass;
    }
    Util::PerformWebPost(this, "/usuarios/saveUsuario", this->usuario, [=](QJsonObject result) {
        emit this->UpdateListadoUsuarios();
        this->close();
    }, [=](QString errorMessage) {
        Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
    });
}
