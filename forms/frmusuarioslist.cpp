#include "frmusuarioslist.h"
#include "ui_frmusuarioslist.h"
#include <QResizeEvent>
#include "../util/util.h"
#include <QScrollBar>
#include <QTimer>
#include <QJsonDocument>

frmUsuariosList::frmUsuariosList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmUsuariosList)
{
    ui->setupUi(this);

    this->ui->txtFiltroSearch->setFocus();

    this->timerSearch = new QTimer(this);
    this->timerSearch->setSingleShot(true);
    connect(this->timerSearch, &QTimer::timeout, this, [this]{
        this->page = 1;
        this->LoadPage();
    });

    this->sortColumn = 1; // Nombre de usuario.
    this->sortDirection = Qt::SortOrder::AscendingOrder;
    this->page = 1;
    this->lastPageLoaded = false;
    this->requestId = 0;
    this->pageRequested = 0;
    this->pageLoaded = 0;

    this->ui->tblUsuarios->sortItems(this->sortColumn, this->sortDirection);

    this->ui->tblUsuarios->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblUsuarios->horizontalHeader()->setSortIndicatorShown(true);
    connect(ui->tblUsuarios->horizontalHeader(), &QHeaderView::sectionClicked, this, &frmUsuariosList::ColumnHeaderClicked);
    connect(ui->tblUsuarios->verticalScrollBar(), &QScrollBar::valueChanged, this, &frmUsuariosList::ListScrolled);

    this->LoadPage();

}

frmUsuariosList::~frmUsuariosList()
{
    delete ui;
    delete this->timerSearch;
}

void frmUsuariosList::closeParent()
{
    this->parentWidget()->close();
}

void frmUsuariosList::resizeEvent(QResizeEvent *resizeEvent)
{

    // Ocultamos la columna Id
    this->ui->tblUsuarios->hideColumn(0);

    QList<double> columnWidths;
    columnWidths.append(0);
    columnWidths.append(100);
    columnWidths.append(100);
    columnWidths.append(100);
    columnWidths.append(100);

    double totalColumnsWidth = 0;
    QList<double>::Iterator i;
    for (i = columnWidths.begin(); i != columnWidths.end(); ++i) {
        totalColumnsWidth += *i;
    }

    int gridWidth = this->ui->tblUsuarios->size().width() - 2; // -2 píxeles porque al parecer no tengo forma de sacar el tamaño del borde.

    for (int i = 0; i < this->ui->tblUsuarios->columnCount(); ++i) {
        int columnWidth = Util::Round((double)gridWidth * (double)columnWidths[i] / (double)totalColumnsWidth);
        if (i == this->ui->tblUsuarios->columnCount() - 1) {
            this->ui->tblUsuarios->setColumnWidth(i, 10);
        } else {
            this->ui->tblUsuarios->setColumnWidth(i, columnWidth);
        }
    }

}

void frmUsuariosList::ColumnHeaderClicked(int columnIndex) {
    if (this->sortColumn != columnIndex) {
        this->sortColumn = columnIndex;
        this->sortDirection = Qt::SortOrder::AscendingOrder;
    } else {
        if (this->sortDirection == Qt::SortOrder::AscendingOrder) {
            this->sortDirection = Qt::SortOrder::DescendingOrder;
        } else {
            this->sortDirection = Qt::SortOrder::AscendingOrder;
        }
    }
    this->ui->tblUsuarios->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblUsuarios->horizontalHeader()->setSortIndicatorShown(true);
    this->page = 1;
    this->ui->tblUsuarios->setRowCount(0);
    this->LoadPage();
}

QString frmUsuariosList::getColumnName(int columnId)
{
    switch (columnId) {
        case 0:
            return "Id";
        case 1:
            return "Username";
        case 2:
            return "Nombre";
        case 3:
            return "Apellidos";
        case 4:
            return "Rol";
        default:
            return "Username";
    }
}

void frmUsuariosList::LoadPage()
{
    this->requestId++;
    this->pageRequested = this->page;

    // Obj Request
    QJsonObject getUsuariosRequest;
    getUsuariosRequest["start"] = (this->page - 1) * this->limit;
    getUsuariosRequest["limit"] = this->limit;
    getUsuariosRequest["sort"] = frmUsuariosList::getColumnName(this->sortColumn);
    if (this->sortDirection == Qt::SortOrder::DescendingOrder) {
        getUsuariosRequest["dir"] = "DESC";
    } else {
        getUsuariosRequest["dir"] = "ASC";
    }
    getUsuariosRequest["filtro_Search"] = this->ui->txtFiltroSearch->text();
    int requestId = this->requestId;
    Util::PerformWebPost(this, "/usuarios/getUsuarios", getUsuariosRequest, [=](QJsonObject response) {
        if (this->requestId == requestId) {
            this->AddPage(response);
        }
    }, [](QString errorMessage) {
        Util::ErrorAlert("Gestión de usuarios", errorMessage);
    });

}

