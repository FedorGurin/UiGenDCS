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

    //! �������� ������ � ������
    void push(T data)
    {
        //BufferDATA<T> *ptr=buffer[i];
    }

    //! ���������� �������� � ��������� ������
    void insert(int i,T value)
    {
        buffers[i]->value=value;
    }
    //! ������ ������ �������
    void setSizeBuffers(int size)
    {
        buffers.resize(size);
        //    buffers.push_back(new Buffer<T>);
    }

    /*
    //! ������ ����� ������
    T top();
    //! ��������� �� �������� ������
    T* top();


    const double * operator [] ( int i ) const;
*/

private:
    //! �����
    QVector<Buffer<T>* > buffers;
    //! ������ ���� ���������
    BufferDATA<T> *root;
};

#endif // IBUFFER_2_H
