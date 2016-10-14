#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include "riga.h"
#include "tabella.h"

Tabella::Tabella(Ordine& o, QWidget* parent) : QTableWidget(parent), ord(o)
{
    /* Configurazione generali della tabella */
    this->setRowCount(0);
    this->setColumnCount(14);

    QStringList header;
    header<<"titolo"<<"editore"<<"data pubblicazione" <<"tipo prodotto"
         <<"autore"<<"ISBN"<<"edizione"<<"genere"<<"numero pagine"
         <<"costo per pagina(€)"
         <<"costo per KB(€)"<<"dimensione(KB)"
         <<"tipo rivista"<<"maggiorazione";
    this->setHorizontalHeaderLabels(header);

    hideAll();
    for (int i=0; i<4; i++)
        this->setColumnWidth(i,150);
}

void Tabella::load() {
    rimuovi_tutte();
    for (Ordine::iteratore it=ord.begin(); it != ord.end(); ++it) {
        aggiungi(ord[it]);
    }
    this->resizeColumnsToContents();
}

/* Definizione dei public slots */

//inserisce una nuova riga;
void Tabella::aggiungi(Prodotto* p) {
    int indice=this->rowCount();
    this->insertRow(indice);

    if (indice==ord.Size()) {   //è l nuova riga che sto aggiungendo dal pulsante.
        ord.Aggiungi_prodotto(*p);
    }

    //"definisco" la nuova riga;
    Riga* item = new Riga(ord, indice, this, p);

    //costruisco la riga, definendone le varie componenti in comune a tutti i prodotti;
    this->setCellWidget(indice,0,item->getTitolo());
    this->setCellWidget(indice,1,item->getEditore());
    this->setCellWidget(indice,2,item->getPubblicazione());
    this->setCellWidget(indice,3,item->getTipologia());
    //Specifici di libro
    this->setCellWidget(indice,4,item->getAutore());
    this->setCellWidget(indice,5,item->getISBN());
    this->setCellWidget(indice,6,item->getEdizione());
    this->setCellWidget(indice,7,item->getGenere());
    this->setCellWidget(indice,8,item->getN_pagine());
    //Specifici di libro cartaceo
    this->setCellWidget(indice,9,item->getCpp());
    //Specifici di ebook
    this->setCellWidget(indice,10,item->getCpKB());
    this->setCellWidget(indice,11,item->getDimensione());
    //Specifici di rivista
    this->setCellWidget(indice,12,item->getCategoria());
    //Specifici di rivista cartacea
        //già presenti;
    //Specifici di rivista domiciliata
    this->setCellWidget(indice,13,item->getMaggiorazione());
    //Specifici di rivista digitale
        //già presenti;
    this->setCurrentCell(indice,0);
}

void Tabella::rimuovi() {
    //situazione in cui non ci sono elementi.
    if (!this->rowCount()) {
        QMessageBox::information(this,"Errore","Impossibile completare l'azione, non ci sono elementi");
        return;
    }

    int indice = this->currentRow();
    this->removeRow(indice);

    ord.Togli_prodotto(indice);

    if (indice)
    this->setCurrentCell(indice-1,0);
}

void Tabella::rimuovi_tutte() {
    while (this->rowCount()) {
        //rimuovo, uno a uno, tutti gli elementi;
        rimuovi();
    }
}

void Tabella::showAll() {
    for (int i=4; i<14; i++) {
        this->showColumn(i);
        this->resizeColumnToContents(i);
    }
}

void Tabella::hideAll() {
    for (int i=4; i<14; i++)
        this->hideColumn(i);
}
