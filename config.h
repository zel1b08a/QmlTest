#pragma once

#include <QObject>
#include <QList>

class Bank;

class Config : public QObject
{
    Q_OBJECT

public:
    explicit Config(QList<Bank*> banks = QList<Bank*>(), QObject *parent = nullptr);

    QList<Bank*> banks() const;
    void setBanks(QList<Bank*> banks);

    bool setBankAt(int id, Bank* bank);

public slots:
    void appendBank();
    void removeBank(int id);

signals:
    void preBankAppended();
    void postBankAppended();
    void preBankRemoved(int id);
    void postBankRemoved();
    void banksChanged(QList<Bank*> banks);

private:
    QList<Bank*> _banks;
};
