#include "configmodel.h"
#include "bank.h"

ConfigModel::ConfigModel(QList<Bank*> banks, QObject* parent)
    : QObject(parent)
    , _banks(banks)
{
}

QList<Bank*> ConfigModel::banks() const
{
    return _banks;
}

void ConfigModel::setBanks(QList<Bank*> banks)
{
    if (_banks == banks)
        return;
    _banks = banks;
    emit banksChanged(_banks);
}
