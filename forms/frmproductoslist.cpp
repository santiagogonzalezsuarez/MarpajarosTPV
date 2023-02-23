#include "frmproductoslist.h"
#include "ui_frmproductoslist.h"
#include <QResizeEvent>
#include "../util/util.h"
#include <QScrollBar>
#include <QTimer>
#include <QMovie>
#include <QImage>
#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>

frmProductosList::frmProductosList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmProductosList)
{
    ui->setupUi(this);

    this->fileSelectionProcess = nullptr;
    this->ui->txtFiltroSearch->setFocus();

    this->timerSearch = new QTimer(this);
    this->timerSearch->setSingleShot(true);
    connect(this->timerSearch, &QTimer::timeout, this, [this]{
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
    if (this->fileSelectionProcess != nullptr) {
        this->fileSelectionProcess->kill();
        delete this->fileSelectionProcess;
    }
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
        QLocale curLocale;
        cell = new QTableWidgetItem(curLocale.toString(producto["PrecioCompra"].toDouble(0), 'f', 2) + " €");
        cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
        cell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tblProductos->setItem(row, 6, cell);

        // Precio venta
        cell = new QTableWidgetItem(curLocale.toString(producto["PrecioVenta"].toDouble(0), 'f', 2) + " €");
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

void frmProductosList::NuevoProducto()
{
    emit this->AbrirProducto(0);
}

void frmProductosList::ModificarProducto()
{
    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblProductos->selectedItems().count())
    {
        int row = this->ui->tblProductos->selectedItems().last()->row();
        if (this->ui->tblProductos->currentRow() > -1) {
            row = this->ui->tblProductos->currentRow();
        }
        int registroId = this->ui->tblProductos->item(row, 0)->text().toInt();
        emit this->AbrirProducto(registroId);
    }
    else
    {
        Util::ErrorAlert("Modificar producto", "Seleccione un producto para modificar.");
    }
}

void frmProductosList::ActualizarListado()
{
    this->page = 1;
    this->LoadPage();
}

void frmProductosList::DeleteProductos()
{
    if (this->ui->tblProductos->selectedItems().count() > 0) {
        if (Util::WarningConfirm("Eliminar productos", "¿Está seguro de que quiere eliminar los productos seleccionados?")) {
            QJsonObject deleteProductosRequest;
            QJsonArray productosIds;
            for (int i = 0; i < this->ui->tblProductos->selectedItems().count(); ++i) {
                int row = this->ui->tblProductos->selectedItems().at(i)->row();
                int registroId = this->ui->tblProductos->item(row, 0)->text().toInt();
                if (!productosIds.contains(registroId)) {
                    productosIds.append(registroId);
                }
            }
            deleteProductosRequest["ProductosIds"] = productosIds;
            Util::PerformWebPost(this, "/productos/deleteProductos", deleteProductosRequest, [=](QJsonObject result) {
                emit this->UpdateListadoProductos();
            }, [=](QString errorMessage) {
                Util::ErrorAlert(this->parentWidget()->windowTitle(), errorMessage);
            });
        }
    } else {
        Util::ErrorAlert("Eliminar productos", "Seleccione al menos un producto para eliminar.");
    }
}


// Carga de imágenes
void frmProductosList::GridSelectionChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow != -1) {
        int registroId = this->ui->tblProductos->item(currentRow, 0)->text().toInt();
        if (registroId != this->productoImagenId) {
            if (this->cargandoImagen) {
                this->recargarImagen = true;
            } else {
                int requestId = ++this->productoImagenRequestId;
                this->productoImagenId = registroId;
                this->cargandoImagen = true;
                QMovie *loader = new QMovie(":/assets/loader.gif");
                this->ui->imgProducto->setMovie(loader);
                loader->start();
                QJsonObject getImagenRequest;
                getImagenRequest["ProductoId"] = registroId;
                Util::PerformWebPost(this, "/productos/getImagen", getImagenRequest, [=](QByteArray imageData) {
                    this->ui->imgProducto->setMovie(nullptr);
                    delete loader;
                    if (this->productoImagenRequestId == requestId) {
                        QImage imgProducto;
                        bool success = imgProducto.loadFromData(imageData);
                        if (success) {
                            QImage img(150, 250, QImage::Format_ARGB32);
                            int x = 0;
                            int y = 0;
                            int width = imgProducto.width();
                            int height = imgProducto.height();

                            if (imgProducto.height() * img.width() / imgProducto.width() > img.height()) {
                                height = img.height();
                                width = imgProducto.width() * img.height() / imgProducto.height();
                            } else {
                                width = img.width();
                                height = imgProducto.height() * img.width() / imgProducto.width();
                            }
                            x = (img.width() - width) / 2;
                            y = (img.height() - height) / 2;

                            QPainter qPainter(&img);
                            qPainter.fillRect(0, 0, 150, 250, QBrush(Qt::white));
                            qPainter.drawImage(QRect(x, y, width, height), imgProducto);
                            this->ui->imgProducto->setPixmap(QPixmap::fromImage(img));

                        } else {
                            QImage img(150, 250, QImage::Format_ARGB32);
                            QPainter qPainter(&img);
                            qPainter.fillRect(0, 0, 150, 250, QBrush(Qt::white));
                            this->ui->imgProducto->setPixmap(QPixmap::fromImage(img));
                        }
                    }
                    this->cargandoImagen = false;
                    if (this->recargarImagen) {
                        this->recargarImagen = false;
                        this->GridSelectionChanged(this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn(), this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn());
                    }
                }, [=](QString err) {
                    this->ui->imgProducto->setMovie(nullptr);
                    delete loader;
                    if (this->productoImagenRequestId == requestId) {
                        QImage img(150, 250, QImage::Format_ARGB32);
                        QPainter qPainter(&img);
                        qPainter.fillRect(0, 0, 150, 250, QBrush(Qt::white));
                        this->ui->imgProducto->setPixmap(QPixmap::fromImage(img));
                    }
                    this->cargandoImagen = false;
                    if (this->recargarImagen) {
                        this->recargarImagen = false;
                        this->GridSelectionChanged(this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn(), this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn());
                    }
                });
            }
        }
    }
}

