#include "ebook.h"
#include <math.h>
#include <typeinfo>

Ebook::Ebook(QString tit, QString edit, QDate pubb, QString aut, QString cod,
             int ediz, QString gen, int np, double costo, int dim) :
    Libro(tit,edit,pubb,aut,cod,ediz,gen,np), cpKB(costo), dimensione(dim) {}


double Ebook::prezzo() const {
    double base = cpKB*dimensione;    //cpKB può essere anche minore di 1 cent;
    return round(base*100.0)/100.0; //in questo modo restituisco un valore arrotondato alla seconda cifra dopo la ,.
}

Ebook* Ebook::clone() const {
    return new Ebook(*this);
}

bool Ebook::isEqual(const Prodotto& p) const {
    const Ebook* eb = static_cast<const Ebook*>(&p);
    return cpKB == eb->cpKB && dimensione == eb->dimensione
            && Libro::operator==(p);
}

bool Ebook::operator==(const Prodotto& p) const {
    return ( (typeid(*this) == typeid(p) && isEqual(p)));
}

bool Ebook::operator!=(const Prodotto& p) const {
    return !(operator ==(p));
}

double Ebook::getCpKB() const {
    return cpKB;
}
void Ebook::setCpKB(double costo) {
    cpKB=costo;
}

int Ebook::getDimensione() const {
    return dimensione;
}
void Ebook::setDimensione(int dim) {
    dimensione=dim;
}
