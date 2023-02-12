#include "treeviewautohideable.h"
#include <QTimer>

TreeViewAutoHideable::TreeViewAutoHideable(QWidget *parent): QTreeView(parent)
{
    this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    connect(this, &TreeViewAutoHideable::clicked, this, &TreeViewAutoHideable::itemClicked);
}

void TreeViewAutoHideable::focusOutEvent ( QFocusEvent * ) {
    this->setVisible(false);
}

void TreeViewAutoHideable::SelectItemByIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        this->setCurrentIndex(index);

        QModelIndex idxId = this->model()->index(index.row(), 1, index.parent());
        QModelIndex idxText = this->model()->index(index.row(), 0, index.parent());

        int Id = this->model()->data(idxId).toInt();
        QString Text = this->model()->data(idxText).toString();

        QModelIndex idx = index.parent();
        while (idx.isValid()) {
            QModelIndex idxTextParent = this->model()->index(idx.row(), 0, idx.parent());
            Text = this->model()->data(idxTextParent).toString() + " > " + Text;
            idx = idx.parent();
        }

        emit this->ItemSelected(Id, Text);
    }
}

void TreeViewAutoHideable::itemClicked(const QModelIndex &index)
{
    if (this->isVisible() && index.isValid()) {

        this->SelectItemByIndex(index);

    }
}
