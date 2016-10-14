#include "riga.h"
#include <typeinfo>

Riga::Riga(Ordine& o, int i, QWidget* parent, Prodotto* p) :
     QWidget(parent), prod(p), ord(o), n_riga(i)  {

    //Creo gli elementi;
    fun_set_elementi();

    //questa connect deve stare prima di fun_stampa_prod, altrimenti cambio la tipologia dopo la stampa.
    connect(tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(setTipologia(int)));

    //leggo il prodotto prod, e faccio il set dei vari campi
    fun_stampa_prod();

    //Modifiche agli elementi:
    //se cambio la tipologia del prodotto, elimino il vecchio prodotto inserendone uno nuovo del tipo scelto, con lo stesso titolo, autore, e data di pubblicazione;
    //textChanged vs editingFinished : editingFinished si attiva ogni volta che sposto il cursore; textChanged si attiva ad ogni modifica del testo, carattere per carattere.
    connect(tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(setPuntatore(int)));
    connect(titolo,SIGNAL(textChanged(QString)), this, SLOT(setTitolo(QString)));
    connect(editore,SIGNAL(textChanged(QString)), this, SLOT(setEditore(QString)));
    connect(pubblicazione,SIGNAL(dateChanged(QDate)), this, SLOT(setPubblicazione(QDate)));
    connect(autore, SIGNAL(textChanged(QString)), this, SLOT(setAutore(QString)));
    connect(ISBN, SIGNAL(textChanged(QString)), this, SLOT(setISBN(QString)));
    connect(genere, SIGNAL(textChanged(QString)), this, SLOT(setGenere(QString)));
    connect(edizione, SIGNAL(valueChanged(int)), this, SLOT(setEdizione(int)));
    connect(categoria, SIGNAL(textChanged(QString)), this, SLOT(setCategoria(QString)));
    connect(n_pagine, SIGNAL(valueChanged(int)), this, SLOT(setN_pagine(int)));
    connect(cpp, SIGNAL(valueChanged(double)), this, SLOT(setCpp(double)));
    connect(cpKB, SIGNAL(valueChanged(double)), this, SLOT(setCpKB(double)));
    connect(dimensione, SIGNAL(valueChanged(int)), this, SLOT(setDimensione(int)));
    connect(maggiorazione,SIGNAL(valueChanged(double)), this, SLOT(setMaggiorazione(double)));
}

void Riga::fun_stampa_prod() {
    //elementi in comune
    titolo->setText(prod->getTitolo());
    editore->setText(prod->getEditore());
    pubblicazione->setDate(prod->getPubblicazione());
    //elementi specifici
    if (typeid(RivistaCartacea) == typeid(*prod)){  //se il prodotto è un una rivistaCartacea;
      const RivistaCartacea* rc = static_cast<const RivistaCartacea*>(prod);
        tipologia->setCurrentIndex(2);
        n_pagine->setValue(rc->getN_pagine());
        categoria->setText(rc->getCategoria());
        cpp->setValue(rc->getCpp());
    }
    else
        if (typeid(RivistaDomiciliata) == typeid(*prod)){  //se il prodotto è un una rivistaDomiciliata;
          const RivistaDomiciliata* rd = static_cast<const RivistaDomiciliata*>(prod);
            tipologia->setCurrentIndex(3);
            n_pagine->setValue(rd->getN_pagine());
            categoria->setText(rd->getCategoria());
            cpp->setValue(rd->getCpp());
            maggiorazione->setValue(rd->getMaggiorazione());
        }
    else
            if (typeid(RivistaDigitale) == typeid(*prod)){  //se il prodotto è un una rivistaDigitale;
            const RivistaDigitale* rd = static_cast<const RivistaDigitale*>(prod);
            tipologia->setCurrentIndex(4);
            categoria->setText(rd->getCategoria());
            cpKB->setValue(rd->getCpKB());
            dimensione->setValue(rd->getDimensione());
        }
    else
            if (typeid(LibroCartaceo) == typeid(*prod)){  //se il prodotto è un una libroCartaceo;
            const LibroCartaceo* lc = static_cast<const LibroCartaceo*>(prod);
            tipologia->setCurrentIndex(0);
            autore->setText(lc->getAutore());
            ISBN->setText(lc->getISBN());
            edizione->setValue(lc->getEdizione());
            genere->setText(lc->getGenere());
            n_pagine->setValue(lc->getN_pagine());
            cpp->setValue(lc->getCpp());
        }
    else
            if (typeid(Ebook) == typeid(*prod)){  //se il prodotto è un Ebook;
            const Ebook* eb = static_cast<const Ebook*>(prod);
            tipologia->setCurrentIndex(1);
            autore->setText(eb->getAutore());
            ISBN->setText(eb->getISBN());
            edizione->setValue(eb->getEdizione());
            genere->setText(eb->getGenere());
            n_pagine->setValue(eb->getN_pagine());
            dimensione->setValue(eb->getDimensione());
            cpKB->setValue(eb->getCpKB());
        }
}

