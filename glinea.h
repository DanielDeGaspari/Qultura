#ifndef GLINEA_H
#define GLINEA_H
#include "grafico.h"

class GLinea : public Grafico {
public:
    GLinea(const DatiGrafico* dati, const QSize& dim, const QPointF& origine);

    //implemento il metodo virtuale puro
    virtual void disegna(QPainter& painter) const;
};

#endif // GLINEA_H
