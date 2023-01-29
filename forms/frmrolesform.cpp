#include "frmrolesform.h"
#include "ui_frmrolesform.h"
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include "../util/flowlayout.h"
#include "../util/util.h"
#include <QJsonDocument>
#include <QList>

frmRolesForm::frmRolesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRolesForm)
{
    ui->setupUi(this);
    this->ui->txtRol->setFocus();

    // Enlazamos los campos con el objeto Json
    connect(this->ui->txtRol, &QLineEdit::textChanged, this, [=](){ this->rol["Rol"] = this->ui->txtRol->text(); });
}

frmRolesForm::~frmRolesForm()
{
    delete ui;
}

void frmRolesForm::closeParent()
{
    this->parentWidget()->close();
}

void frmRolesForm::LoadModulos(QJsonArray modulos)
{
    QCheckBox *lastCheck = nullptr;
    for (QJsonArray::Iterator i = modulos.begin(); i != modulos.end(); ++i) {
        QJsonObject modulo = (*i).toObject();
        QGroupBox *grpModulo = new QGroupBox();
        grpModulo->setTitle(modulo["Modulo"].toString(""));
        grpModulo->setProperty("MPisModule", true);
        this->ui->formContainer->addWidget(grpModulo);
        QJsonArray permisos = modulo["Permisos"].toArray();
        FlowLayout *grpModuloLayout = new FlowLayout();
        grpModulo->setLayout(grpModuloLayout);

        for (QJsonArray::Iterator j = permisos.begin(); j != permisos.end(); ++j) {
            QJsonObject permiso = (*j).toObject();
            QCheckBox *chkPermiso = new QCheckBox();
            chkPermiso->setText(permiso["Permiso"].toString(""));
            chkPermiso->setMinimumWidth(250);
            int permisoId = permiso["Id"].toInt(0);
            chkPermiso->setProperty("PermisoId", permisoId);
            connect(chkPermiso, &QCheckBox::clicked, this, [=]() {
                QJsonArray permisos = this->rol["PermisosIds"].toArray();
                if (chkPermiso->isChecked()) {
                    if (!permisos.contains(permisoId)) {
                        permisos.append(permisoId);
                    }
                } else {
                    if (permisos.contains(permisoId)) {
                        for (int i = permisos.count() - 1; i >= 0; --i) {
                            if (permisos.at(i).isDouble() && permisos.at(i).toInt(0) == permisoId) {
                                permisos.removeAt(i);
                                break;
                            }
                        }
                    }
                }
                this->rol["PermisosIds"] = permisos;
            });
            grpModuloLayout->addWidget(chkPermiso);
            lastCheck = chkPermiso;
        }
    }
    if (lastCheck != nullptr) {
        // Colocamos los botones aceptar y cancelar al final del órden de tabulación
        QWidget::setTabOrder(lastCheck, this->ui->btnAceptar);
        QWidget::setTabOrder(this->ui->btnAceptar, this->ui->btnCancelar);
    }
}

void frmRolesForm::LoadRol(QJsonObject rol)
{
    this->ui->txtRol->setText(rol["Rol"].toString(""));
    for (int i = 0; i < this->ui->formContainer->count(); ++i) {
        QLayoutItem *item = this->ui->formContainer->itemAt(i);
        if (item->widget() != nullptr && item->widget()->property("MPisModule").toBool()) {
            QGroupBox *grpModulo = (QGroupBox*)item->widget();
            for (int j = 0; j < grpModulo->layout()->count(); ++j) {
                QLayoutItem *item = grpModulo->layout()->itemAt(j);
                if (item->widget() != nullptr && item->widget()->property("PermisoId").toInt(0) > 0) {
                    QCheckBox *chkPermiso = (QCheckBox*)item->widget();
                    int PermisoId = chkPermiso->property("PermisoId").toInt(0);
                    if (rol["PermisosIds"].toArray().contains(PermisoId)) {
                        chkPermiso->setCheckState(Qt::CheckState::Checked);
                    } else {
                        chkPermiso->setCheckState(Qt::CheckState::Unchecked);
                    }
                }
            }
        }
    }

    this->rol = rol;
}

void frmRolesForm::SaveRol()
{
    Util::PerformWebPost(this, "/roles/saveRol", this->rol, [=](QJsonObject result) {
        emit this->UpdateListadoRoles();
        this->close();
    }, [=](QString errorMessage) {
        Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
    });
}
