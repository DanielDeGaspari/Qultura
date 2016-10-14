#include "datigrafico.h"
#include "rivistacartacea.h"
#include "rivistadigitale.h"
#include "rivistadomiciliata.h"
#include "librocartaceo.h"
#include "ebook.h"
#include <typeinfo>

DatiGrafico::DatiGrafico(const Ordine& ord) {
    double sumRivCar=0;
    double sumRivDom=0;
    double sumRivDig=0;
    double sumLibCar=0;
    double sumEbook=0;

    for (Ordine::const_iterator cit = ord.cbegin(); cit != ord.cend(); ++cit ) {
        if (typeid(RivistaCartacea) == typeid(**cit)){
            sumRivCar+=(*cit)->prezzo();
        }
        else
        if (typeid(RivistaDomiciliata) == typeid(**cit)){
            sumRivDom+=(*cit)->prezzo();
        }
        else
        if (typeid(RivistaDigitale) == typeid(**cit)){
            sumRivDig+=(*cit)->prezzo();
        }
        else
        if (typeid(LibroCartaceo) == typeid(**cit)){
            sumLibCar+=(*cit)->prezzo();
        }
        else
        if (typeid(Ebook) == typeid(**cit)){
            sumEbook+=(*cit)->prezzo();
        }
    }

    value.push_back(sumLibCar);
    value.push_back(sumEbook);
    value.push_back(sumRivCar);
    value.push_back(sumRivDom);
    value.push_back(sumRivDig);
}

double DatiGrafico::getMax() const {
    double max=0;
    QVector<double>::ConstIterator cit = value.begin();
    for (; cit!=value.end(); ++cit) {
        if (max < *cit)
            max = *cit;
    }
    return max;
}

QVector<const QPointF*> DatiGrafico::punti(const QSize& dim, const QPointF& origine) const {
    QVector<const QPointF*> aux;

    int next=0;
    QPointF* punto;
    double max=getMax();
    if (!max)
        max = 1;

    QVector<double>::ConstIterator cit = value.begin();
    for (; cit != value.end(); ++cit) {
        punto = new QPointF(origine.x() + next, origine.y() - ((dim.height() -100)*(*cit))/max);
        next+=100;
        aux.push_back(punto);
    }
    return aux;
}

double DatiGrafico::operator [](int i) const {
    return value[i];
}
