#include "rivistacartacea.h"
#include "rivistadomiciliata.h"
#include <math.h>
#include <typeinfo>

RivistaCartacea::RivistaCartacea(QString tit, QString edit, QDate pubb,
                QString cat, int num_p, double costo) :
        Rivista(tit,edit,pubb,cat), n_pagine(num_p), cpp(costo) {}


double RivistaCartacea::prezzo() const {
    double base = cpp* n_pagine;    //cpp può anche essere minore di 1 centesimo;
    return round(base*100.0)/100.0;
}

bool RivistaCartacea::isEqual(const Prodotto& p) const {
    const RivistaCartacea* rc = static_cast<const RivistaCartacea*>(&p);
    return n_pagine == rc->n_pagine && cpp == rc->cpp &&
            Rivista::operator==(p);
}

bool RivistaCartacea::operator==(const Prodotto& p) const {
    return ( (typeid(*this) == typeid(p) && isEqual(p)));
}

bool RivistaCartacea::operator!=(const Prodotto& p) const {
    return !(operator==(p));
}

RivistaCartacea* RivistaCartacea::clone() const {
    return new RivistaCartacea(*this);
}


int RivistaCartacea::getN_pagine() const {
    return n_pagine;
}
void RivistaCartacea::setN_pagine(int num_p) {
    n_pagine=num_p;
}
double RivistaCartacea::getCpp() const {
    return cpp;
}
void RivistaCartacea::setCpp(double costo) {
    cpp=costo;
}
