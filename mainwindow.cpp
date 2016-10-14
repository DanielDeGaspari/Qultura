#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <typeinfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), nomeFileAperto("") {
    /* Configurazioni della finestra; */
    setWindowTitle(tr("Qultura"));
    setWindowIcon(QIcon(":/images/logo.png"));
    setGeometry(200,150,1000,500);

    /* Configurazione section */
    section = new Tabella(ord,this);
    setCentralWidget(section);

    /* Configurazione del menu in alto: */
    FileMenu = new QMenu(tr("File"), this);
    ModificaMenu = new QMenu(tr("Modifica"), this);
    VisualizzaMenu = new QMenu(tr("Visualizza"), this);

    menuBar()->addMenu(FileMenu);
    menuBar()->addMenu(ModificaMenu);
    menuBar()->addMenu(VisualizzaMenu);

        //Apri
        Apri = new QAction(QIcon(":/images/apri.png"),tr("Apri ..."),this);
        FileMenu->addAction(Apri);
        connect(Apri,SIGNAL(triggered()),this, SLOT(apri()));
        Apri->setShortcut(QKeySequence::Open);

        //Salva
        Salva = new QAction(QIcon(":/images/salva.png"),tr("Salva"),this);
        FileMenu->addAction(Salva);
        connect(Salva, SIGNAL(triggered()),this,SLOT(store()));
        Salva->setShortcut(QKeySequence::Save);

        //Salva con nome
        SalvaCome = new QAction(QIcon(":/images/salvaCome.png"),tr("Salva con nome ..."),this);
        FileMenu->addAction(SalvaCome);
        connect(SalvaCome, SIGNAL(triggered(bool)), this, SLOT(storeAs()));
        SalvaCome->setShortcut(QKeySequence::SaveAs);

        //Chiudi file
        Chiudi = new QAction(QIcon(":/images/chiudi.png"),tr("Chiudi file corrente"),this);
        FileMenu->addAction(Chiudi);
        connect(Chiudi, SIGNAL(triggered(bool)), this, SLOT(chiudi()));
        Chiudi->setShortcut(QKeySequence::Close);

        //Esci
        Esci = new QAction(QIcon(":/images/esci.png"),tr("Esci"), this);
        FileMenu->addAction(Esci);
        connect(Esci, SIGNAL(triggered()), this, SLOT(close()));
        Esci->setShortcut(QKeySequence::Quit);

        //Aggiungi riga
        Aggiungi = new QAction(QIcon(":/images/aggiungi.png"),tr("Aggiungi elemento"),this);
        ModificaMenu->addAction(Aggiungi);
        connect(Aggiungi, SIGNAL(triggered(bool)), this, SLOT(aggiungiDato()));

        //Rimuovi riga
        Rimuovi = new QAction(QIcon(":/images/rimuovi.png"),tr("Rimuovi elemento"),this);
        ModificaMenu->addAction(Rimuovi);
        connect(Rimuovi, SIGNAL(triggered()), section, SLOT(rimuovi()));

        //Rimuovi tutte le righe
        Rimuovi_tutte = new QAction(QIcon(":/images/rimuovi_tutte.png"),tr("Rimuovi tutti gli elementi"),this);
        ModificaMenu->addAction(Rimuovi_tutte);
        connect(Rimuovi_tutte, SIGNAL(triggered()), section, SLOT(rimuovi_tutte()));

        //Visualizza tabella completa
        MostraInfoAggiuntive = new QAction(QIcon(":/images/showmore.png"), tr("Mostra informazioni complete"), this);
        VisualizzaMenu->addAction(MostraInfoAggiuntive);
        connect(MostraInfoAggiuntive, SIGNAL(triggered(bool)), section, SLOT(showAll()));

        //Non visualizzare tabella completa
        NascondiInfoAggiuntive = new QAction(QIcon(":/images/hide.png"), tr("Nascondi informazioni complete"), this);
        VisualizzaMenu->addAction(NascondiInfoAggiuntive);
        connect(NascondiInfoAggiuntive, SIGNAL(triggered(bool)), section, SLOT(hideAll()));
        NascondiInfoAggiuntive->setEnabled(false);

        //Visualizza grafico(istogramma)
        Istogramma = new QAction(QIcon(":/images/istogramma.png"), tr("Visualizza istogramma"), this);
        VisualizzaMenu->addAction(Istogramma);
        connect(Istogramma, SIGNAL(triggered(bool)), this, SLOT(graficoIstogramma()));

        //Visualizza grafico(linea)
        Linea = new QAction(QIcon(":/images/linea.png"), tr("Visualizza grafico linea"), this);
        VisualizzaMenu->addAction(Linea);
        connect(Linea, SIGNAL(triggered(bool)), this, SLOT(graficoLinea()));


    /* Configurazione del menu secondario: */
    statusBar();
    File = addToolBar(tr("File"));
    Modifica = addToolBar(tr("Modifica"));
    Visualizza = addToolBar(tr("Visualizza"));

        //Salva
        File->addAction(Salva);
        //Apri
        File->addAction(Apri);
        //Chiudi file
        File->addAction(Chiudi);

        //Aggiungi riga
        Modifica->addAction(Aggiungi);
        //Rimuovi riga
        Modifica->addAction(Rimuovi);
        Modifica->addAction(Rimuovi_tutte);

        //Visualizza tabella completa
        Visualizza->addAction(MostraInfoAggiuntive);
        Visualizza->addAction(NascondiInfoAggiuntive);
        Visualizza->addAction(Istogramma);
        Visualizza->addAction(Linea);

        connect(MostraInfoAggiuntive,SIGNAL(triggered(bool)), this, SLOT(mostraTutto()));
        connect(NascondiInfoAggiuntive, SIGNAL(triggered(bool)), this, SLOT(nascondi()));
}

