#include "fillform.h"
#include "librocartaceo.h"
#include "ebook.h"
#include "rivistadomiciliata.h"
#include "rivistacartacea.h"
#include "rivistadigitale.h"
#include "tabella.h"

FillForm::FillForm(Prodotto* &p, const QString& t,
                   const QString& ed, const QDate& pub,
                   const int tip, QWidget *parent):
                        QDialog(parent), prod(p), tit(t), edit(ed),
                        pubb(pub), indice(tip) {

    this->setWindowTitle("Continua con l'inserimento dei dati");
    QDialog::reject();
    this->setModal(true);
    this->resize(500,300);

    main = new QVBoxLayout;

    fieldset = new QGroupBox(tr("Inserisci i dati specifici del prodotto"));
        dati = new QVBoxLayout;

        //Creo gli elementi in comune a tutti i prodotti;
        fun_set_elementi_comuni();

        //Dati specifici:
        aggiungiSpecifici();

    fieldset->setLayout(dati);

    azione = new QHBoxLayout;
        conferma = new QPushButton(tr("Conferma"));
        connect(conferma, SIGNAL(clicked(bool)), this, SLOT(sendData()));

        annulla = new QPushButton(tr("Torna indietro"));
        connect(annulla, SIGNAL(clicked(bool)), this, SLOT(close()));

        azione->addWidget(conferma);
        azione->addWidget(annulla);

    main->addWidget(fieldset);
    main->addLayout(azione);
    this->setLayout(main);
}

void FillForm::fun_set_elementi_comuni() {
    titolo=new QLineEdit;
    titolo->setText(tit);
    titolo->setEnabled(false);
    editore=new QLineEdit;
    editore->setText(edit);
    editore->setEnabled(false);
    pubblicazione=new QDateEdit;
    pubblicazione->setDate(pubb);
    pubblicazione->setEnabled(false);

    tipologia=new QComboBox;
    tipologia->insertItem(0, "Libro Cartaceo");
    tipologia->insertItem(1, "Ebook");
    tipologia->insertItem(2, "Rivista Cartacea");
    tipologia->insertItem(3, "Rivista Domiciliata");
    tipologia->insertItem(4, "Rivista digitale");
    tipologia->setCurrentIndex(indice);
    tipologia->setEnabled(false);

    //Dati in comune;
    QLabel* title= new QLabel(tr("Titolo:"));
    dati->addWidget(title);
    dati->addWidget(titolo);

    QLabel* edition= new QLabel(tr("Editore:"));
    dati->addWidget(edition);
    dati->addWidget(editore);

    QLabel* dpubb= new QLabel(tr("Pubblicazione:"));
    dati->addWidget(dpubb);
    dati->addWidget(pubblicazione);

    QLabel* tip= new QLabel(tr("Tipologia:"));
    dati->addWidget(tip);
    dati->addWidget(tipologia);

}

void FillForm::fun_set_libro() {
    autore = new QLineEdit;
    ISBN = new  QLineEdit;
    edizione = new QSpinBox;
    edizione->setRange(1,50);
    genere = new QLineEdit;

    n_pagine = new QSpinBox;
    n_pagine->setRange(1,10000);
    n_pagine->setAccelerated(true);

    QLabel* aut = new QLabel(tr("Autore:"));
    dati->addWidget(aut);
    dati->addWidget(autore);

    QLabel* codi = new QLabel(tr("ISBN:"));
    dati->addWidget(codi);
    dati->addWidget(ISBN);

    QLabel* ed = new QLabel(tr("Edizione:"));
    dati->addWidget(ed);
    dati->addWidget(edizione);

    QLabel* gen = new QLabel(tr("Genere:"));
    dati->addWidget(gen);
    dati->addWidget(genere);

    QLabel* num_p = new QLabel(tr("Numero pagine:"));
    dati->addWidget(num_p);
    dati->addWidget(n_pagine);
}

void FillForm::fun_set_libro_cartaceo() {
    cpp = new QDoubleSpinBox;
    cpp->setDecimals(3);
    cpp->setMinimum(0.001);

    QLabel* cost = new QLabel(tr("Costo per la stampa di una pagina singola pagina:"));
    dati->addWidget(cost);
    dati->addWidget(cpp);
}

void FillForm::fun_set_ebook() {
    cpKB = new QDoubleSpinBox;
    cpKB->setDecimals(5);
    cpKB->setMinimum(0.00001);
    dimensione = new QSpinBox;
    dimensione->setRange(1,1000000000);
    dimensione->setAccelerated(true);

    QLabel* cost = new QLabel(tr("Costo per KB:"));
    dati->addWidget(cost);
    dati->addWidget(cpKB);

    QLabel* dim = new QLabel(tr("Dimensione in KB:"));
    dati->addWidget(dim);
    dati->addWidget(dimensione);
}

