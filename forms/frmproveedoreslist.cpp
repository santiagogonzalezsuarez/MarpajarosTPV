#include "frmproveedoreslist.h"
#include "ui_frmproveedoreslist.h"
#include <QResizeEvent>
#include "../util/util.h"
#include <QScrollBar>
#include <QTimer>

frmProveedoresList::frmProveedoresList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmProveedoresList)
{
    ui->setupUi(this);

    this->ui->txtFiltroSearch->setFocus();

    this->timerSearch = new QTimer(this);
    this->timerSearch->setSingleShot(true);
    connect(this->timerSearch, &QTimer::timeout, this, [this]{
        this->page = 1;
        this->LoadPage();
    });

    this->sortColumn = 1; // Nombre
    this->sortDirection = Qt::SortOrder::AscendingOrder;
    this->page = 1;
    this->lastPageLoaded = false;
    this->requestId = 0;
    this->pageRequested = 0;
    this->pageLoaded = 0;

    this->ui->tblProveedores->sortItems(this->sortColumn, this->sortDirection);

    this->ui->tblProveedores->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblProveedores->horizontalHeader()->setSortIndicatorShown(true);
    connect(ui->tblProveedores->horizontalHeader(), &QHeaderView::sectionClicked, this, &frmProveedoresList::ColumnHeaderClicked);
    connect(ui->tblProveedores->verticalScrollBar(), &QScrollBar::valueChanged, this, &frmProveedoresList::ListScrolled);

    this->LoadPage();

}

frmProveedoresList::~frmProveedoresList()
{
    delete ui;
    delete this->timerSearch;
}

void frmProveedoresList::closeParent()
{
    this->parentWidget()->close();
}

void frmProveedoresList::resizeEvent(QResizeEvent *resizeEvent)
{

    // Ocultamos la columna Id
    this->ui->tblProveedores->hideColumn(0);

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

    int gridWidth = this->ui->tblProveedores->size().width() - 2; // -2 píxeles porque al parecer no tengo forma de sacar el tamaño del borde.

    for (int i = 0; i < this->ui->tblProveedores->columnCount(); ++i) {
        int columnWidth = Util::Round((double)gridWidth * (double)columnWidths[i] / (double)totalColumnsWidth);
        if (i == this->ui->tblProveedores->columnCount() - 1) {
            this->ui->tblProveedores->setColumnWidth(i, 10);
        } else {
            this->ui->tblProveedores->setColumnWidth(i, columnWidth);
        }
    }

}

void frmProveedoresList::ColumnHeaderClicked(int columnIndex)
{
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
    this->ui->tblProveedores->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblProveedores->horizontalHeader()->setSortIndicatorShown(true);
    this->page = 1;
    this->ui->tblProveedores->setRowCount(0);
    this->LoadPage();
}

QString frmProveedoresList::getColumnName(int columnId)
{
    switch (columnId) {
        case 0:
            return "Id";
        case 1:
            return "Nombre";
        case 2:
            return "Telefono";
        case 3:
            return "Email";
        case 4:
            return "PaginaWeb";
        default:
            return "Nombre";
    }
}

void frmProveedoresList::LoadPage()
{
    this->requestId++;
    this->pageRequested = this->page;

    // Obj Request
    QJsonObject getProveedoresRequest;
    getProveedoresRequest["start"] = (this->page - 1) * this->limit;
    getProveedoresRequest["limit"] = this->limit;
    getProveedoresRequest["sort"] = frmProveedoresList::getColumnName(this->sortColumn);
    if (this->sortDirection == Qt::SortOrder::DescendingOrder) {
        getProveedoresRequest["dir"] = "DESC";
    } else {
        getProveedoresRequest["dir"] = "ASC";
    }
    getProveedoresRequest["filtro_Search"] = this->ui->txtFiltroSearch->text();

    int requestId = this->requestId;
    Util::PerformWebPost(this, "/proveedores/getProveedores", getProveedoresRequest, [=](QJsonObject response) {
        if (this->requestId == requestId) {
            this->AddPage(response);
        }
    }, [](QString errorMessage) {
        Util::ErrorAlert("Listado de proveedores", errorMessage);
    });
}

