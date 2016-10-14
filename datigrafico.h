#ifndef DATIGRAFICO_H
#define DATIGRAFICO_H

#include "ordine.h"
#include <QVector>
#include <QPointF>
#include <QSize>

class DatiGrafico {
 private:
    QVector<double> value;
 public:
    DatiGrafico(const Ordine& ord);

    double getMax() const;
    double operator[](int i) const;
    QVector<const QPointF*> punti(const QSize& dim, const QPointF& origine) const;
};

#endif // DATIGRAFICO_H