/* Definizione degli SLOT */

void MainWindow::apri() {
    QString filename = QFileDialog::getOpenFileName(this,
                               tr("Apri"), QDir::currentPath(), tr("xml files (*.xml)"));

    if (!filename.isEmpty()) {
        if (!nomeFileAperto.isEmpty()) {  //c'è un file aperto;
            QMessageBox::StandardButtons reply;
            reply = QMessageBox::question(this,"Attenzione","E' presente un file già aperto. Chiuderlo?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                chiudi();
                ParseXML(filename,ord);
                nomeFileAperto=filename;
                section->load();
            }
            else
                return;
        }
        else { //se ho aggiunto elementi su una finestra senza avere file aperti
            if (ord.Size()) {
                QMessageBox::StandardButtons reply;
                reply = QMessageBox::question(this,"Attenzione","Le modifiche non salvate andranno perse. Si desidera salvare il file corrente?", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    store();
                }
            }
        }

        section->rimuovi_tutte();
        ParseXML(filename,ord);
        section->load();
        nomeFileAperto=filename;
    }
}

void MainWindow::ParseXML(QString filename, Ordine& o) {
    QFile file(filename);

    if (file.open(QFile::ReadOnly)) {
        QXmlStreamReader read;
        read.setDevice(&file);

        //Preparo le variabili che userò;

        //Elementi in comune;
        QString titolo;
        QString editore;
        QDate pubblicazione;

        //Elementi di rivista;
        QString categoria;

        //Elementi di rivista cartacea;
        int n_pagine; //presente anche su libro
        double cpp; //presente anche su libro cartaceo

        //Elementi di rivista digitale;
        double cpKB; //presente anche su ebook
        int dimensione; //presente anche su ebook

        //Elementi di rivista domiciliata;
        double maggiorazione;

        //Elementi di Libro
        QString genere;
        QString autore;
        QString ISBN;
        int edizione;

        //lettura dal file: leggi finchè non arrivi all' eof e non incontri errori.
        while (!read.atEnd() && !read.hasError()) {

            if (read.isStartElement()) {
                QString name = read.name().toString();
                if (name == "LibroCartaceo") {
                    titolo="";
                    editore="";
                    pubblicazione=QDate::currentDate();
                    n_pagine=0;
                    cpp=0;
                    genere="";
                    autore="";
                    ISBN="";
                    edizione=1;

                    while (!read.isEndElement()) {
                        name = read.name().toString();
                        if ( name == "Titolo" ) {
                            titolo = read.readElementText();
                        }
                        else if ( name == "Editore" ) {
                            editore = read.readElementText();
                        }
                        else if ( name == "Pubblicazione" ) {
                            QString temp=read.readElementText();
                            pubblicazione= QDate::fromString(temp,"dd.MM.yyyy");
                        }
                        else if ( name == "Autore" ) {
                            autore = read.readElementText();
                        }
                        else if ( name == "ISBN" ) {
                            ISBN= read.readElementText();
                        }
                        else if ( name == "Edizione" ) {
                            edizione = read.readElementText().toInt();
                        }
                        else if ( name == "Genere" ) {
                            genere = read.readElementText();
                        }
                        else if ( name == "NumeroPagine" ) {
                            n_pagine = read.readElementText().toInt();
                        }
                        else if ( name == "CostoPerPagina" ) {
                            cpp = read.readElementText().toDouble();
                        }

                    read.readNext();
                    }

                    LibroCartaceo* lc = new LibroCartaceo(titolo,editore,pubblicazione,autore,ISBN,edizione,genere,n_pagine,cpp);
                    o.Aggiungi_prodotto(*lc);
                }

                else
                if (name == "Ebook") {
                    titolo="";
                    editore="";
                    pubblicazione=QDate::currentDate();
                    n_pagine=0;
                    cpKB=0;
                    dimensione=0;
                    genere="";
                    autore="";
                    ISBN="";
                    edizione=1;

                    while (!read.isEndElement()) {
                        name = read.name().toString();
                        if ( name == "Titolo" ) {
                            titolo = read.readElementText();
                        }
                        else if ( name == "Editore" ) {
                            editore = read.readElementText();
                        }
                        else if ( name == "Pubblicazione" ) {
                            QString temp=read.readElementText();
                            pubblicazione= QDate::fromString(temp,"dd.MM.yyyy");
                        }
                        else if ( name == "Autore" ) {
                            autore = read.readElementText();
                        }
                        else if ( name == "ISBN" ) {
                            ISBN= read.readElementText();
                        }
                        else if ( name == "Edizione" ) {
                            edizione = read.readElementText().toInt();
                        }
                        else if ( name == "Genere" ) {
                            genere = read.readElementText();
                        }
                        else if ( name == "NumeroPagine" ) {
                            n_pagine = read.readElementText().toInt();
                        }
                        else if ( name == "CostoPerByte" ) {
                            cpKB = read.readElementText().toDouble();
                        }
                        else if ( name == "Dimensione" ) {
                            dimensione = read.readElementText().toInt();
                        }
                    read.readNext();
                    }

                    Ebook* eb = new Ebook(titolo,editore,pubblicazione,autore,ISBN,edizione,genere,n_pagine,cpKB,dimensione);
                    o.Aggiungi_prodotto(*eb);
                }
                else
                if (name == "RivistaCartacea") {
                    titolo="";
                    editore="";
                    pubblicazione=QDate::currentDate();
                    n_pagine=0;
                    cpp=0;
                    categoria="";

                    while (!read.isEndElement()) {
                        name = read.name().toString();
                        if ( name == "Titolo" ) {
                            titolo = read.readElementText();
                        }
                        else if ( name == "Editore" ) {
                            editore = read.readElementText();
                        }
                        else if ( name == "Pubblicazione" ) {
                            QString temp=read.readElementText();
                            pubblicazione= QDate::fromString(temp,"dd.MM.yyyy");
                        }
                        else if ( name == "Categoria" ) {
                            categoria = read.readElementText();
                        }
                        else if ( name == "NumeroPagine" ) {
                            n_pagine = read.readElementText().toInt();
                        }
                        else if ( name == "CostoPerPagina" ) {
                            cpp = read.readElementText().toDouble();
                        }
                    read.readNext();
                    }

                    RivistaCartacea* rc = new RivistaCartacea(titolo,editore,pubblicazione,categoria,n_pagine,cpp);
                    o.Aggiungi_prodotto(*rc);
                 }
                 else
                 if (name == "RivistaDomiciliata") {
                    titolo="";
                    editore="";
                    pubblicazione=QDate::currentDate();
                    n_pagine=0;
                    cpp=0;
                    categoria="";
                    maggiorazione=0;

                    while (!read.isEndElement()) {
                        name = read.name().toString();
                        if ( name == "Titolo" ) {
                            titolo = read.readElementText();
                        }
                        else if ( name == "Editore" ) {
                            editore = read.readElementText();
                        }
                        else if ( name == "Pubblicazione" ) {
                            QString temp=read.readElementText();
                            pubblicazione= QDate::fromString(temp,"dd.MM.yyyy");
                        }
                        else if ( name == "Categoria" ) {
                            categoria = read.readElementText();
                        }
                        else if ( name == "NumeroPagine" ) {
                            n_pagine = read.readElementText().toInt();
                        }
                        else if ( name == "CostoPerPagina" ) {
                            cpp = read.readElementText().toDouble();
                        }
                        else if (name == "Maggiorazione") {
                            maggiorazione = read.readElementText().toDouble();
                        }
                    read.readNext();
                    }

                        RivistaDomiciliata* rd = new RivistaDomiciliata(titolo,editore,pubblicazione,categoria,n_pagine,cpp,maggiorazione);
                        o.Aggiungi_prodotto(*rd);
                }
                else
                if (name == "RivistaDigitale") {
                    titolo="";
                    editore="";
                    pubblicazione=QDate::currentDate();
                    cpKB=0;
                    dimensione=0;
                    categoria="";

                    while (!read.isEndElement()) {
                        name = read.name().toString();
                        if ( name == "Titolo" ) {
                            titolo = read.readElementText();
                        }
                        else if ( name == "Editore" ) {
                            editore = read.readElementText();
                        }
                        else if ( name == "Pubblicazione" ) {
                            QString temp=read.readElementText();
                            pubblicazione= QDate::fromString(temp,"dd.MM.yyyy");
                        }
                        else if ( name == "Categoria" ) {
                            categoria = read.readElementText();
                        }
                        else if ( name == "CostoPerByte" ) {
                            cpKB = read.readElementText().toDouble();
                        }
                        else if (name == "Dimensione") {
                            dimensione = read.readElementText().toInt();
                        }
                    read.readNext();
                    }

                    RivistaDigitale* rd = new RivistaDigitale(titolo,editore,pubblicazione,categoria,cpKB,dimensione);
                    o.Aggiungi_prodotto(*rd);
                }
            }
        read.readNext();
        } // fine while;
        if (read.hasError()) {
            QMessageBox::warning(0,"Errore!","Attenzione! è stato riscontrato un'errore nell'apertura del file. Si prega di riprovare.");
            nomeFileAperto="";
        }

        file.close();
}
}

