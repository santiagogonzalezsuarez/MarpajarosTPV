#ifndef FRMCONFIGURACION_H
#define FRMCONFIGURACION_H

#include <QDialog>

namespace Ui {
class frmConfiguracion;
}

class frmConfiguracion : public QDialog
{
    Q_OBJECT

public:
    explicit frmConfiguracion(QWidget *parent = nullptr);
    ~frmConfiguracion();
    void LoadData();

private slots:
    void SaveData();

private:
    Ui::frmConfiguracion *ui;
};

#endif // FRMCONFIGURACION_H
