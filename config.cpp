#include "config.h"
#include "bank.h"

Config::Config(QList<Bank*> banks, QObject *parent)
    : QObject(parent)
    , _banks(banks)
{
}

QList<Bank*> Config::banks() const
{
    return _banks;
}

void Config::setBanks(QList<Bank*> banks)
{
    if (_banks != banks) {
        _banks.swap(banks);
        emit banksChanged(_banks);
    }
}

bool Config::setBankAt(int id, Bank* bank)
{
    if (id < 0 || id >= _banks.size() || !bank)
        return false;

    Bank* const& bank_current = _banks.at(id);
    if (bank->coefficients() == bank_current->coefficients())
        return false;

    delete _banks[id];
    bank->setParent(this);
    _banks[id] = bank;
    emit banksChanged(_banks);

    return true;
}

void Config::appendBank()
{
    emit preBankAppended();
    Bank* bank = new Bank(QVector<Coefficient>(), this);
    _banks.append(bank);
    emit postBankAppended();
    emit banksChanged(_banks);
}

void Config::removeBank(int id)
{
    if (id < 0 || id >= _banks.size())
        return;

    emit preBankRemoved(id);
    delete _banks.takeAt(id);
    emit postBankRemoved();
    emit banksChanged(_banks);
}