void MainWindow::store() {

    if (nomeFileAperto.isEmpty()) {
        storeAs();
        return;
    }
    QFile file(nomeFileAperto);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0,"Errore!","Errore nell'apertura del file; impossibile salvare il file.");
    }
    else {
        StoreXML(file);
        file.close();
    }
}

void MainWindow::StoreXML(QFile& file) {
    QXmlStreamWriter write;
    write.setDevice(&file);
    //Il documento inizia con la versione XML usata.
    write.writeStartDocument();
    //Il documento sarà identato automaticamente;
    write.setAutoFormatting(true);
    //root del documento;
    write.writeStartElement("Prodotto");

    for(Ordine::const_iterator it = ord.cbegin(); it !=ord.cend(); ++it) {
        //Prendo il prodotto;
        const Prodotto* prod= ord[it];

        if (typeid(RivistaCartacea) == typeid(*prod)){  //se il prodotto è un una rivistaCartacea;
          const RivistaCartacea* rc = static_cast<const RivistaCartacea*>(prod);
            write.writeStartElement("RivistaCartacea");
                //writeTextElement gestisce apertura e chiusura del tag + inserimento del contenuto;
                write.writeTextElement("Titolo",rc->getTitolo());
                write.writeTextElement("Editore",rc->getEditore());
                write.writeTextElement("Pubblicazione",rc->getPubblicazione().toString("dd.MM.yyyy"));
                write.writeTextElement("Categoria",rc->getCategoria());
                write.writeTextElement("NumeroPagine",QString::number(rc->getN_pagine()));
                write.writeTextElement("CostoPerPagina",QString::number(rc->getCpp()));
            write.writeEndElement();
        }
        else
            if (typeid(RivistaDomiciliata) == typeid(*prod)){  //se il prodotto è un una rivistaDomiciliata;
              const RivistaDomiciliata* rd = static_cast<const RivistaDomiciliata*>(prod);
              write.writeStartElement("RivistaDomiciliata");
                  write.writeTextElement("Titolo",rd->getTitolo());
                  write.writeTextElement("Editore",rd->getEditore());
                  write.writeTextElement("Pubblicazione",rd->getPubblicazione().toString("dd.MM.yyyy"));
                  write.writeTextElement("Categoria",rd->getCategoria());
                  write.writeTextElement("NumeroPagine",QString::number(rd->getN_pagine()));
                  write.writeTextElement("CostoPerPagina",QString::number(rd->getCpp()));
                  write.writeTextElement("Maggiorazione",QString::number(rd->getMaggiorazione()));
              write.writeEndElement();
          }
      else
            if (typeid(RivistaDigitale) == typeid(*prod)){  //se il prodotto è un una rivistaDigitale;
            const RivistaDigitale* rd = static_cast<const RivistaDigitale*>(prod);
              write.writeStartElement("RivistaDigitale");
                  write.writeTextElement("Titolo",rd->getTitolo());
                  write.writeTextElement("Editore",rd->getEditore());
                  write.writeTextElement("Pubblicazione",rd->getPubblicazione().toString("dd.MM.yyyy"));
                  write.writeTextElement("Categoria",rd->getCategoria());
                  write.writeTextElement("CostoPerByte",QString::number(rd->getCpKB()));
                  write.writeTextElement("Dimensione",QString::number(rd->getDimensione()));
              write.writeEndElement();
          }
      else
            if (typeid(LibroCartaceo) == typeid(*prod)){  //se il prodotto è un una libroCartaceo;
            const LibroCartaceo* lc = static_cast<const LibroCartaceo*>(prod);
              write.writeStartElement("LibroCartaceo");
                  write.writeTextElement("Titolo",lc->getTitolo());
                  write.writeTextElement("Editore",lc->getEditore());
                  write.writeTextElement("Pubblicazione",lc->getPubblicazione().toString("dd.MM.yyyy"));
                  write.writeTextElement("Autore",lc->getAutore());
                  write.writeTextElement("ISBN",lc->getISBN());
                  write.writeTextElement("Edizione",QString::number(lc->getEdizione()));
                  write.writeTextElement("Genere",lc->getGenere());
                  write.writeTextElement("NumeroPagine",QString::number(lc->getN_pagine()));
                  write.writeTextElement("CostoPerPagina",QString::number(lc->getCpp()));
              write.writeEndElement();
          }
      else
            if (typeid(Ebook) == typeid(*prod)){  //se il prodotto è un Ebook;
            const Ebook* eb = static_cast<const Ebook*>(prod);
              write.writeStartElement("Ebook");
                  write.writeTextElement("Titolo",eb->getTitolo());
                  write.writeTextElement("Editore",eb->getEditore());
                  write.writeTextElement("Pubblicazione",eb->getPubblicazione().toString("dd.MM.yyyy"));
                  write.writeTextElement("Autore",eb->getAutore());
                  write.writeTextElement("ISBN",eb->getISBN());
                  write.writeTextElement("Edizione",QString::number(eb->getEdizione()));
                  write.writeTextElement("Genere",eb->getGenere());
                  write.writeTextElement("NumeroPagine",QString::number(eb->getN_pagine()));
                  write.writeTextElement("CostoPerByte",QString::number(eb->getCpKB()));
                  write.writeTextElement("Dimensione",QString::number(eb->getDimensione()));
              write.writeEndElement();
          }
  }
  write.writeEndElement();
  write.writeEndDocument();

  if (!write.hasError()) {
      QMessageBox::information(this,"Messaggio","I dati sono stati salvati con successo");
  }
  else {
      QMessageBox::warning(this,"Attenzione","I dati non sono stati memorizzati correttamente; Riprovare");
  }
}

