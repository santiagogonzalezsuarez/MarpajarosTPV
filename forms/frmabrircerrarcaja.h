#ifndef FRMABRIRCERRARCAJA_H
#define FRMABRIRCERRARCAJA_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class frmAbrirCerrarCaja;
}

class frmAbrirCerrarCaja : public QDialog
{
    Q_OBJECT

public:
    explicit frmAbrirCerrarCaja(QWidget *parent = nullptr);
    ~frmAbrirCerrarCaja();
    QJsonObject ultimaAperturaCaja;
    void CuadrePredeterminado();

public slots:
    void CalcularImportes();

private:
    Ui::frmAbrirCerrarCaja *ui;

private slots:
    void CashValuesChanged();
    void SaveCuadreCaja();
};

#endif // FRMABRIRCERRARCAJA_H
