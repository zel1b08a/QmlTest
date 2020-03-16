#pragma once

#include <QAbstractListModel>

class Bank;

class BankModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Bank* bank READ bank WRITE setBank)

public:
    enum {
        CoefficientRole = Qt::UserRole
    };

    explicit BankModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = CoefficientRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Bank* bank() const;
    void setBank(Bank* bank);

private:
    Bank* _bank;
};
