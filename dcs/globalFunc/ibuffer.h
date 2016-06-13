#ifndef IBUFFER_H
#define IBUFFER_H

#include <QVector>

//! тип данных должен поддерживать операцию глубокого копирования
template <typename T> struct BufferDATA
{
public:
    BufferDATA()
    {
        next=0;
        prev=0;
        index=0;
    }
    BufferDATA(BufferDATA *prevous)
    {
        index=0;
        next=0;
        prev=prevous;
        prev->next=this;
    }
    //! заменить значение
    //! следующий элемент
    BufferDATA<T> *next;
    //! предыдущий элемент
    BufferDATA<T> *prev;
    //! значение текущего элемента

    //T value;
    union
    {
//        T value;//нужно расскоментировать
        double masDouble[sizeof(T)/8];
        //double masInt[sizeof(T)/4];
    };
    //Tunion un;
    //! текущий индекс
    int index;
};
//! верхний уровень
template <typename T> class Buffer
{
public:
    Buffer<T>()
    {
        current_=0;
        value_=0;
    }
    //! задать текущий элемент
    void setCurrent(BufferDATA<T> *ptr)
    {
        current_=ptr;
//        value_=&(ptr->value);//нужно расскомментировать
    }
    //! текущий элемент
    BufferDATA<T> *current()
    {
        return current_;
    }
    //! значение текущего элемента
    T* value(){return value_;}
    T valueCopy(){return *value_;}
    //void setValue();
    //! копирование значения
    void copyValue(T* ptr)
    {
        *value_=*ptr;
    }
private:
    //! указатель на текущий элемент
    BufferDATA<T> *current_;
    //! значение хранящееся в текущем элементе
    T *value_;
};
//! класс
template <typename T> class IBuffers
{
public:
    IBuffers<T>(int sizeBuffer=4)
    {
        root=0;
        setSizeBuffers(sizeBuffer);
    }
    //! добавить новые данные(по значению)
    void push(T data)
    {
        push(&data);
    }
    //! добавить новые данные(по указателю)
    void push(T *data)
    {
        if(buffers.size()!=0)
        {
            int temp=buffers.size()-1;

            buffers[temp-1]->current()->next=0;
            buffers[temp]->current()->prev=0;
            buffers[temp]->current()->next=buffers[0]->current();
            buffers[0]->current()->prev=buffers[temp]->current();

            buffers[temp]->current()->prev=0;

            root=buffers[temp]->current();

            //! рекомбинация элементов
            recombine();
            //! копирование элемента
            buffers[0]->copyValue(data);
        }
    }
    //! добавление элемента в указанный массив
    void insert(int i,T value)
    {
        buffers[i]->copyValue(&value);
    }
    //! задать размер массива
    void setSizeBuffers(int size)
    {
        int i=0;
        buffers.clear();
        for(i=0;i<size;i++) buffers.push_back(new Buffer<T>);

        i=0;

        root=new BufferDATA<T>;
        BufferDATA<T>* temp=root;
        buffers[0]->setCurrent(temp);
        do
        {
            i++;
            temp=new BufferDATA<T>(temp);
            buffers[i]->setCurrent(temp);
        }while(i<(size-1));
    }
    //! вернуть буфер на i буфер
    Buffer<T>* buf(int i)
    {
        return buffers[i];
    }
    //! вернуть буфер на i буфер
    Buffer<T>* operator [] ( int i ) const
    {
        return buffers[i];
    }
    //! указатель на верхушку данных
    T* top()
    {
        return buffers[0]->value;
    }
private:
    //! рекомбинация элементов
    void recombine()
    {
        int i=0;

        BufferDATA<T> *temp=root;

        if(buffers.size()==0) return;

        buffers[0]->setCurrent(root);
        do
        {
            i++;
            temp=temp->next;
            buffers[i]->setCurrent(temp);
        }while(temp->next!=0);
    }
    //! буфер
    QVector<Buffer<T>* > buffers;
    //! корень всех элементов
    BufferDATA<T> *root;
};

#endif // IBUFFER_H
