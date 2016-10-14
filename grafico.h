#ifndef GRAFICO_H
#define GRAFICO_H
#include <QPainter>
#include <QVector>
#include "datigrafico.h"

class Grafico {
 protected:
    const QPointF& origine;
    const DatiGrafico* dg;
    const QVector<const QPointF*> punti;
 public:
    Grafico(const DatiGrafico* dati, const QSize& dim, const QPointF& origine);

    virtual ~Grafico();

    //metodo virtuale puro;
    virtual void disegna(QPainter& painter) const =0;
};
#endif // GRAFICO_H
