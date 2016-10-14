#ifndef MYITERATOR
#define MYITERATOR

class Ordine;

template <class T>
class MyIterator {
 friend class Ordine;
 private:
    T *punt;
 public:
    bool operator==(const MyIterator&) const;
    bool operator!=(const MyIterator&) const;
    MyIterator& operator++();   //prefisso
    MyIterator operator++(int); //postfisso
    T& operator*() const;
};

template <class T>
bool MyIterator<T>::operator ==(const MyIterator<T>& i) const {
    return punt == i.punt;
}

template <class T>
bool MyIterator<T>::operator !=(const MyIterator<T> &i) const {
    return punt != i.punt;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator ++() {
    punt++;
    return *this;
}

template <class T>
MyIterator<T> MyIterator<T>::operator ++(int) {
    MyIterator<T> aux = *this;
    punt++;
    return aux;
}

template <class T>
T& MyIterator<T>::operator *() const {
    return *punt;
}

#endif // MYITERATOR
