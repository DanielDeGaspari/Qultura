#include "libro.h"

Libro::Libro(QString tit, QString edit, QDate pubb, QString aut, QString cod, int ediz, QString gen, int np) :
    Prodotto(tit,edit,pubb), autore(aut), ISBN(cod), edizione(ediz), genere(gen), n_pagine(np) {}

Libro::~Libro() {}

bool Libro::operator==(const Prodotto& p) const {
    const Libro* aux = dynamic_cast<const Libro*>(&p);
    if ( aux && Prodotto::operator==(p) && autore == aux->autore &&
         ISBN == aux->ISBN && edizione == aux->edizione &&
         genere == aux->genere && n_pagine == aux->n_pagine)
        return true;
    //else
    return false;
}

bool Libro::operator!=(const Prodotto& p) const {
    return !(operator ==(p));
}

QString Libro::getAutore() const{
    return autore;
}
void Libro::setAutore(QString aut) {
    autore=aut;
}

QString Libro::getISBN() const {
    return ISBN;
}
void Libro::setISBN(QString cod) {
    ISBN=cod;
}

int Libro::getEdizione() const {
    return edizione;
}
void Libro::setEdizione(int ediz) {
    edizione=ediz;
}

QString Libro::getGenere() const {
    return genere;
}
void Libro::setGenere(QString gen) {
    genere=gen;
}

int Libro::getN_pagine() const {
    return n_pagine;
}
void Libro::setN_pagine(int x) {
    n_pagine=x;
}
