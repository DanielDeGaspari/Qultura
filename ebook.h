#ifndef EBOOK_H
#define EBOOK_H
#include "libro.h"


class Ebook : public Libro {
 private:
    double cpKB; //indica il costo per l'invio di un singolo KB (cpKB= costo per KB)
                //cpKB può essere anche minore di 0.01;
    int dimensione;
 protected:
    virtual bool isEqual(const Prodotto& p) const;
 public:
    Ebook(QString tit="",QString edit="",QDate pubb =QDate::currentDate(),
          QString autore="", QString isbn="", int ediz=1, QString gen="",
          int num_p=1, double cpKB=0, int dim=0);

    //implemento i metodi virtuali puri;
    virtual double prezzo() const;
    virtual Ebook* clone() const;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //metodi get/set
    double getCpKB() const;
    void setCpKB(double);

    int getDimensione() const;
    void setDimensione(int);
};

#endif // EBOOK_H
