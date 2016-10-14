#ifndef RIGA_H
#define RIGA_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QString>
#include <QDateEdit>
#include "ordine.h"
#include "librocartaceo.h"
#include "ebook.h"
#include "rivistacartacea.h"
#include "rivistadigitale.h"
#include "rivistadomiciliata.h"

class Riga : public QWidget {
    Q_OBJECT

 private:
    //Elementi in comune;
    QLineEdit* titolo;
    QLineEdit* editore;
    QDateEdit* pubblicazione;
    QComboBox* tipologia;

    //Elementi di rivista;
    QLineEdit* categoria;

    //Elementi di rivista cartacea;
    QSpinBox* n_pagine; //presente anche su libro
    QDoubleSpinBox* cpp; //presente anche su libro cartaceo

    //Elementi di rivista digitale;
    QDoubleSpinBox* cpKB; //presente anche su ebook
    QSpinBox* dimensione; //presente anche su ebook

    //Elementi di rivista domiciliata;
    QDoubleSpinBox* maggiorazione;

    //Elementi di Libro
    QLineEdit* genere;
    QLineEdit* autore;
    QLineEdit* ISBN;
    QSpinBox* edizione;

    Prodotto* prod;
    Ordine& ord;
    int n_riga;

    void fun_set_elementi();
    void fun_set_elementi_comuni();
    void fun_set_libro();
    void fun_set_libro_cartaceo();
    void fun_set_ebook();
    void fun_set_rivista();
    void fun_set_rivistacartacea();
    void fun_set_rivistadomiciliata();
    void fun_set_rivistadigitale();
    void reset_valori();
    void fun_stampa_prod();

 public:
    Riga(Ordine&, int riga, QWidget* parent=0, Prodotto* p= new LibroCartaceo);

    QLineEdit* getTitolo() const;
    QLineEdit* getEditore() const;
    QDateEdit* getPubblicazione() const;
    QComboBox* getTipologia() const;

    QLineEdit* getCategoria() const;

    QSpinBox* getN_pagine() const;
    QDoubleSpinBox* getCpp() const;

    QDoubleSpinBox* getCpKB() const;
    QSpinBox* getDimensione() const;

    QDoubleSpinBox* getMaggiorazione() const;

    QLineEdit* getGenere() const;
    QLineEdit* getAutore() const;
    QLineEdit* getISBN() const;
    QSpinBox* getEdizione() const;
    Prodotto* getProd() const;

 private slots:
    void setTitolo(QString);
    void setEditore(QString);
    void setPubblicazione(QDate);
    void setTipologia(int);
    void setPuntatore(int);

    void setCategoria(QString);

    void setN_pagine(int);
    void setCpp(double);

    void setCpKB(double);
    void setDimensione(int);

    void setMaggiorazione(double);

    void setGenere(QString);
    void setAutore(QString);
    void setISBN(QString);
    void setEdizione(int);

};

#endif // RIGA_H
