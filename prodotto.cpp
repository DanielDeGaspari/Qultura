#include "prodotto.h"

Prodotto::Prodotto(QString tit, QString edit, QDate pubb) :
    titolo(tit), editore(edit), data_pubblicazione(pubb) {}

Prodotto::~Prodotto() {}

bool Prodotto::operator==(const Prodotto& p) const {
    return (titolo == p.titolo && editore == p.editore &&
            data_pubblicazione == p.data_pubblicazione);
}

bool Prodotto::operator!=(const Prodotto& p) const {
    return !(operator==(p));
}

QString Prodotto::getTitolo() const {
    return titolo;
}
void Prodotto::setTitolo(QString tit) {
    titolo=tit;
}

QString Prodotto::getEditore() const {
    return editore;
}
void Prodotto::setEditore(QString edit) {
    editore=edit;
}

QDate Prodotto::getPubblicazione() const {
    return data_pubblicazione;
}
void Prodotto::setPubblicazione(QDate data) {
    data_pubblicazione=data;
}
