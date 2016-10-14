#ifndef FILLFORM_H
#define FILLFORM_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QString>
#include <QDateEdit>
#include "ordine.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
class FillForm : public QDialog {
    Q_OBJECT
 private:
    QVBoxLayout* main;
    QGroupBox* fieldset;
    QPushButton* conferma;
    QHBoxLayout* azione ;
    QVBoxLayout* dati;
    QPushButton* annulla;

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

    Prodotto* &prod;

    const QString& tit;
    const QString& edit;
    const QDate& pubb;
    const int indice;

    void fun_set_elementi_comuni();
    void fun_set_libro();
    void fun_set_libro_cartaceo();
    void fun_set_ebook();
    void fun_set_rivista();
    void fun_set_rivistacartacea();
    void fun_set_rivistadomiciliata();
    void fun_set_rivistadigitale();

    void aggiungiSpecifici();

 public:
    FillForm(Prodotto* &p, const QString& tit, const QString& edit,
             const QDate& pubb, const int tip, QWidget *parent=0);

 private slots:
    void sendData();
 signals:
    void send();
};

#endif // FILLFORM_H
