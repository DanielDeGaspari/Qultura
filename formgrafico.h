#ifndef FORMGRAFICO_H
#define FORMGRAFICO_H

#include <QDialog>
#include <QPoint>
#include "ordine.h"
#include "grafico.h"
#include "datigrafico.h"

class formGrafico : public QDialog {
    Q_OBJECT
 private:
    Ordine* ord;
    Grafico* graph;
    DatiGrafico* dati;

    QPointF origine;
    QPointF estremoX;
    QPointF estremoY;

    void setOrigine(const QPointF&);
    void setestremoX(const QPointF&);
    void setestremoY(const QPointF&);
    void inizializza();
 protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
 public:
    formGrafico(Ordine* o, QWidget *parent=0);

    ~formGrafico();
 public slots:
    void disegnaLinea();
    void disegnaIstogramma();
};
#endif // formGrafico_H
