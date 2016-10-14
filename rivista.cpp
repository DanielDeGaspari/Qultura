#include "rivista.h"

Rivista::Rivista(QString tit, QString edit, QDate pubb, QString cat) :
        Prodotto(tit,edit,pubb) , categoria(cat) {}

Rivista::~Rivista() {}

bool Rivista::operator==(const Prodotto& p) const {
    const Rivista* aux = dynamic_cast<const Rivista*>(&p);
    if ( aux && Prodotto::operator==(p) && categoria == aux->categoria)
        return true;
    //else
    return false;
}

bool Rivista::operator!=(const Prodotto& p) const {
    return !(operator==(p));
}

QString Rivista::getCategoria() const {
    return categoria;
}
void Rivista::setCategoria(QString cat) {
    categoria=cat;
}
