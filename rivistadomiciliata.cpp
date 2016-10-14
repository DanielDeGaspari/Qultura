#include "rivistadomiciliata.h"
#include <typeinfo>

RivistaDomiciliata::RivistaDomiciliata(QString tit, QString edit, QDate pubb,
                                QString cat,int num_p, double cpp, double mag) :
        RivistaCartacea(tit,edit,pubb,cat,num_p,cpp), maggiorazione(mag) {}

double RivistaDomiciliata::prezzo() const {
    return RivistaCartacea::prezzo() + maggiorazione;
}


bool RivistaDomiciliata::isEqual(const Prodotto& p) const {
    const RivistaDomiciliata* rd = static_cast<const RivistaDomiciliata*>(&p);
    return maggiorazione == rd->maggiorazione &&
            RivistaCartacea::isEqual(p);
}

bool RivistaDomiciliata::operator==(const Prodotto& p) const {
    return ( (typeid(*this) == typeid(p) && isEqual(p)));
}

bool RivistaDomiciliata::operator !=(const Prodotto& p) const {
    return !(operator==(p));
}

RivistaDomiciliata* RivistaDomiciliata::clone() const {
    return new RivistaDomiciliata(*this);
}


double RivistaDomiciliata::getMaggiorazione() const {
    return maggiorazione;
}
void RivistaDomiciliata::setMaggiorazione(double mag) {
    maggiorazione=mag;
}
