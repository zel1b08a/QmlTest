#include "configastreemodel.h"
#include "configastreeitem.h"


ConfigAsTreeModel::ConfigAsTreeModel(QObject* parent)
    : QObject(parent)
    , _tree(QList<ConfigAsTreeItem*>())
{
    _tree.append(new ConfigAsTreeItem(QVector<Coefficient>({ 12 }), this));
}

const QList<ConfigAsTreeItem*>&ConfigAsTreeModel::tree() const
{
    return _tree;
}

const QList<QObject*> ConfigAsTreeModel::treeAsQObjects() const
{
    QList<QObject *> res;
    res.reserve(_tree.count());
    for (auto i : _tree)
        res.append(i);
    return res;
}
