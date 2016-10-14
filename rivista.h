#ifndef RIVISTA_H
#define RIVISTA_H
#include "prodotto.h"
#include <QString>

class Rivista : public Prodotto {
 private:
    QString categoria;  //indica il tipo di rivista, programmi tv, gossip, sport ecc..
 protected:
    //metodo virtuale puro ereditato da Prodotto
    virtual bool isEqual(const Prodotto&) const =0;
 public:
    Rivista(QString titolo="", QString editore="",
            QDate pubb =QDate::currentDate(), QString categoria="");

    virtual ~Rivista();

    //metodi virtuali puri ereditati da Prodotto
    virtual double prezzo() const =0;
    virtual Rivista* clone() const =0;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //Metodi get/set
    QString getCategoria() const;
    void setCategoria(QString categoria);

};
#endif // RIVISTA_H