void Riga::setTipologia(int i) {
    reset_valori();
    //libro cartaceo;
    switch ( i ) {
        //libro cartaceo
        case 0:
            autore->setDisabled(false);
            ISBN->setDisabled(false);
            edizione->setDisabled(false);
            genere->setDisabled(false);
            n_pagine->setDisabled(false);
            cpp->setDisabled(false);

            autore->setFrame(true);
            ISBN->setFrame(true);
            genere->setFrame(true);

            categoria->setDisabled(true);
            cpKB->setDisabled(true);
            dimensione->setDisabled(true);
            maggiorazione->setDisabled(true);

            categoria->setFrame(false);
            break;
        //ebook
        case 1:
            autore->setDisabled(false);
            ISBN->setDisabled(false);
            edizione->setDisabled(false);
            genere->setDisabled(false);
            n_pagine->setDisabled(false);
            cpKB->setDisabled(false);
            dimensione->setDisabled(false);

            autore->setFrame(true);
            ISBN->setFrame(true);
            genere->setFrame(true);

            cpp->setDisabled(true);
            categoria->setDisabled(true);
            maggiorazione->setDisabled(true);

            categoria->setFrame(false);
        break;
        //rivista cartacea
        case 2:
            n_pagine->setDisabled(false);
            categoria->setDisabled(false);
            cpp->setDisabled(false);

            categoria->setFrame(true);

            cpKB->setDisabled(true);
            dimensione->setDisabled(true);
            autore->setDisabled(true);
            ISBN->setDisabled(true);
            edizione->setDisabled(true);
            genere->setDisabled(true);
            maggiorazione->setDisabled(true);

            autore->setFrame(false);
            ISBN->setFrame(false);
            genere->setFrame(false);
        break;
        //rivista domiciliata
        case 3:
            n_pagine->setDisabled(false);
            categoria->setDisabled(false);
            cpp->setDisabled(false);
            maggiorazione->setDisabled(false);

            categoria->setFrame(true);

            cpKB->setDisabled(true);
            dimensione->setDisabled(true);
            autore->setDisabled(true);
            ISBN->setDisabled(true);
            edizione->setDisabled(true);
            genere->setDisabled(true);

            autore->setFrame(false);
            ISBN->setFrame(false);
            genere->setFrame(false);
        break;
        //rivista digitale
        case 4:
            categoria->setDisabled(false);
            cpKB->setDisabled(false);
            dimensione->setDisabled(false);

            categoria->setFrame(true);

            n_pagine->setDisabled(true);
            cpp->setDisabled(true);
            maggiorazione->setDisabled(true);
            autore->setDisabled(true);
            ISBN->setDisabled(true);
            edizione->setDisabled(true);
            genere->setDisabled(true);

            autore->setFrame(false);
            ISBN->setFrame(false);
            genere->setFrame(false);

        break;
    }
}

void Riga::reset_valori() {
    categoria->setText("");
    cpp->setValue(0);
    cpKB->setValue(0);
    dimensione->setValue(1);
    n_pagine->setValue(1);
    maggiorazione->setValue(0);
    autore->setText("");
    ISBN->setText("");
    edizione->setValue(1);
    genere->setText("");
}

