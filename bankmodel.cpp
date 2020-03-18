#include "bankmodel.h"
#include "bank.h"

BankModel::BankModel(QObject* parent)
    : QAbstractListModel(parent)
    , _bank(nullptr)
{
}

int BankModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !_bank)
        return 0;

    return _bank->coefficients().size();
}

QVariant BankModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_bank)
        return QVariant();

    const Coefficient coefficient = _bank->coefficients().at(index.row());
    switch (role) {
    case CoefficientRole: return QVariant::fromValue(coefficient);
    }

    return QVariant();
}

bool BankModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!_bank)
        return false;

    Coefficient coefficient = _bank->coefficients().at(index.row());
    switch (role) {
    case CoefficientRole: coefficient = value.value<Coefficient>(); break;
    }

    if (_bank->setCoefficientAt(index.row(), coefficient)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags BankModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> BankModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[CoefficientRole] = "coefficient";
    return names;
}

Bank* BankModel::bank() const
{
    return _bank;
}

void BankModel::setBank(Bank* bank)
{
    beginResetModel();

    if (_bank)
        _bank->disconnect(this);

    _bank = bank;

    if (_bank) {
        connect(_bank, &Bank::preCoefficientAppended, this, [=](){
            const int index = _bank->coefficients().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(_bank, &Bank::postCoefficientAppended, this, [=](){
            endResetModel();
        });
        connect(_bank, &Bank::preCoefficientRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(_bank, &Bank::postCoefficientRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