void MainWindow::storeAs() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), tr("xml files (*.xml)")) + ".xml";

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0,"Errore!","Errore nell'apertura del file; impossibile salvare il file.");
    }
    else {
        StoreXML(file);
        nomeFileAperto=filename;
        file.close();
    }
}

void MainWindow::chiudi() {
    if (!nomeFileAperto.isEmpty()) {
        checkModifiche();
    }
    else
        QMessageBox::information(this,tr("Attenzione"),tr("Al momento non è aperto nessun file"),QMessageBox::Close);
}

void MainWindow::nascondi() {
    NascondiInfoAggiuntive->setEnabled(false);
    MostraInfoAggiuntive->setEnabled(true);
}

void MainWindow::mostraTutto() {
    MostraInfoAggiuntive->setEnabled(false);
    NascondiInfoAggiuntive->setEnabled(true);
}

void MainWindow::aggiungiDato() {
    form = new FormContinua(prod, this);
    connect(form, SIGNAL(send()), this, SLOT(aggiungiNuovo()));
    form->show();
}

void MainWindow::aggiungiNuovo() {
    section->aggiungi(prod);
    section->resizeColumnsToContents();
}

bool MainWindow::checkModifiche() {
    Ordine vecchio;
    bool ok = true;
    ParseXML(nomeFileAperto,vecchio);
    if (ord != vecchio) {
        QMessageBox attenzione;
        attenzione.setText(tr("Il file ha subito modifiche."));
        attenzione.setInformativeText(tr("Salvare le modifiche?"));
        attenzione.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        attenzione.setDefaultButton(QMessageBox::Save);
        attenzione.button(QMessageBox::Save)->setText(tr("Salva"));
        attenzione.button(QMessageBox::Discard)->setText(tr("Non salvare"));
        attenzione.button(QMessageBox::Cancel)->setText(tr("Annulla"));
        int scelta = attenzione.exec();
        switch ( scelta ) {
        case QMessageBox::Save :
            store();
            section->rimuovi_tutte();
            nomeFileAperto="";
            break;
        case QMessageBox::Discard :
            section->rimuovi_tutte();
            nomeFileAperto="";
            break;
        case QMessageBox::Cancel :
            ok=false;
            break;
        }
    }
    else {
        section->rimuovi_tutte();
        nomeFileAperto="";
    }
return ok;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    bool chiudi = checkModifiche();
    if (!chiudi)
        event->ignore();
}

void MainWindow::graficoIstogramma() {
    formGraph = new formGrafico(&ord, this);
    formGraph->disegnaIstogramma();
    formGraph->show();
}

void MainWindow::graficoLinea() {
    formGraph = new formGrafico(&ord, this);
    formGraph->disegnaLinea();
    formGraph->show();
}
