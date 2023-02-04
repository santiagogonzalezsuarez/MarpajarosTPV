#ifndef FRMSOLICITARCONTRASENA_H
#define FRMSOLICITARCONTRASENA_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class frmSolicitarContrasena;
}

class frmSolicitarContrasena : public QDialog
{
    Q_OBJECT

public:
    explicit frmSolicitarContrasena(QWidget *parent = nullptr);
    ~frmSolicitarContrasena();
    QString username;
    void SetLabelTitle(QString text);

public slots:
    void ValidatePassword();

private:
    Ui::frmSolicitarContrasena *ui;
};

#endif // FRMSOLICITARCONTRASENA_H
