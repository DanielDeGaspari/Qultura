#include "gistogramma.h"
#include <QRect>

gIstogramma::gIstogramma(const DatiGrafico* dati,  const QSize& dim, const QPointF& orig)
    : Grafico(dati,dim,orig) {}

void gIstogramma::disegna(QPainter& painter) const {
    painter.setPen(QPen(Qt::black, 3));

    //Disegno il segmento;
    QVector<const QPointF*>::ConstIterator cit = punti.begin();
    for (; cit != punti.end() ; ++cit) {
        int altezzaR = origine.y() - (*cit)->y();
        QRectF rettangolo((*cit)->x()+3, origine.y(), 50,  - altezzaR);    //x,y,width,height
        painter.drawRect(rettangolo);
        painter.fillRect(rettangolo,QBrush(Qt::lightGray));
    }

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
