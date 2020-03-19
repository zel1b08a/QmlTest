#include "configmodel.h"
#include "coefficientitem.h"

ConfigModel::ConfigModel(const QVector<QVector<quint32> >& config, CoefficientItem* root, QObject *parent)
    : QAbstractItemModel(parent)
    , _root_item(root)
{
    setModelUp(config);
}

ConfigModel::~ConfigModel()
{
    delete _root_item;
}

QModelIndex ConfigModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CoefficientItem* parent_item;
    if (!parent.isValid())
        parent_item = _root_item;
    else
        parent_item = static_cast<CoefficientItem*>(parent.internalPointer());

    CoefficientItem* child_item = parent_item->childAt(row);
    if (child_item)
        return createIndex(row, column, child_item);

    return QModelIndex();
}

QModelIndex ConfigModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CoefficientItem* parent_item = static_cast<CoefficientItem*>(index.internalPointer())->parent();
    if (!parent_item || parent_item == _root_item)
        return QModelIndex();

    return createIndex(parent_item->row(), 0, parent_item);
}

int ConfigModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    CoefficientItem* parent_item;
    if (!parent.isValid())
        parent_item = _root_item;
    else
        parent_item = static_cast<CoefficientItem*>(parent.internalPointer());

    return parent_item->childrenCount();
}

int ConfigModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!parent.isValid())
        return 0;

    return 1;
}

QVariant ConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const CoefficientItem* item = static_cast<CoefficientItem*>(index.internalPointer());
    switch (role) {
        case CoefficientRole:
            return QVariant::fromValue(item->value());
    }

    return QVariant();
}

bool ConfigModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const auto& current_value = data(index, role);
    if (current_value != value && value.isValid()) {
        if (!index.isValid())
            return false;
        CoefficientItem* item = static_cast<CoefficientItem*>(index.internalPointer());
        switch (role) {
        case CoefficientRole:
            item->setValue(value.toUInt());
            break;
        default: return false;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | index.flags();
}

void ConfigModel::setModelUp(const QVector<QVector<quint32> >& config)
{
    if (!_root_item)
        _root_item = new CoefficientItem();

    foreach (const auto& bank, config) {
        _root_item->appendChild(new CoefficientItem());
        foreach (const auto& coefficient, bank)
            _root_item->childAt(_root_item->childrenCount() - 1)->appendChild(new CoefficientItem(coefficient));
    }
}


QHash<int, QByteArray> ConfigModel::roleNames() const
{
    return {
        {CoefficientRole, "coefficient"},
    };
}