void frmProductosList::ActualizarImagen()
{

    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblProductos->selectedItems().count())
    {
        int row = this->ui->tblProductos->selectedItems().last()->row();
        if (this->ui->tblProductos->currentRow() > -1) {
            row = this->ui->tblProductos->currentRow();
        }
        int registroId = this->ui->tblProductos->item(row, 0)->text().toInt();

        QString PicturesPath = Util::GetConfigString("Paths.LastPicturesPath");
        if (PicturesPath == "" || PicturesPath == nullptr) {
            PicturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        }

        if (fileSelectionProcess != nullptr) {
            fileSelectionProcess->kill();
            delete fileSelectionProcess;
        }
        fileSelectionProcess = new QProcess();
        QString path = QString(qgetenv("PATH"));
        bool executed = false;
        #ifdef Q_OS_WIN
        QStringList paths = path.split(";");
        #else
        QStringList paths = path.split(":");
        #endif

        for (QStringList::Iterator i = paths.begin(); i != paths.end() && !executed; ++i) {
            QString pathItem = *i;
            QString executableName = pathItem + QDir::separator() + "kdialog";
            if (QFile::exists(executableName)) {
                emit this->DisableMainWindow();
                QStringList args;
                args << "--getopenfilename";
                args << "--title";
                args << "Actualizar imagen";
                args << PicturesPath;
                args << "Archivos de imagen(*.jpg *.png *.gif)|Todos los archivos(*)";
                args << "--attach";
                args << QString::number(this->winId());
                fileSelectionProcess->start(executableName, args);
                if (fileSelectionProcess->waitForStarted()) {
                    executed = true;
                    connect(fileSelectionProcess, &QProcess::finished, this, [=]() {
                        QString stdout = fileSelectionProcess->readAllStandardOutput();
                        QString fileName = stdout.split("\n").first();
                        if (this->fileSelectionProcess->exitCode() == 0) {
                            QString filePath = fileName;
                            if (filePath.contains(QDir::separator())) {
                                filePath = filePath.left(filePath.lastIndexOf(QDir::separator()));
                                Util::SetConfigString("Paths.LastPicturesPath", filePath);
                                Util::SaveConfig();
                            }
                            this->ActualizarImagenProducto(registroId, fileName);
                        }

                        emit this->EnableMainWindow();
                        delete this->fileSelectionProcess;
                        this->fileSelectionProcess = nullptr;
                        this->setFocus();
                    });
                }
            }
        }

        if (!executed) {
            QString fileName = QFileDialog::getOpenFileName(this, "Seleccione una imagen", PicturesPath, "Archivos de imágenes (*.png *.jpg *.bmp)");
            if (fileName != nullptr && fileName != "") {
                QString filePath = fileName;
                if (filePath.contains(QDir::separator())) {
                    filePath = filePath.left(filePath.lastIndexOf(QDir::separator()));
                    Util::SetConfigString("Paths.LastPicturesPath", filePath);
                    Util::SaveConfig();
                }
                this->ActualizarImagenProducto(registroId, fileName);
            }
        }
    }
    else
    {
        Util::ErrorAlert("Actualizar imagen", "Seleccione un producto para cambiar la imagen.");
    }
}