void FillForm::fun_set_rivista() {
    categoria = new QLineEdit;

    QLabel* cat = new QLabel(tr("Categoria:"));
    dati->addWidget(cat);
    dati->addWidget(categoria);
}

void FillForm::fun_set_rivistacartacea() {
    n_pagine = new QSpinBox;
    n_pagine->setRange(1,10000);
    n_pagine->setAccelerated(true);

    cpp = new QDoubleSpinBox;
    cpp->setDecimals(3);
    cpp->setMinimum(0.001);

    QLabel* num_p = new QLabel(tr("Numero Pagine:"));
    dati->addWidget(num_p);
    dati->addWidget(n_pagine);

    QLabel* cost = new QLabel(tr("Costo per la stampa di una pagina singola pagina:"));
    dati->addWidget(cost);
    dati->addWidget(cpp);
}

void FillForm::fun_set_rivistadomiciliata() {
    maggiorazione = new QDoubleSpinBox;
    maggiorazione->setAccelerated(true);
    maggiorazione->setMinimum(0.01);

    QLabel* mag = new QLabel(tr("Maggiorazione:"));
    dati->addWidget(mag);
    dati->addWidget(maggiorazione);
}

void FillForm::fun_set_rivistadigitale() {
    cpKB = new QDoubleSpinBox;
    cpKB->setDecimals(5);
    cpKB->setMinimum(0.00001);
    dimensione = new QSpinBox;
    dimensione->setRange(1,1000000000);
    dimensione->setAccelerated(true);

    QLabel* cost = new QLabel(tr("Costo per KB:"));
    dati->addWidget(cost);
    dati->addWidget(cpKB);

    QLabel* dim = new QLabel(tr("Dimensione in KB:"));
    dati->addWidget(dim);
    dati->addWidget(dimensione);
}



void FillForm::sendData() {
    QString tit = titolo->text();
    QString edit = editore->text();
    QDate pubb = pubblicazione->date();

    QString cat;

    int np;
    double costopp;

    int dim;
    double costopb;

    double mag;

    QString gen;
    QString aut;
    QString cod;
    int ediz;

    switch (tipologia->currentIndex()) {
    case 0: //Libro Cartaceo
        gen = genere->text();
        aut = autore->text();
        cod = ISBN->text();
        ediz = edizione->value();
        np = n_pagine->value();
        costopp = cpp->value();

        prod = new LibroCartaceo(tit,edit,pubb,aut,cod,ediz,gen,np,costopp);
        break;

    case 1: //Ebook
        gen = genere->text();
        aut = autore->text();
        cod = ISBN->text();
        ediz = edizione->value();
        np = n_pagine->value();
        costopb = cpKB->value();
        dim = dimensione->value();

        prod = new Ebook(tit,edit,pubb,aut,cod,ediz,gen,np,costopb,dim);
        break;

    case 2: //Rivista Cartacea
        np = n_pagine->value();
        costopp = cpp->value();
        cat = categoria->text();

        prod = new RivistaCartacea(tit,edit,pubb,cat,np,costopp);
        break;

    case 3: //Rivista Domiciliata
        np = n_pagine->value();
        costopp = cpp->value();
        cat = categoria->text();
        mag = maggiorazione->value();

        prod = new RivistaDomiciliata(tit,edit,pubb,cat,np,costopp,mag);
        break;

    case 4: //Rivista Digitale
        costopb = cpKB->value();
        dim = dimensione->value();
        cat = categoria->text();

        prod = new RivistaDigitale(tit,edit,pubb,cat,costopb,dim);
        break;
    }

    emit send();

    close();
}

void FillForm::aggiungiSpecifici() {
    switch (tipologia->currentIndex()) {
     case 0:    //libro cartaceo;
        fun_set_libro();
        fun_set_libro_cartaceo();
        break;
    case 1:     //ebook;
        fun_set_libro();
        fun_set_ebook();
        break;
    case 2:     //rivista cartacea
        fun_set_rivista();
        fun_set_rivistacartacea();
        break;
    case 3:     //rivista domiciliata
        fun_set_rivista();
        fun_set_rivistacartacea();
        fun_set_rivistadomiciliata();
        break;
    case 4:     //rivista digitale
        fun_set_rivista();
        fun_set_rivistadigitale();
        break;
    }
}
