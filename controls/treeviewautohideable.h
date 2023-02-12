#ifndef TREEVIEWAUTOHIDEABLE_H
#define TREEVIEWAUTOHIDEABLE_H

#include <QTreeView>

class TreeViewAutoHideable : public QTreeView
{
    Q_OBJECT

public:
    TreeViewAutoHideable(QWidget *parent);
    void SelectItemByIndex(const QModelIndex &index);

signals:
    void ItemSelected(int Id, QString Text);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void itemClicked(const QModelIndex &index);
};

#endif // TREEVIEWAUTOHIDEABLE_H
