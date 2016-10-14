#ifndef LIBROCARTACEO_H
#define LIBROCARTACEO_H
#include "libro.h"

class LibroCartaceo : public Libro {
 private:
    double cpp; //indica il costo per stampare una singola pagina (cpp= costo per pagina)
 protected:
    virtual bool isEqual(const Prodotto& p) const;
 public:
    LibroCartaceo(QString tit="",QString edit="",QDate pubb =QDate::currentDate(),
                  QString autore="", QString isbn="", int ediz=1, QString genere="",
                  int num_p=1, double cpp=0);

    //implemento i metodi virtuali puri;
    virtual double prezzo() const;
    virtual LibroCartaceo* clone() const;

    virtual bool operator ==(const Prodotto&) const;
    virtual bool operator !=(const Prodotto&) const;

    //metodi get/set
    double getCpp() const;
    void setCpp(double);
};

#endif // LIBROCARTACEO_H
