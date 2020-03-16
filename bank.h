#pragma once

#include <QObject>
#include <QVector>
#include <QMetaType>

struct Coefficient {
    quint32 value;
    bool operator==(const Coefficient& o) const;
};
Q_DECLARE_METATYPE(Coefficient)

class Bank : public QObject
{
    Q_OBJECT

public:
    explicit Bank(QVector<Coefficient> coefficients = QVector<Coefficient>(), QObject *parent = nullptr);

    QVector<Coefficient> coefficients() const;
    void setCoefficients(QVector<Coefficient> coefficients);

    bool setCoefficientAt(int id, const Coefficient& coefficient);

public slots:
    void appendCoefficient();
    void removeCoefficient(int id);

signals:
    void preCoefficientAppended();
    void postCoefficientAppended();
    void preCoefficientRemoved(int index);
    void postCoefficientRemoved();
    void coefficientsChanged(QVector<Coefficient> coefficients);

private:
    QVector<Coefficient> _coefficients;
};
