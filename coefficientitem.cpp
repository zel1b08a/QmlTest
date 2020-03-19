#include "coefficientitem.h"

CoefficientItem::CoefficientItem(quint32 value, int row, CoefficientItem* parent)
    : _value(value)
    , _parent_item(parent)
    , _row_number(row)
{
}

CoefficientItem::~CoefficientItem()
{
    qDeleteAll(_child_items);
}

CoefficientItem* CoefficientItem::childAt(int i)
{
    return _child_items.value(i);
}

int CoefficientItem::childrenCount()
{
    return _child_items.size();
}

CoefficientItem* CoefficientItem::parent()
{
    return _parent_item;
}

quint32 CoefficientItem::value() const
{
    return _value;
}

int CoefficientItem::row() const
{
    return _row_number;
}

void CoefficientItem::setValue(const quint32& value)
{
    _value = value;
}

void CoefficientItem::setParent(CoefficientItem* parent_item)
{
    _parent_item = parent_item;
}

void CoefficientItem::appendChild(CoefficientItem* child)
{
    int row = _child_items.size();
    child->_parent_item = this;
    child->_row_number = row;
    _child_items.insert(row, child);
}
