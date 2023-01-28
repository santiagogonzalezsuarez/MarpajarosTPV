#ifndef FRMUSUARIOSLIST_H
#define FRMUSUARIOSLIST_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class frmUsuariosList;
}

class frmUsuariosList : public QDialog
{
    Q_OBJECT

public:
    explicit frmUsuariosList(QWidget *parent = nullptr);
    ~frmUsuariosList();
    int sortColumn;
    Qt::SortOrder sortDirection;
    int page;
    const int limit = 20;

public slots:
    void SearchChanged();
    void NuevoUsuario();
    void ModificarUsuario();
    void ActualizarListado();

signals:
    void AbrirUsuario(int UsuarioId);

private slots:
    void closeParent();
    void LoadPage();
    void ColumnHeaderClicked(int columnIndex);
    void ListScrolled(int position);
    void DeleteUsuarios();

private:
    Ui::frmUsuariosList *ui;
    void resizeEvent(QResizeEvent*);
    QString getColumnName(int columnId);
    void AddPage(QJsonObject page);
    bool lastPageLoaded;
    QTimer *timerSearch;
    int requestId;
    int pageRequested;
    int pageLoaded;
};

#endif // FRMUSUARIOSLIST_H
