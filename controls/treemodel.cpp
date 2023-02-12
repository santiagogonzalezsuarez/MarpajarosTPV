#include "treemodel.h"
#include "treeitem.h"

TreeModel::TreeModel(const QJsonArray &data, QObject *parent)
    : QAbstractItemModel{parent}
{
    rootItem = new TreeItem({"Text", "Id"});
    setupModelData(data, rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::update(const QJsonArray &items)
{
    delete rootItem;
    rootItem = new TreeItem({"Id", "Text"});
    setupModelData(items, rootItem);
}

void TreeModel::setupModelData(const QJsonArray &items, TreeItem *parent)
{
    for (QJsonArray::const_iterator i = items.begin(); i != items.end(); ++i) {
        if ((*i).isObject()) {
            QJsonObject item = (*i).toObject();
            QList<QVariant> columnData;
            columnData << item["Text"].toString("[No hay datos]");
            columnData << QString::number(item["Id"].toInt(0));
            TreeItem *treeItem = new TreeItem(columnData, parent);
            parent->appendChild(treeItem);
            if (item["Children"].isArray()) {
                this->setupModelData(item["Children"].toArray(), treeItem);
            }
        }
    }
}
