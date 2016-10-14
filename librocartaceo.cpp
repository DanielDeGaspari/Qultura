#include "librocartaceo.h"
#include <math.h>
#include <typeinfo>

LibroCartaceo::LibroCartaceo(QString tit, QString edit, QDate pubb, QString aut, QString cod, int ediz, QString gen, int np, double costo) :
    Libro(tit,edit,pubb,aut,cod,ediz,gen,np), cpp(costo) {}


double LibroCartaceo::prezzo() const {
    double base = getN_pagine()*cpp;    //cpp può essere anche minore di 1 cent;
    return round(base*100.0)/100.0; //in questo modo restituisco un valore arrotondato alla seconda cifra dopo la ,.
}

LibroCartaceo* LibroCartaceo::clone() const {
    return new LibroCartaceo(*this);
}

bool LibroCartaceo::isEqual(const Prodotto& p) const {
    const LibroCartaceo* lc = static_cast<const LibroCartaceo*>(&p);
    return cpp == lc->cpp && Libro::operator ==(p);
}

bool LibroCartaceo::operator==(const Prodotto& p) const {
    return ( (typeid(*this) == typeid(p) && isEqual(p)));
}

bool LibroCartaceo::operator !=(const Prodotto& p) const {
    return !(operator ==(p));
}

double LibroCartaceo::getCpp() const {
    return cpp;
}
void LibroCartaceo::setCpp(double costo) {
    cpp=costo;
}
