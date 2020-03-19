#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVector>
#include <QtGlobal>

class CoefficientItem;

class ConfigModel : public QAbstractItemModel
{
    Q_OBJECT

    enum { CoefficientRole = Qt::UserRole };

public:
    explicit ConfigModel(const QVector<QVector<quint32>>& config, CoefficientItem* root = nullptr, QObject *parent = nullptr);
    ~ConfigModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = CoefficientRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setModelUp(const QVector<QVector<quint32> >& config);

private:
    CoefficientItem* _root_item;
};
