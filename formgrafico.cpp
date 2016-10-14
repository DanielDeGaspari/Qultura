#include "formgrafico.h"
#include <QPainter>
#include "glinea.h"
#include "gistogramma.h"
#include <typeinfo>

formGrafico::formGrafico(Ordine* o, QWidget *parent) :  QDialog(parent), ord(o), graph(0), dati(0) {
    this->setWindowTitle("Grafico vendite per categoria di prodotti");
    QDialog::reject();
    this->resize(800,400);
    this->setMinimumHeight(350);
    this->setMinimumWidth(700);
}

formGrafico::~formGrafico(){
    if (graph)
        delete graph;
    if (dati)
        delete dati;
}

void formGrafico::setOrigine(const QPointF& o){
    origine=o;
}

void formGrafico::setestremoX(const QPointF& x){
    estremoX=x;
}

void formGrafico::setestremoY(const QPointF& y){
    estremoY=y;
}

void formGrafico::inizializza() {
    //dimensioni della finistra;
    QSize dim = this->size();
    setestremoX(QPointF(dim.width()-100,dim.height()-50));
    setestremoY(QPointF(50,20));
    setOrigine(QPointF(50,dim.height()-50));
}

void formGrafico::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,5));
    inizializza();
    QLineF assex(estremoX, origine);
    QLineF assey(origine, estremoY);

    painter.drawLine(assex);
    painter.drawLine(assey);
    painter.drawText(origine.x()-10, origine.y() +15, "O");
    painter.drawText(estremoX.x()+10, estremoX.y() +15, "X (tipologia)");
    painter.drawText(estremoY.x()-15, estremoY.y() -5, "Y (incasso in €)");

    if (graph && ord->Size())
        graph->disegna(painter);

    //legenda grafico:
    painter.setPen(QPen(Qt::black,3));
    QRect legenda(size().width()-180,1,178,140);
    painter.drawRect(legenda);
    //campi:
        painter.drawText(legenda.x()+5,legenda.y()+20,"Legenda:");
        painter.drawText(legenda.x()+5,legenda.y()+45,"LC = Libri cartacei");
        painter.drawText(legenda.x()+5,legenda.y()+65,"EB = Ebook");
        painter.drawText(legenda.x()+5,legenda.y()+85,"RC = Riviste cartacee");
        painter.drawText(legenda.x()+5,legenda.y()+105,"RDOM = Riviste domiciliate");
        painter.drawText(legenda.x()+5,legenda.y()+125,"RDIG = Riviste digitali");
}

void formGrafico::resizeEvent(QResizeEvent *) {
    inizializza();

    if (typeid(gIstogramma) == typeid(*graph))  //se il grafico e' un istogramma
        disegnaIstogramma();
    else
        if (typeid(GLinea) == typeid(*graph))  //se il grafico e' un grafico linea
        disegnaLinea();
}

void formGrafico::disegnaLinea() {
    if (graph)
        delete graph;
    if (dati)
        delete dati;
    dati = new DatiGrafico(*ord);
    graph = new GLinea(dati,this->size(),origine);
}

void formGrafico::disegnaIstogramma() {
    if (graph)
        delete graph;
    if (dati)
        delete dati;
    dati = new DatiGrafico(*ord);
    graph = new gIstogramma(dati,this->size(),origine);
}
