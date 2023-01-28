#include "frmroleslist.h"
#include "ui_frmroleslist.h"
#include <QResizeEvent>
#include "../util/util.h"
#include <QScrollBar>
#include <QTimer>
#include <QJsonObject>

frmRolesList::frmRolesList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRolesList)
{
    ui->setupUi(this);

    this->ui->txtFiltroSearch->setFocus();

    this->timerSearch = new QTimer(this);
    this->timerSearch->setSingleShot(true);
    connect(this->timerSearch, &QTimer::timeout, this, [this]{
        this->page = 1;
        this->LoadPage();
    });

}

frmRolesList::~frmRolesList()
{
    delete ui;
}
