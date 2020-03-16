#pragma once

#include <QObject>


class ConfigAsTreeItem;

class ConfigAsTreeModel : public QObject
{
    Q_OBJECT

public:
    explicit ConfigAsTreeModel(QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> tree READ treeAsQObjects NOTIFY treeChanged)
    const QList<ConfigAsTreeItem*> &tree() const;
    const QList<QObject*> treeAsQObjects() const;

signals:
    void treeChanged();

private:
    QList<ConfigAsTreeItem*> _tree;
};
