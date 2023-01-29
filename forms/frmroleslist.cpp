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

    this->sortColumn = 1; // Rol
    this->sortDirection = Qt::SortOrder::AscendingOrder;
    this->page = 1;
    this->lastPageLoaded = false;
    this->requestId = 0;
    this->pageRequested = 0;
    this->pageLoaded = 0;

    this->ui->tblRoles->sortItems(this->sortColumn, this->sortDirection);

    this->ui->tblRoles->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblRoles->horizontalHeader()->setSortIndicatorShown(true);
    connect(ui->tblRoles->horizontalHeader(), &QHeaderView::sectionClicked, this, &frmRolesList::ColumnHeaderClicked);
    connect(ui->tblRoles->verticalScrollBar(), &QScrollBar::valueChanged, this, &frmRolesList::ListScrolled);

    this->LoadPage();

}

frmRolesList::~frmRolesList()
{
    delete ui;
    delete this->timerSearch;
}

void frmRolesList::closeParent()
{
    this->parentWidget()->close();
}

void frmRolesList::resizeEvent(QResizeEvent *resizeEvent)
{
    // Ocultamos la columna Id
    this->ui->tblRoles->hideColumn(0);

    QList<double> columnWidths;
    columnWidths.append(0);
    columnWidths.append(100);

    double totalColumnsWidth = 0;
    QList<double>::Iterator i;
    for (i = columnWidths.begin(); i != columnWidths.end(); ++i) {
        totalColumnsWidth += *i;
    }

    int gridWidth = this->ui->tblRoles->size().width() - 2; // -2 píxeles porque al parecer no tengo forma de sacar el tamaño del borde.

    for (int i = 0; i < this->ui->tblRoles->columnCount(); ++i) {
        int columnWidth = Util::Round((double)gridWidth + (double)columnWidths[i] / (double)totalColumnsWidth);
        if (i == this->ui->tblRoles->columnCount() - 1) {
            this->ui->tblRoles->setColumnWidth(i, 10);
        } else {
            this->ui->tblRoles->setColumnWidth(i, columnWidth);
        }
    }

}

void frmRolesList::ColumnHeaderClicked(int columnIndex)
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
    this->ui->tblRoles->horizontalHeader()->setSortIndicator(this->sortColumn, this->sortDirection);
    this->ui->tblRoles->horizontalHeader()->setSortIndicatorShown(true);
    this->page = 1;
    this->ui->tblRoles->setRowCount(0);
    this->LoadPage();
}

QString frmRolesList::getColumnName(int columnId)
{
    switch (columnId) {
        case 0:
            return "Id";
        case 1:
            return "Rol";
        default:
            return "Rol";
    }
}

void frmRolesList::LoadPage()
{
    this->requestId++;
    this->pageRequested = this->page;

    // Obj Request
    QJsonObject getRolesRequest;
    getRolesRequest["start"] = (this->page - 1) * this->limit;
    getRolesRequest["limit"] = this->limit;
    getRolesRequest["sort"] = frmRolesList::getColumnName(this->sortColumn);
    if (this->sortDirection == Qt::SortOrder::DescendingOrder) {
        getRolesRequest["dir"] = "DESC";
    } else {
        getRolesRequest["dir"] = "ASC";
    }
    getRolesRequest["filtro_Search"] = this->ui->txtFiltroSearch->text();
    int requestId = this->requestId;
    Util::PerformWebPost(this, "/roles/getRoles", getRolesRequest, [=](QJsonObject response) {
        if (this->requestId == requestId) {
            this->AddPage(response);
        }
    }, [](QString errorMessage) {
        Util::ErrorAlert("Gestión de roles", errorMessage);
    });
}

void frmRolesList::AddPage(QJsonObject page)
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
        this->ui->tblRoles->setRowCount(0);
    }
    QJsonArray roles = page["collection"].toArray();
    QJsonArray::Iterator i;
    for (i = roles.begin(); i != roles.end(); ++i) {
        QJsonObject rol = (*i).toObject();

        int row = ui->tblRoles->rowCount();
        ui->tblRoles->insertRow(row);

        // Id
        QTableWidgetItem *cell = new QTableWidgetItem(QString::number(rol["Id"].toInt(0)));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblRoles->setItem(row, 0, cell);

        // Rol
        cell = new QTableWidgetItem(rol["Rol"].toString(""));
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->tblRoles->setItem(row, 1, cell);

    }

    // Obtenemos el scroll vertical para determinar si hay que cargar otra página.
    // El scroll vertical no se actualiza hasta que no termina de pintarse el widget
    QTimer::singleShot(1, this, [this](){

        QScrollBar *vScroll = this->ui->tblRoles->verticalScrollBar();
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

void frmRolesList::ListScrolled(int position)
{

    QScrollBar *vScroll = this->ui->tblRoles->verticalScrollBar();
    int verticalMaxValue = vScroll->maximum();
    int verticalCurrentValue = vScroll->value();

    if (verticalMaxValue - verticalCurrentValue < 100) {
        if ((!this->lastPageLoaded) && (this->pageRequested == this->pageLoaded)) {
            this->page++;
            this->LoadPage();
        }
    }

}

void frmRolesList::SearchChanged()
{
    this->timerSearch->stop();
    this->timerSearch->start(300);
}

void frmRolesList::NuevoRol()
{
    emit this->AbrirRol(0);
}

void frmRolesList::ModificarRol()
{
    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblRoles->selectedItems().count())
    {
        int row = this->ui->tblRoles->selectedItems().last()->row();
        if (this->ui->tblRoles->currentRow() > -1) {
            row = this->ui->tblRoles->currentRow();
        }
        int registroId = this->ui->tblRoles->item(row, 0)->text().toInt();
        emit this->AbrirRol(registroId);
    }
    else
    {
        Util::ErrorAlert("Modificar rol", "Seleccione un rol para modificar.");
    }
}

void frmRolesList::ActualizarListado()
{
    this->page = 1;
    this->LoadPage();
}

void frmRolesList::DeleteRoles()
{
    if (this->ui->tblRoles->selectedItems().count() > 0) {
        if (Util::WarningConfirm("Eliminar roles", "¿Está seguro de que quiere eliminar los roles seleccionados?")) {
            QJsonObject deleteRolesRequest;
            QJsonArray rolesIds;
            for (int i = 0; i < this->ui->tblRoles->selectedItems().count(); ++i) {
                int row = this->ui->tblRoles->selectedItems().at(i)->row();
                int registroId = this->ui->tblRoles->item(row, 0)->text().toInt();
                if (!rolesIds.contains(registroId)) {
                    rolesIds.append(registroId);
                }
            }
            deleteRolesRequest["RolesIds"] = rolesIds;
            Util::PerformWebPost(this, "/roles/deleteRoles", deleteRolesRequest, [=](QJsonObject result) {
                emit this->UpdateListadoRoles();
            }, [=](QString errorMessage) {
                Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
            });
        }
    } else {
        Util::ErrorAlert("Eliminar roles", "Seleccione al menos un rol para eliminar.");
    }
}
