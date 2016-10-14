#include "rivistadigitale.h"
#include <math.h>
#include <typeinfo>

RivistaDigitale::RivistaDigitale(QString tit, QString edit, QDate pubb,
                                 QString cat, double costo, int dim) :
   Rivista(tit,edit,pubb,cat), cpKB(costo), dimensione(dim) {}

double RivistaDigitale::prezzo() const {
    double base = cpKB*dimensione;    //cpKB può essere anche minore di 1 cent;
    return round(base*100.0)/100.0; //in questo modo restituisco un valore arrotondato alla seconda cifra dopo la ,.
}

bool RivistaDigitale::isEqual(const Prodotto& p) const {
    const RivistaDigitale* rd = static_cast<const RivistaDigitale*>(&p);
    return cpKB == rd->cpKB && dimensione == rd->dimensione &&
            Rivista::operator==(p);
}

bool RivistaDigitale::operator==(const Prodotto& p) const {
    return ( (typeid(*this) == typeid(p) && isEqual(p)));
}

bool RivistaDigitale::operator!=(const Prodotto& p) const {
    return !(operator ==(p));
}

RivistaDigitale* RivistaDigitale::clone() const {
    return new RivistaDigitale(*this);
}


double RivistaDigitale::getCpKB() const {
    return cpKB;
}
void RivistaDigitale::setCpKB(double costo) {
    cpKB=costo;
}
int RivistaDigitale::getDimensione() const {
    return dimensione;
}
void RivistaDigitale::setDimensione(int dim) {
    dimensione=dim;
}
