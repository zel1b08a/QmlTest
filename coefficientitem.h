#pragma once

#include <QHash>

class CoefficientItem
{
public:
    CoefficientItem(quint32 value = -1, int row = 0, CoefficientItem* parent = nullptr);
    ~CoefficientItem();

    CoefficientItem *childAt(int i);
    int childrenCount();
    CoefficientItem *parent();
    quint32 value() const;
    int row() const;

    void setValue(const quint32& value);
    void setParent(CoefficientItem* parent_item);

    void appendChild(CoefficientItem* child);

private:
    quint32 _value;
    CoefficientItem* _parent_item;
    QHash<int, CoefficientItem*> _child_items;
    int _row_number;
};
