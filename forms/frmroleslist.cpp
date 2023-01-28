#include "frmroleslist.h"
#include "ui_frmroleslist.h"

frmRolesList::frmRolesList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRolesList)
{
    ui->setupUi(this);
}

frmRolesList::~frmRolesList()
{
    delete ui;
}
