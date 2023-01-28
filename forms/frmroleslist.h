#ifndef FRMROLESLIST_H
#define FRMROLESLIST_H

#include <QDialog>

namespace Ui {
class frmRolesList;
}

class frmRolesList : public QDialog
{
    Q_OBJECT

public:
    explicit frmRolesList(QWidget *parent = nullptr);
    ~frmRolesList();

private:
    Ui::frmRolesList *ui;
};

#endif // FRMROLESLIST_H
