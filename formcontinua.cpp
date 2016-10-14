#include "formcontinua.h"

FormContinua::FormContinua(Prodotto* &p ,QWidget *parent) : QDialog(parent), prod(p){
    this->setWindowTitle("Aggiungi un nuovo dato");
    QDialog::reject();
    this->setModal(true);
    this->resize(500,300);

    main = new QVBoxLayout;

    fieldset = new QGroupBox(tr("Inserisci i dati generali del prodotto"));
        dati = new QVBoxLayout;

        //Creo gli elementi in comune a tutti i prodotti;
        fun_set_elementi_comuni();

    fieldset->setLayout(dati);

    azione = new QHBoxLayout;
        continua = new QPushButton(tr("Continua"));
        connect(continua, SIGNAL(clicked(bool)), this, SLOT(prosegui()));

        annulla = new QPushButton(tr("Annulla"));
        connect(annulla, SIGNAL(clicked(bool)), this, SLOT(close()));

        azione->addWidget(continua);
        azione->addWidget(annulla);

    main->addWidget(fieldset);
    main->addLayout(azione);
    this->setLayout(main);
}

void FormContinua::fun_set_elementi_comuni() {
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

    //Dati in comune;
    QLabel* title= new QLabel(tr("Titolo:"));
    dati->addWidget(title);
    dati->addWidget(titolo);

    QLabel* edition= new QLabel(tr("Editore:"));
    dati->addWidget(edition);
    dati->addWidget(editore);

    QLabel* dpubb= new QLabel(tr("Data di pubblicazione:"));
    dati->addWidget(dpubb);
    dati->addWidget(pubblicazione);

    QLabel* tip= new QLabel(tr("Tipologia del prodotto:"));
    dati->addWidget(tip);
    dati->addWidget(tipologia);
}

void FormContinua::prosegui() {
    QString tit = titolo->text();
    QString edit = editore->text();
    QDate pubb = pubblicazione->date();

    nuovaForm = new FillForm(prod, tit, edit, pubb,
                             tipologia->currentIndex(), this);
    connect(nuovaForm, SIGNAL(send()), this, SIGNAL(send()));
    connect(nuovaForm, SIGNAL(send()), this, SLOT(close()));
    nuovaForm->show();
}
