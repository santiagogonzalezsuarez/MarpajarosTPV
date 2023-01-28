#ifndef FRMROLESLIST_H
#define FRMROLESLIST_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class frmRolesList;
}

class frmRolesList : public QDialog
{
    Q_OBJECT

public:
    explicit frmRolesList(QWidget *parent = nullptr);
    ~frmRolesList();
    int sortColumn;
    Qt::SortOrder sortDirection;
    int page;
    const int limit = 20;

public slots:
    void SearchChanged();
    void NuevoRol();
    void ModificarRol();
    void ActualizarListado();

signals:
    void AbrirRol(int RolId);

private slots:
    void closeParent();
    void LoadPage();
    void ColumnHeaderClicked(int columnIndex);
    void ListScrolled(int position);
    void DeleteRoles();

private:
    Ui::frmRolesList *ui;
    void resizeEvent(QResizeEvent *);
    QString getColumnName(int columnId);
    void AddPage(QJsonObject page);
    bool lastPageLoaded;
    QTimer *timerSearch;
    int requestId;
    int pageRequested;
    int pageLoaded;
};

#endif // FRMROLESLIST_H
