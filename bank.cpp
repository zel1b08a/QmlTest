#include "bank.h"


bool Coefficient::operator==(const Coefficient& o) const
{
    return this->value == o.value;
}


Bank::Bank(QVector<Coefficient> coefficients, QObject* parent)
    : QObject(parent)
    , _coefficients(coefficients)
{
}

QVector<Coefficient> Bank::coefficients() const
{
    return _coefficients;
}

void Bank::setCoefficients(QVector<Coefficient> coefficients)
{
    if (_coefficients != coefficients) {
        _coefficients.swap(coefficients);
        emit coefficientsChanged(_coefficients);
    }
}

bool Bank::setCoefficientAt(int id, const Coefficient& coefficient)
{
    if (id < 0 || id >= _coefficients.size())
        return false;

    if (coefficient == _coefficients.at(id))
        return false;

    _coefficients[id] = coefficient;
    return true;
}

void Bank::appendCoefficient()
{
    emit preCoefficientAppended();
    _coefficients.append(Coefficient {});
    emit postCoefficientAppended();
}

void Bank::removeCoefficient(int id)
{
    if (id < 0 || id >= _coefficients.size())
        return;
    emit preCoefficientRemoved(id);
    _coefficients.removeAt(id);
    emit postCoefficientRemoved();
}
