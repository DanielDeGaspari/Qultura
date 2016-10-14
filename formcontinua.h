#ifndef FORMCONTINUA_H
#define FORMCONTINUA_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QDateEdit>
#include "ordine.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "fillform.h"

class FormContinua : public QDialog {
    Q_OBJECT
 private:
    QVBoxLayout* main;
    QGroupBox* fieldset;
    QPushButton* continua;
    QHBoxLayout* azione ;
    QVBoxLayout* dati;
    QPushButton* annulla;

    //Elementi in comune;
    QLineEdit* titolo;
    QLineEdit* editore;
    QDateEdit* pubblicazione;
    QComboBox* tipologia;

    Prodotto* &prod;

    FillForm* nuovaForm;
    void fun_set_elementi_comuni();
 public:
    FormContinua(Prodotto* &p, QWidget *parent=0);

 private slots:
    void prosegui();
 signals:
    void send();
};

#endif // FORMCONTINUA_H
