#ifndef LIBRO_H
#define LIBRO_H
#include "prodotto.h"

class Libro : public Prodotto {
 private:
    QString autore;
    QString ISBN;
    int edizione;
    QString genere;
    int n_pagine;
 protected:
    //metodo virtuale puro ereditato da Prodotto
    virtual bool isEqual(const Prodotto& p) const =0;
 public:
    Libro(QString tit="", QString edit="", QDate pubb =QDate::currentDate(),
          QString autore="", QString isbn="", int ediz=1, QString gen="", int num_p=0);

    virtual ~Libro();

    //metodi virtuali puri ereditati da Prodotto
    virtual double prezzo() const =0;
    virtual Libro* clone() const =0;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //metodi get/set
    QString getAutore() const;
    void setAutore(QString);

    QString getISBN() const;
    void setISBN(QString);

    int getEdizione() const;
    void setEdizione(int);

    QString getGenere() const;
    void setGenere(QString);

    int getN_pagine() const;
    void setN_pagine(int);

};

#endif // LIBRO_H
