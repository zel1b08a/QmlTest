#pragma once

#include <QObject>

class Bank;

class ConfigModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Bank*> banks READ banks WRITE setBanks NOTIFY banksChanged)

public:
    explicit ConfigModel(QList<Bank*> banks = QList<Bank*>(), QObject *parent = nullptr);

    QList<Bank*> banks() const;
    void setBanks(QList<Bank*> banks);

signals:
    void banksChanged(QList<Bank*> banks);

private:
    QList<Bank*> _banks;
};
