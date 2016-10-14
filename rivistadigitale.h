#ifndef RIVISTADIGITALE_H
#define RIVISTADIGITALE_H
#include "rivista.h"

class RivistaDigitale : public Rivista {
 private:
    double cpKB;
    int dimensione;
 protected:
    virtual bool isEqual(const Prodotto&) const;
 public:
    RivistaDigitale(QString tit="", QString edit="", QDate pubb =QDate::currentDate(),
                    QString cat="", double costo=0, int dim=0);

    //implemento i metodi virtuali puri;
    virtual double prezzo() const;
    virtual RivistaDigitale* clone() const;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //metodi get/set
    double getCpKB() const;
    void setCpKB(double costo);

    int getDimensione() const;
    void setDimensione(int);
};

#endif // RIVISTADIGITALE_H
