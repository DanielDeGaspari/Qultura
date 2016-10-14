#include "grafico.h"

Grafico::Grafico(const DatiGrafico* dati, const QSize& dim, const QPointF& orig)
    :  origine(orig), dg(dati), punti(dati->punti(dim,orig)) {}

Grafico::~Grafico() {
    QVector<const QPointF*>::ConstIterator cit = punti.begin();
    for (; cit != punti.end(); ++cit) {
        delete (*cit);
    }
}
