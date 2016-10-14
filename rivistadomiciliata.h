#ifndef RIVISTADOMICILIATA_H
#define RIVISTADOMICILIATA_H
#include "rivistacartacea.h"

class RivistaDomiciliata : public RivistaCartacea {
 private:
    double maggiorazione;
 protected:
    virtual bool isEqual(const Prodotto& p) const;
 public:
    RivistaDomiciliata(QString tit="", QString edit="", QDate pubb =QDate::currentDate(),
                       QString cat="", int num_p=0, double cpp=0, double mag=0);

    //implemento i metodi virtuali puri;
    virtual double prezzo() const;
    virtual RivistaDomiciliata* clone() const;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //metodi get/set
    double getMaggiorazione() const;
    void setMaggiorazione(double mag);
};

#endif // RIVISTADOMICILIATA_H