void Riga::setPuntatore(int x) {
    switch ( x ) {
    case 0:
        prod = new LibroCartaceo(prod->getTitolo(),
            prod->getEditore(), prod->getPubblicazione());
        ord.Cambia_tipo(n_riga,*prod);
        break;
    case 1:
        prod = new Ebook(prod->getTitolo(),
            prod->getEditore(), prod->getPubblicazione());
        ord.Cambia_tipo(n_riga,*prod);
        break;
    case 2:
        prod = new RivistaCartacea(prod->getTitolo(),
            prod->getEditore(), prod->getPubblicazione());
        ord.Cambia_tipo(n_riga,*prod);
        break;
    case 3:
        prod = new RivistaDomiciliata(prod->getTitolo(),
            prod->getEditore(), prod->getPubblicazione());
        ord.Cambia_tipo(n_riga,*prod);
        break;
    case 4:
        prod = new RivistaDigitale(prod->getTitolo(),
            prod->getEditore(), prod->getPubblicazione());
        ord.Cambia_tipo(n_riga,*prod);
        break;
    }
}

/* Elenco di metodi get */

QLineEdit* Riga::getTitolo() const {
    return titolo;
}

QLineEdit* Riga::getEditore() const {
    return editore;
}

QDateEdit* Riga::getPubblicazione() const {
    return pubblicazione;
}

QComboBox* Riga::getTipologia() const {
    return tipologia;
}

QLineEdit* Riga::getCategoria() const {
    return categoria;
}

QSpinBox* Riga::getN_pagine() const {
    return n_pagine;
}

QDoubleSpinBox* Riga::getCpp() const {
    return cpp;
}

QDoubleSpinBox* Riga::getCpKB() const {
    return cpKB;
}

QSpinBox* Riga::getDimensione() const {
    return dimensione;
}

QDoubleSpinBox* Riga::getMaggiorazione() const {
    return maggiorazione;
}

QLineEdit* Riga::getGenere() const {
    return genere;
}

QLineEdit* Riga::getAutore() const {
    return autore;
}

QLineEdit* Riga::getISBN() const {
    return ISBN;
}

QSpinBox* Riga::getEdizione() const {
    return edizione;
}

Prodotto* Riga::getProd() const {
    return prod;
}



/* Elenco di metodi set */

void Riga::setTitolo(QString t) {
    prod->setTitolo(t);
}

void Riga::setEditore(QString e) {
    prod->setEditore(e);
}

void Riga::setPubblicazione(QDate d) {
    prod->setPubblicazione(d);
}

void Riga::setCategoria(QString c) {
    RivistaCartacea* rc = dynamic_cast<RivistaCartacea*>(prod);
    if (rc) {
        rc->setCategoria(c);
        return;
    }

    RivistaDigitale* rd = dynamic_cast<RivistaDigitale*>(prod);
    if (rd) {
        rd->setCategoria(c);
        return;
    }
}

void Riga::setN_pagine(int np) {
    RivistaCartacea* rc = dynamic_cast<RivistaCartacea*>(prod);
    if (rc) {
        rc->setN_pagine(np);
        return;
    }

    Libro* lb = dynamic_cast<Libro*>(prod);
    if (lb) {
        lb->setN_pagine(np);
        return;
    }
}

void Riga::setCpp(double costo) {
    RivistaCartacea* rc = dynamic_cast<RivistaCartacea*>(prod);
    if (rc) {
        rc->setCpp(costo);
        return;
    }

    LibroCartaceo* lc = dynamic_cast<LibroCartaceo*>(prod);
    if (lc) {
        lc->setCpp(costo);
        return;
    }

}

void Riga::setCpKB(double costo) {
    RivistaDigitale* rd = dynamic_cast<RivistaDigitale*>(prod);
    if (rd) {
        rd->setCpKB(costo);
        return;
    }

    Ebook* eb = dynamic_cast<Ebook*>(prod);
    if (eb) {
        eb->setCpKB(costo);
        return;
    }
}