void frmProductosList::ActualizarImagenProducto(int ProductoId, QString fileName)
{
    QFile imageFile(fileName);
    if (imageFile.open(QIODevice::ReadOnly))
    {
        QByteArray srcRawData = imageFile.readAll().toBase64();
        imageFile.close();
        if (srcRawData.length() < 1) {
            Util::ErrorAlert("Actualizar imagen", "No se ha podido leer el fichero.");
            return;
        }
        QJsonObject actualizarImagenRequest;
        actualizarImagenRequest["Id"] = ProductoId;
        actualizarImagenRequest["fileName"] = fileName;
        actualizarImagenRequest["base64Image"] = QString(srcRawData);
        Util::PerformWebPost(this, "/productos/actualizarImagen", actualizarImagenRequest, [=](QJsonObject result) {
            this->productoImagenId = -1;
            this->GridSelectionChanged(this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn(), this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn());
        }, [=](QString errorMessage) {
            Util::ErrorAlert("Actualizar imagen", errorMessage);
        });
    }
}

void frmProductosList::EliminarImagen()
{
    // Determinamos el primer elemento seleccionado.
    if (this->ui->tblProductos->selectedItems().count())
    {
        int row = this->ui->tblProductos->selectedItems().last()->row();
        if (this->ui->tblProductos->currentRow() > -1) {
            row = this->ui->tblProductos->currentRow();
        }
        int registroId = this->ui->tblProductos->item(row, 0)->text().toInt();
        if (Util::WarningConfirm("Eliminar imagen del producto", "¿Está seguro de que quiere quitar la imagen del producto seleccionado?")) {
            QJsonObject eliminarImagenRequest;
            eliminarImagenRequest["Id"] = registroId;
            Util::PerformWebPost(this, "/productos/eliminarImagen", eliminarImagenRequest, [=](QJsonObject result) {
                this->productoImagenId = -1;
                this->GridSelectionChanged(this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn(), this->ui->tblProductos->currentRow(), this->ui->tblProductos->currentColumn());
            }, [=](QString errorMessage) {
                Util::ErrorAlert("Eliminar imagen", errorMessage);
            });
        }
    }
    else
    {
        Util::ErrorAlert("Eliminar imagen", "Seleccione un producto para quitar la imagen.");
    }
}