void frmUsuariosList::AddPage(QJsonObject page)
{
    int loadedPage = page["page"].toInt(0);
    int total = page["total"].toInt(0);
    int lastPage = Util::Ceil((double)total / (double)this->limit);
    if (loadedPage == lastPage) {
        this->lastPageLoaded = true;
    } else {
        this->lastPageLoaded = false;
    }
    if (loadedPage == 1) {
        this->ui->tblUsuarios->setRowCount(0);
    }
    QJsonArray usuarios = page["collection"].toArray();
    QJsonArray::Iterator i;
    for (i = usuarios.begin(); i != usuarios.end(); ++i) {
        QJsonObject usuario = (*i).toObject();

        int row = ui->tblUsuarios->rowCount();
        ui->tblUsuarios->insertRow(row);

        // Id
        QTableWidgetItem *cell = new QTableWidgetItem(QString::number(usuario["Id"].toInt(0)));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblUsuarios->setItem(row, 0, cell);

        // Nombre de usuario
        cell = new QTableWidgetItem(usuario["Username"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblUsuarios->setItem(row, 1, cell);

        // Nombre
        cell = new QTableWidgetItem(usuario["Nombre"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblUsuarios->setItem(row, 2, cell);

        // Apellidos
        cell = new QTableWidgetItem(usuario["Apellidos"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblUsuarios->setItem(row, 3, cell);

        // Rol
        cell = new QTableWidgetItem(usuario["Rol"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblUsuarios->setItem(row, 4, cell);

    }

    // Obtenemos el scroll vertical para determinar si hay que cargar otra página.
    // El scroll vertical no se actualiza hasta que no termina de pintarse el widget
    QTimer::singleShot(1, this, [this](){

        QScrollBar *vScroll = this->ui->tblUsuarios->verticalScrollBar();
        int verticalMaxValue = vScroll->maximum();
        int verticalCurrentValue = vScroll->value();

        if (verticalMaxValue - verticalCurrentValue < 100) {
            if ((!this->lastPageLoaded) && (this->pageRequested == this->pageLoaded)) {
                this->page++;
                this->LoadPage();
            }
        }

    });

    this->pageLoaded = page["page"].toInt(0);
}

void frmUsuariosList::ListScrolled(int position) {

    QScrollBar *vScroll = this->ui->tblUsuarios->verticalScrollBar();
    int verticalMaxValue = vScroll->maximum();
    int verticalCurrentValue = vScroll->value();

    if (verticalMaxValue - verticalCurrentValue < 100) {
        if ((!this->lastPageLoaded) && (this->pageRequested == this->pageLoaded)) {
            this->page++;
            this->LoadPage();
        }
    }

}

void frmUsuariosList::SearchChanged()
{
    this->timerSearch->stop();
    this->timerSearch->start(300);
}

void frmUsuariosList::NuevoUsuario()
{
    emit this->AbrirUsuario(0);
}

void frmUsuariosList::ModificarUsuario()
{
    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblUsuarios->selectedItems().count())
    {
        int row = this->ui->tblUsuarios->selectedItems().last()->row();
        if (this->ui->tblUsuarios->currentRow() > -1) {
            row = this->ui->tblUsuarios->currentRow();
        }
        int registroId = this->ui->tblUsuarios->item(row, 0)->text().toInt();
        emit this->AbrirUsuario(registroId);
    }
    else
    {
        Util::ErrorAlert("Modificar usuario", "Seleccione un usuario para modificar.");
    }
}

void frmUsuariosList::ActualizarListado()
{
    this->page = 1;
    this->LoadPage();
}

void frmUsuariosList::DeleteUsuarios()
{
    if (this->ui->tblUsuarios->selectedItems().count() > 0) {
        if (Util::WarningConfirm("Eliminar usuarios", "¿Está seguro de que quiere eliminar los usuarios seleccionados?")) {
            QJsonObject deleteUsuariosRequest;
            QJsonArray usuariosIds;
            for (int i = 0; i < this->ui->tblUsuarios->selectedItems().count(); ++i) {
                int row = this->ui->tblUsuarios->selectedItems().at(i)->row();
                int registroId = this->ui->tblUsuarios->item(row, 0)->text().toInt();
                if (!usuariosIds.contains(registroId)) {
                    usuariosIds.append(registroId);
                }
            }
            deleteUsuariosRequest["UsuariosIds"] = usuariosIds;
            Util::PerformWebPost(this, "/usuarios/deleteUsuarios", deleteUsuariosRequest, [=](QJsonObject result) {
                this->ActualizarListado();
            }, [=](QString errorMessage) {
                Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
            });

        }
    } else {
        Util::ErrorAlert("Eliminar usuarios", "Seleccione al menos un usuario para eliminar.");
    }
}