void Riga::setDimensione(int dim) {
    RivistaDigitale* rd = dynamic_cast<RivistaDigitale*>(prod);
    if (rd) {
        rd->setDimensione(dim);
        return;
    }

    Ebook* eb = dynamic_cast<Ebook*>(prod);
    if (eb) {
        eb->setDimensione(dim);
        return;
    }
}

void Riga::setMaggiorazione(double mag) {
    RivistaDomiciliata* rd = dynamic_cast<RivistaDomiciliata*>(prod);
    if (rd) {
        rd->setMaggiorazione(mag);
        return;
    }
}

void Riga::setGenere(QString gen) {
    Libro* lb = dynamic_cast<Libro*>(prod);
    if (lb) {
        lb->setGenere(gen);
        return;
    }
}

void Riga::setAutore(QString aut) {
    Libro* lb = dynamic_cast<Libro*>(prod);
    if (lb) {
        lb->setAutore(aut);
        return;
    }
}

void Riga::setISBN(QString cod) {
    Libro* lb = dynamic_cast<Libro*>(prod);
    if (lb) {
        lb->setISBN(cod);
        return;
    }
}

void Riga::setEdizione(int ed) {
    Libro* lb = dynamic_cast<Libro*>(prod);
    if (lb) {
        lb->setEdizione(ed);
        return;
    }
}

/* Funzioni di creazione degli elementi */

void Riga::fun_set_elementi() {
    //Creo gli elementi in comune a tutti i prodotti;
    fun_set_elementi_comuni();

    //Creo gli elementi di libro:
    fun_set_libro();

    //Creo gli elementi di rivista:
    fun_set_rivista();
}

void Riga::fun_set_elementi_comuni() {
    titolo=new QLineEdit;
    editore=new QLineEdit;
    pubblicazione=new QDateEdit;
    pubblicazione->setAccelerated(true);

    tipologia=new QComboBox;
    tipologia->insertItem(0, "Libro Cartaceo");
    tipologia->insertItem(1, "Ebook");
    tipologia->insertItem(2, "Rivista Cartacea");
    tipologia->insertItem(3, "Rivista Domiciliata");
    tipologia->insertItem(4, "Rivista digitale");
}

void Riga::fun_set_libro() {
    autore = new QLineEdit;
    ISBN = new  QLineEdit;
    edizione = new QSpinBox;
    edizione->setRange(1,50);
    genere = new QLineEdit;
    n_pagine = new QSpinBox;
    n_pagine->setRange(1,10000);
    n_pagine->setAccelerated(true);

    //creo gli elementi specifici di libro cartaceo;
    fun_set_libro_cartaceo();
    //creo gli elementi specifici di ebook;
    fun_set_ebook();
}

void Riga::fun_set_libro_cartaceo() {
    cpp = new QDoubleSpinBox;
    cpp->setDecimals(3);
}

void Riga::fun_set_ebook() {
    cpKB = new QDoubleSpinBox;
    cpKB->setDisabled(true);
    cpKB->setDecimals(5);
    dimensione = new QSpinBox;
    dimensione->setMinimum(1);
    dimensione->setMaximum(1000000000);
    dimensione->setAccelerated(true);
    dimensione->setDisabled(true);
}

void Riga::fun_set_rivista() {
    categoria = new QLineEdit;
    categoria->setDisabled(true);

    fun_set_rivistacartacea();
    fun_set_rivistadomiciliata();
    fun_set_rivistadigitale();
}

void Riga::fun_set_rivistacartacea() {
    //n_pagine già presente;
    //cpp già presente;
}

void Riga::fun_set_rivistadomiciliata() {
    maggiorazione = new QDoubleSpinBox;
    maggiorazione->setMinimum(0.01);
    maggiorazione->setDecimals(2);
    maggiorazione->setDisabled(true);
}

void Riga::fun_set_rivistadigitale() {
    //cpKB già presente;
    //dimensione già presente;
}
