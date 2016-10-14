#ifndef TABELLA_H
#define TABELLA_H

#include <QTableWidget>
#include "ordine.h"
#include "riga.h"

class Tabella : public QTableWidget {
    Q_OBJECT
 public:
    Tabella(Ordine& o , QWidget* parent=0 );

    void load();
 private:
    Ordine& ord;

 public slots:
    void aggiungi(Prodotto* p=new LibroCartaceo());
    void rimuovi();
    void rimuovi_tutte();
    void showAll();
    void hideAll();
};

#endif // TABELLA_H
