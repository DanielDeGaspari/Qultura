#include "glinea.h"
#include <QVector>
#include <QPointF>

GLinea::GLinea(const DatiGrafico* dati, const QSize& dim, const QPointF& origine)
    : Grafico(dati,dim,origine) {}

void GLinea::disegna(QPainter& painter) const {
    //Disegno il segmento;
    QVector<const QPointF*>::ConstIterator cit = punti.begin();
    for (; cit != punti.end()-1; ++cit) {
        painter.setPen(QPen(Qt::black, 3));
        QLineF segmento(**cit, **(cit+1));
        painter.drawLine(segmento);
        painter.setPen(QPen(Qt::red,7));
        painter.drawPoint(**cit);
    }
    //evidenzio l'ultimo punto;
    painter.drawPoint(**cit);

    painter.setPen(QPen(Qt::black, 3));

    //Scrivo i dati sull'asse delle ascisse;
        painter.drawText(punti[0]->x()+10, origine.y()+20, "LC");
        painter.drawText(punti[1]->x()+10, origine.y()+20, "EB");
        painter.drawText(punti[2]->x()+10, origine.y()+20, "RC");
        painter.drawText(punti[3]->x()+10, origine.y()+20, "RDOM");
        painter.drawText(punti[4]->x()+10, origine.y()+20, "RDIG");

    //scrivo i dati sull'asse delle ordinate;
        for (int i=0; i<punti.size(); i++) {
            painter.drawText(origine.x()-40, punti[i]->y()-2, QString::number((*dg)[i]));
            painter.drawLine(QPoint(origine.x()-10,punti[i]->y()),QPoint(origine.x(),punti[i]->y()));
        }
}
