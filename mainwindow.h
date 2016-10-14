#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QCloseEvent>

#include <QMenu>
#include <QToolBar>
#include <QFile>

#include "tabella.h"
#include "formcontinua.h"
#include "formgrafico.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
 private:
    /* menu in alto*/
    QMenu* FileMenu;
        QAction* Apri;
        QAction* Salva;
        QAction* SalvaCome;
        QAction* Chiudi;
        QAction* Esci;

    QMenu* ModificaMenu;
        QAction* Aggiungi;
        QAction* Rimuovi;
        QAction* Rimuovi_tutte;

    QMenu* VisualizzaMenu;
        QAction* MostraInfoAggiuntive;
        QAction* NascondiInfoAggiuntive;
        QAction* Istogramma;
        QAction* Linea;

    /* menu secondario */
    QToolBar* File;

    QToolBar* Modifica;

    QToolBar* Visualizza;

    /* Sezione principale */
    Tabella* section;

    void ParseXML(QString, Ordine&);
    void StoreXML(QFile&);
    bool checkModifiche();
    void closeEvent(QCloseEvent*);

    Ordine ord;
    Prodotto* prod;
    QString nomeFileAperto;

    FormContinua* form;
    formGrafico* formGraph;

 public:
    MainWindow(QWidget *parent = 0);

 private slots:
    void apri();
    void store();
    void storeAs();
    void chiudi();
    void mostraTutto();
    void nascondi();
    void aggiungiDato();
    void aggiungiNuovo();
    void graficoLinea();
    void graficoIstogramma();
};

#endif // MYWIDGET_H
