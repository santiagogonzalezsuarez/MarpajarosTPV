#ifndef FRMPRODUCTOSLIST_H
#define FRMPRODUCTOSLIST_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

namespace Ui {
class frmProductosList;
}

class frmProductosList : public QDialog
{
    Q_OBJECT

public:
    explicit frmProductosList(QWidget *parent = nullptr);
    ~frmProductosList();
    int sortColumn;
    Qt::SortOrder sortDirection;
    int page;
    const int limit = 20;

public slots:
    void SearchChanged();
    void NuevoProducto();
    void ModificarProducto();
    void ActualizarListado();

signals:
    void UpdateListadoProductos();
    void AbrirProducto(int ProductoId);
    void DisableMainWindow();
    void EnableMainWindow();

private slots:
    void closeParent();
    void LoadPage();
    void ColumnHeaderClicked(int columnIndex);
    void ListScrolled(int position);
    void GridSelectionChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void DeleteProductos();
    void ActualizarImagen();
    void EliminarImagen();

private:
    Ui::frmProductosList *ui;
    void resizeEvent(QResizeEvent*);
    QString getColumnName(int columnId);
    void AddPage(QJsonObject page);
    bool lastPageLoaded;
    QTimer *timerSearch;
    int requestId;
    int pageRequested;
    int pageLoaded;
    void ActualizarImagenProducto(int ProductoId, QString fileName);

    int productoImagenId = 0;
    int productoImagenRequestId = 0;
    bool recargarImagen = false;
    bool cargandoImagen = false;
    QProcess *fileSelectionProcess;
};

#endif // FRMPRODUCTOSLIST_H
