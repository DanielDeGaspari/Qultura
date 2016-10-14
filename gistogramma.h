#ifndef GISTOGRAMMA_H
#define GISTOGRAMMA_H
#include "grafico.h"

class gIstogramma : public Grafico {
 public:
    gIstogramma(const DatiGrafico* dati,  const QSize& dim, const QPointF& orig);

    //implemento il metodo virtuale puro
    virtual void disegna(QPainter& painter) const;
};

#endif // GISTOGRAMMA_H
