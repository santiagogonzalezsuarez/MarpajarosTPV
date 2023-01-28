#include "frmproductoslist.h"
#include "ui_frmproductoslist.h"
#include <QResizeEvent>
#include "../util/util.h"
#include <QScrollBar>
#include <QTimer>

frmProductosList::frmProductosList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmProductosList)
{
    ui->setupUi(this);

    this->ui->txtFiltroSearch->setFocus();

    this->timerSearch = new QTimer(this);
    this->timerSearch->setSingleShot(true);
    connect(this->timerSearch, &QTimer::timeout, [this]{
        this->page = 1;
        this->LoadPage();
    });

    this->sortColumn = 2; // Producto
    this->sortDirection = Qt::SortOrder::AscendingOrder;
    this->page = 1;
    this->lastPageLoaded = false;
    this->requestId = 0;
    this->pageRequested = 0;
    this->pageLoaded = 0;

    this->ui->tblProductos->sortItems(this->sortColumn, this->sortDirection);

    this->ui->tblProductos->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblProductos->horizontalHeader()->setSortIndicatorShown(true);
    connect(ui->tblProductos->horizontalHeader(), &QHeaderView::sectionClicked, this, &frmProductosList::ColumnHeaderClicked);
    connect(ui->tblProductos->verticalScrollBar(), &QScrollBar::valueChanged, this, &frmProductosList::ListScrolled);

    this->LoadPage();

}

frmProductosList::~frmProductosList()
{
    delete ui;
    delete this->timerSearch;
}

void frmProductosList::closeParent()
{
    this->parentWidget()->close();
}

void frmProductosList::resizeEvent(QResizeEvent *resizeEvent)
{

    // Ocultamos la columna Id
    this->ui->tblProductos->hideColumn(0);

    QList<double> columnWidths;
    columnWidths.append(0);
    columnWidths.append(137);
    columnWidths.append(274);
    columnWidths.append(45);
    columnWidths.append(92);
    columnWidths.append(91);
    columnWidths.append(73);
    columnWidths.append(73);

    double totalColumnsWidth = 0;
    QList<double>::Iterator i;
    for (i = columnWidths.begin(); i != columnWidths.end(); ++i) {
        totalColumnsWidth += *i;
    }

    int gridWidth = this->ui->tblProductos->size().width() - 2; // -2 píxeles porque al parecer no tengo forma de sacar el tamaño del borde.

    for (int i = 0; i < this->ui->tblProductos->columnCount(); ++i) {
        int columnWidth = Util::Round((double)gridWidth * (double)columnWidths[i] / (double)totalColumnsWidth);
        if (i == this->ui->tblProductos->columnCount() - 1) {
            this->ui->tblProductos->setColumnWidth(i, 10);
        } else {
            this->ui->tblProductos->setColumnWidth(i, columnWidth);
        }
    }

}

void frmProductosList::ColumnHeaderClicked(int columnIndex) {
    if (columnIndex == 6) {
        this->ui->tblProductos->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
        this->ui->tblProductos->horizontalHeader()->setSortIndicatorShown(true);
        return; // Columna no ordenable.
    }
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
    this->ui->tblProductos->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblProductos->horizontalHeader()->setSortIndicatorShown(true);
    this->page = 1;
    this->ui->tblProductos->setRowCount(0);
    this->LoadPage();
}

QString frmProductosList::getColumnName(int columnId) {
    switch (columnId) {
        case 0:
            return "Id";
        case 1:
            return "Categorias";
        case 2:
            return "Producto";
        case 3:
            return "Stock";
        case 4:
            return "Marca";
        case 5:
            return "Referencias";
        case 7:
            return "PrecioVenta";
        default:
            return "Producto";
    }
}

void frmProductosList::LoadPage()
{
    this->requestId++;
    this->pageRequested = this->page;

    // Obj Request
    QJsonObject getProductosRequest;
    getProductosRequest["start"] = (this->page - 1) * this->limit;
    getProductosRequest["limit"] = this->limit;
    getProductosRequest["sort"] = frmProductosList::getColumnName(this->sortColumn);
    if (this->sortDirection == Qt::SortOrder::DescendingOrder) {
        getProductosRequest["dir"] = "DESC";
    } else {
        getProductosRequest["dir"] = "ASC";
    }
    getProductosRequest["filtro_Search"] = this->ui->txtFiltroSearch->text();
    getProductosRequest["filtro_ProveedorId"] = "";

    int requestId = this->requestId;
    Util::PerformWebPost(this, "/productos/getProductos", getProductosRequest, [=](QJsonObject response) {
        if (this->requestId == requestId) {
            this->AddPage(response);
        }
    }, [](QString errorMessage) {
        Util::ErrorAlert("Listado de productos", errorMessage);
    });

}

void frmProductosList::AddPage(QJsonObject page)
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
        this->ui->tblProductos->setRowCount(0);
    }
    QJsonArray productos = page["collection"].toArray();
    QJsonArray::Iterator i;
    for (i = productos.begin(); i != productos.end(); ++i) {
        QJsonObject producto = (*i).toObject();

        int row = ui->tblProductos->rowCount();
        ui->tblProductos->insertRow(row);

        // Id
        QTableWidgetItem *cell = new QTableWidgetItem(QString::number(producto["Id"].toInt(0)));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 0, cell);

        // Categorías
        cell = new QTableWidgetItem(producto["Categorias"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 1, cell);

        // Producto
        cell = new QTableWidgetItem(producto["Producto"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 2, cell);

        // Stock
        cell = new QTableWidgetItem(QString::number(producto["Stock"].toInt(0)));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 3, cell);

        // Marca
        cell = new QTableWidgetItem(producto["Marca"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 4, cell);

        // Referencia
        cell = new QTableWidgetItem(producto["Referencia"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 5, cell);

        // Precio compra
        cell = new QTableWidgetItem(((QString::number(producto["PrecioCompra"].toDouble(0), 'f', 2).replace(".", ",")) + " €"));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 6, cell);

        // Precio venta
        cell = new QTableWidgetItem(((QString::number(producto["PrecioVenta"].toDouble(0), 'f', 2).replace(".", ",")) + " €"));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 7, cell);

    }

    // Obtenemos el scroll vertical para determinar si hay que cargar otra página.
    // El scroll vertical no se actualiza hasta que no termina de pintarse el widget.
    QTimer::singleShot(1, this, [this](){

        QScrollBar *vScroll = this->ui->tblProductos->verticalScrollBar();
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

void frmProductosList::ListScrolled(int position) {

    QScrollBar *vScroll = this->ui->tblProductos->verticalScrollBar();
    int verticalMaxValue = vScroll->maximum();
    int verticalCurrentValue = vScroll->value();

    if (verticalMaxValue - verticalCurrentValue < 100) {
        if ((!this->lastPageLoaded) && (this->pageRequested == this->pageLoaded)) {
            this->page++;
            this->LoadPage();
        }
    }

}

void frmProductosList::SearchChanged() {

    this->timerSearch->stop();
    this->timerSearch->start(300);

}