#ifndef RIVISTACARTACEA_H
#define RIVISTACARTACEA_H
#include "rivista.h"

class RivistaCartacea : public Rivista {
 private:
    int n_pagine;
    double cpp; //costo per pagina, può anche essere minore di 0.01;
 protected:
    virtual bool isEqual(const Prodotto&) const;
 public:
    RivistaCartacea(QString tit="", QString edit="", QDate pubb =QDate::currentDate(),
                    QString cat="", int num_p=0, double cpp=0);

    //implemento i metodi virtuali puri;
    virtual double prezzo() const;
    virtual RivistaCartacea* clone() const;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //metodi get/set
    int getN_pagine() const;
    void setN_pagine(int num_p);

    double getCpp() const;
    void setCpp(double);
};

#endif // RIVISTACARTACEA_H
