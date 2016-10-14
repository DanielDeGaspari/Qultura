#ifndef PRODOTTO_H
#define PRODOTTO_H
#include <QString>
#include <QDate>

class Prodotto {
 private:
    QString titolo;
    QString editore;
    QDate data_pubblicazione;
 protected:
    virtual bool isEqual(const Prodotto&) const =0;
 public:
    Prodotto(QString tit="", QString edit="", QDate pubb =QDate::currentDate());
    virtual ~Prodotto();

    //metodi virtuali puri
    virtual double prezzo() const =0;
    virtual Prodotto* clone() const =0;

    virtual bool operator==(const Prodotto&) const;
    virtual bool operator!=(const Prodotto&) const;

    //Metodi get/set
    QString getTitolo() const;
    void setTitolo(QString titolo);

    QString getEditore() const;
    void setEditore(QString editore);

    QDate getPubblicazione() const;
    void setPubblicazione(QDate data_pubblicazione);
};

#endif // PRODOTTO_H
