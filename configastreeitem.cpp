#include "configastreeitem.h"

ConfigAsTreeItem::ConfigAsTreeItem(QVector<Coefficient> coefficients, QObject* parent)
    : QObject(parent)
    , _coefficients(coefficients)
    , _child_items(QList<ConfigAsTreeItem*>())
    , _is_open(false)
{
}

QVector<Coefficient> ConfigAsTreeItem::coefficients() const
{
    return _coefficients;
}

void ConfigAsTreeItem::setCoefficients(QVector<Coefficient> coefficients)
{
    if (coefficients != _coefficients){
        _coefficients = coefficients;
        emit coefficientsChanged();
    }
}

const QList<ConfigAsTreeItem*>&ConfigAsTreeItem::childItems() const
{
    return _child_items;
}

const QList<QObject*> ConfigAsTreeItem::childItemsAsQObject() const
{
    QList<QObject *> res;
    res.reserve(_child_items.count());
    for (auto i : _child_items)
        res.append(i);
    return res;
}

void ConfigAsTreeItem::addChildItem(ConfigAsTreeItem* child_item)
{
    _child_items.append(child_item);
    emit childItemsChanged();
    if (_child_items.count() == 1)
        emit hasChildChanged();
}

bool ConfigAsTreeItem::isOpen() const
{
    return _is_open;
}

void ConfigAsTreeItem::setIsOpen(bool is_open)
{
    if (_is_open != is_open){
        _is_open = is_open;
        emit isOpenChanged();
    }
}

bool ConfigAsTreeItem::hasChild() const
{
    return !_child_items.isEmpty();
}
