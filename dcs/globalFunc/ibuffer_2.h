#ifndef IBUFFER_2_H
#define IBUFFER_2_H
#include <QList>
template <typename T> class IBuffers
{
public:
    IBuffers(int sizeBuffer=4)
    {
        setSizeBuffers(sizeBuffer);
    }

    //! добавить данные в начало
    void push(T data)
    {
        //BufferDATA<T> *ptr=buffer[i];
    }

    //! добавление элемента в указанный массив
    void insert(int i,T value)
    {
        buffers[i]->value=value;
    }
    //! задать размер массива
    void setSizeBuffers(int size)
    {
        buffers.resize(size);
        //    buffers.push_back(new Buffer<T>);
    }

    /*
    //! даннеы самые свежие
    T top();
    //! указатель на верхушку данных
    T* top();


    const double * operator [] ( int i ) const;
*/

private:
    //! буфер
    QVector<Buffer<T>* > buffers;
    //! корень всех элементов
    BufferDATA<T> *root;
};

#endif // IBUFFER_2_H
