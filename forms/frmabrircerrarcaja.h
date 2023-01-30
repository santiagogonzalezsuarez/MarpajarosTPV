#ifndef FRMABRIRCERRARCAJA_H
#define FRMABRIRCERRARCAJA_H

#include <QDialog>

namespace Ui {
class frmAbrirCerrarCaja;
}

class frmAbrirCerrarCaja : public QDialog
{
    Q_OBJECT

public:
    explicit frmAbrirCerrarCaja(QWidget *parent = nullptr);
    ~frmAbrirCerrarCaja();

private:
    Ui::frmAbrirCerrarCaja *ui;
};

#endif // FRMABRIRCERRARCAJA_H
