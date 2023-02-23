#ifndef FRMPROVEEDORESLIST_H
#define FRMPROVEEDORESLIST_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

namespace Ui {
class frmProveedoresList;
}

class frmProveedoresList : public QDialog
{
    Q_OBJECT

public:
    explicit frmProveedoresList(QWidget *parent = nullptr);
    ~frmProveedoresList();
    int sortColumn;
    Qt::SortOrder sortDirection;
    int page;
    const int limit = 20;

public slots:
    void SearchChanged();
    void NuevoProveedor();
    void ModificarProveedor();
    void ActualizarListado();

signals:
    void UpdateListadoProveedores();
    void AbrirProveedor(int ProveedorId);

private slots:
    void closeParent();
    void LoadPage();
    void ColumnHeaderClicked(int columnIndex);
    void ListScrolled(int position);
    void DeleteProveedores();

private:
    Ui::frmProveedoresList *ui;
    void resizeEvent(QResizeEvent*);
    QString getColumnName(int columnId);
    void AddPage(QJsonObject page);
    bool lastPageLoaded;
    QTimer *timerSearch;
    int requestId;
    int pageRequested;
    int pageLoaded;
};

#endif // FRMPROVEEDORESLIST_H