void frmProveedoresList::AddPage(QJsonObject page)
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
        this->ui->tblProveedores->setRowCount(0);
    }
    QJsonArray proveedores = page["collection"].toArray();
    QJsonArray::Iterator i;
    for (i = proveedores.begin(); i != proveedores.end(); ++i) {
        QJsonObject proveedor = (*i).toObject();

        int row = ui->tblProveedores->rowCount();
        ui->tblProveedores->insertRow(row);

        // Id
        QTableWidgetItem *cell = new QTableWidgetItem(QString::number(proveedor["Id"].toInt(0)));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProveedores->setItem(row, 0, cell);

        // Nombre
        cell = new QTableWidgetItem(proveedor["Nombre"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProveedores->setItem(row, 1, cell);

        // Teléfono
        cell = new QTableWidgetItem(proveedor["Telefono"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProveedores->setItem(row, 2, cell);

        // Email
        cell = new QTableWidgetItem(proveedor["Email"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProveedores->setItem(row, 3, cell);

        // Página web
        cell = new QTableWidgetItem(proveedor["PaginaWeb"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProveedores->setItem(row, 4, cell);

    }

    // Obtenemos el scroll vertical para determinar si hay que cargar otra página.
    // El scroll vertical no se actualiza hasta que no termina de pintarse el widget.
    QTimer::singleShot(1, this, [this](){

        QScrollBar *vScroll = this->ui->tblProveedores->verticalScrollBar();
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

void frmProveedoresList::ListScrolled(int position)
{

    QScrollBar *vScroll = this->ui->tblProveedores->verticalScrollBar();
    int verticalMaxValue = vScroll->maximum();
    int verticalCurrentValue = vScroll->value();

    if (verticalMaxValue - verticalCurrentValue < 100) {
        if ((!this->lastPageLoaded) && (this->pageRequested == this->pageLoaded)) {
            this->page++;
            this->LoadPage();
        }
    }

}

void frmProveedoresList::SearchChanged()
{
    this->timerSearch->stop();
    this->timerSearch->start(300);
}

void frmProveedoresList::NuevoProveedor()
{
    emit this->AbrirProveedor(0);
}

void frmProveedoresList::ModificarProveedor()
{
    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblProveedores->selectedItems().count())
    {
        int row = this->ui->tblProveedores->selectedItems().last()->row();
        if (this->ui->tblProveedores->currentRow() > -1) {
            row = this->ui->tblProveedores->currentRow();
        }
        int registroId = this->ui->tblProveedores->item(row, 0)->text().toInt();
        emit this->AbrirProveedor(registroId);
    }
    else
    {
        Util::ErrorAlert("Modificar proveedor", "Seleccione un proveedor para modificar.");
    }
}

void frmProveedoresList::ActualizarListado()
{
    this->page = 1;
    this->LoadPage();
}

void frmProveedoresList::DeleteProveedores()
{
    if (this->ui->tblProveedores->selectedItems().count() > 0) {
        if (Util::WarningConfirm("Eliminar proveedores", "¿Está seguro de que quiere eliminar los proveedores seleccionados?")) {
            QJsonObject deleteProveedoresRequest;
            QJsonArray proveedoresIds;
            for (int i = 0; i < this->ui->tblProveedores->selectedItems().count(); ++i) {
                int row = this->ui->tblProveedores->selectedItems().at(i)->row();
                int registroId = this->ui->tblProveedores->item(row, 0)->text().toInt();
                if (!proveedoresIds.contains(registroId)) {
                    proveedoresIds.append(registroId);
                }
            }
            deleteProveedoresRequest["ProveedoresIds"] = proveedoresIds;
            Util::PerformWebPost(this, "/proveedores/deleteProveedores", deleteProveedoresRequest, [=](QJsonObject result) {
                emit this->UpdateListadoProveedores();
            }, [=](QString errorMessage) {
                Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
            });
        }
    } else {
        Util::ErrorAlert("Eliminar proveedores", "Seleccione al menos un proveedor para eliminar.");
    }
}
