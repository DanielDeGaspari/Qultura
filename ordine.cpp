#include "ordine.h"

/* METODI DI ORDINE*/

Ordine::Ordine() : capacity(1), size(0), array(new Prodotto*[1]) {}

Ordine::Ordine(int s) : capacity(s), size(s), array(new Prodotto*[s]) {}

Ordine::Ordine(const Ordine& v) : capacity(v.capacity), size(v.size),
        array(copia(v)) {}

Prodotto** Ordine::copia(const Ordine& v) {
    Prodotto* *aux = new Prodotto*[v.capacity];
    for (int i=0; i<v.Size(); i++) {
        Prodotto* temp = v.array[i]->clone();   //copia profonda
        aux[i] = temp;
    }

    return aux;
}

void Ordine::distruggi(Prodotto** p, int dim) {
    for (int i = 0; i< dim; i++) {
        delete p[i];
    }
    delete[] p;
}

Ordine::~Ordine() {
    distruggi(array, size);
}

Ordine& Ordine::operator=(const Ordine& v) {
    if (this != &v) {
        distruggi(array, size);
        array = copia(v);
        size = v.size;
        capacity = v.capacity;
    }
    return *this;
}

bool Ordine::empty() const {
    return size==0;
}

void Ordine::Aggiungi_prodotto(const Prodotto& p) {
    Prodotto* aux = const_cast<Prodotto*>(&p);
    if (size == capacity) {
        allunga(capacity);
    }

    array[size] = aux;
    size++;
}

void Ordine::allunga(int cap) {
    Prodotto* *aux = new Prodotto*[cap*2];

    for (int i = 0; i < cap; i++) {
        Prodotto* temp = array[i]->clone();
        aux[i] = temp;
    }

    distruggi(array, size);

    array = aux;
    capacity = capacity*2;
}

void Ordine::Togli_prodotto(int i) {
    delete array[i];
    compatta(i);
    size=size-1;
}

void Ordine::compatta(int i) {
    for (int j=i; j < Size()-1; j++) {
        array[j] = array[j+1];
    }
}

void Ordine::Svuota() {
    distruggi(array,size);
    size=0;
    capacity=1;
    array = new Prodotto*[1];
}

int Ordine::Size() const {
    return size;
}

void Ordine::Cambia_tipo(int i, const Prodotto& p1) {
    Prodotto* aux = const_cast<Prodotto*>(&p1);
    delete array[i];
    array[i] = aux;
}

bool Ordine::operator ==(const Ordine& o) const {
    if (Size() != o.Size())
        return false;

    for (int i=0; i<size; i++)
        if ( *(array[i]) != *(o.array[i]) )
            return false;
    return true;
}

bool Ordine::operator !=(const Ordine& o) const {
    return !(*this == o);
}

Ordine::iteratore Ordine::begin() const {
    iteratore aux;
    aux.punt = array;
    return aux;
}

Ordine::iteratore Ordine::end() const {
    iteratore aux;
    aux.punt = array + Size();
    return aux;
}

Prodotto* Ordine::operator [](Ordine::iteratore it) const {
    return *(it.punt);
}

Ordine::const_iterator Ordine::cbegin() const {
    const_iterator aux;
    aux.punt = array;
    return aux;
}

Ordine::const_iterator Ordine::cend() const {
    const_iterator aux;
    aux.punt = array + Size();
    return aux;
}

const Prodotto* Ordine::operator [](Ordine::const_iterator cit) const {
    return *(cit.punt);
}
