#pragma once

#include <QObject>
#include <QVector>

typedef quint32 Coefficient;

class Bank;

class ConfigAsTreeItem : public QObject
{
    Q_OBJECT

public:
    explicit ConfigAsTreeItem(QVector<Coefficient> coefficients = QVector<Coefficient>(), QObject *parent = nullptr);

    Q_PROPERTY(QVector<Coefficient> coefficients READ coefficients NOTIFY coefficientsChanged)
    QVector<Coefficient> coefficients() const;
    void setCoefficients(QVector<Coefficient> coefficients);

    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)
    const QList<ConfigAsTreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    void addChildItem(ConfigAsTreeItem * child_item);

    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    bool isOpen() const;
    void setIsOpen(bool is_open);

    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    bool hasChild() const;

//public slots:
//    void appendCoefficient();
//    void removeCoefficient(int id);

signals:
    void coefficientsChanged();
    void childItemsChanged();
    void isOpenChanged();
    void hasChildChanged();

    void preCoefficientAppended();
    void postCoefficientAppended();
    void preCoefficientRemoved(int index);
    void postCoefficientRemoved();
    void coefficientsChanged(QVector<Coefficient> coefficients);

private:
    QVector<Coefficient> _coefficients;
    QList<ConfigAsTreeItem *> _child_items;
    bool _is_open;
};
