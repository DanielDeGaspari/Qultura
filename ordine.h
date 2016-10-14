#ifndef ORDINE_H
#define ORDINE_H

#include "prodotto.h"
#include "myiterator.h"

class Ordine {
 friend class iteratore;
 private:
    int capacity;
    int size;
    Prodotto* *array;

    static Prodotto** copia(const Ordine& v);   //effettua la copia profonda
    static void distruggi(Prodotto**, int);
    void allunga(int capacity);
    void compatta(int);

 public:

    typedef MyIterator<Prodotto*> iteratore;
    typedef MyIterator<const Prodotto* const> const_iterator;

    Ordine();
    Ordine(int s);

    Ordine(const Ordine& v);            //copia profonda
    ~Ordine();                          //distruzione profonda
    Ordine& operator=(const Ordine&);   //assegnazione profonda

    bool empty() const;
    void Aggiungi_prodotto(const Prodotto&);
    void Togli_prodotto(int i);
    void Svuota();
    int Size() const;
    void Cambia_tipo(int, const Prodotto&);
    bool operator==(const Ordine&) const;
    bool operator!=(const Ordine&) const;

    //metodi che usano iteratore;
    iteratore begin() const;
    iteratore end() const;
    Prodotto* operator[](iteratore) const;

    //metodi che usano const_iteratore;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const Prodotto* operator[](const_iterator) const;
};

#endif // ORDINE_H
