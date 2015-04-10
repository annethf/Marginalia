#ifndef VECTOR_H
#define VECTOR_H

template <typename Object> //��template <class Object>
class Vector
{
public:
    explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
    {
        objects = new Object[theCapacity]; //�ڶ��Ϸ���һ���ܴ��theCapacity��ObjectԪ�ص����飬
    }
    Vector(const Vector & rhs) : objects(NULL)
    {
        operator= (rhs);
    }
    ~Vector()
    {
        delete [] objects;
    }
    const Vector& operator= (const Vector &rhs);
    void reSize(int newSize);
    void reServe(int newCapacity);
    Object& operator[](int index);
    const Object& operator[](int index) const;
    bool isEmpty() const;
    int Size() const;
    int Capacity() const;
    void pushBack(const Object &x);
    void popBack();
    const Object &Back() const;
    //��һ�μ���
    typedef Object * Iterator;
    typedef const Object * const_Iterator;

    Iterator Begin();
    const_Iterator Begin() const;
    Iterator End();
    const_Iterator End() const;
    /**��ȷ������
    Iterator Begin()
    {
        return &objects[0];
    }
    const_Iterator Begin() const;
    {
        return &objects[0];
    }
    Iterator End()
    {
        return &objects[Size()];
    }
    const_Iterator End() const
    {
        return &objects[Size()];
    }**/
private:
    int theSize;
    int theCapacity;
    Object *objects;
    static const int SPARE_CAPACITY = 10;
};

template <typename Object>
const Vector<Object>& Vector<Object>::operator= (const Vector<Object> &rhs)
{
    if(this != &rhs)
    {
        delete [] objects;
        theSize = rhs.Size();
        theCapacity = rhs.theCapacity;

        objects = new Object[Capacity()];
        for(int k = 0; k < Size(); k++)
            objects[k] = rhs.objects[k];
    }
    return *this;
}

template <typename Object>
void Vector<Object>::reSize(int newSize)
{
    if(newSize > theCapacity)
        reServe(newSize * 2 + 1);
    theSize = newSize;
}

template <typename Object>
void Vector<Object>::reServe(int newCapacity)
{
    if(newCapacity < theSize)
        return;

    Object *oldArray = objects;

    objects = new Object[newCapacity];
    for(int k = 0; k < theSize; k++)
        objects[k] = oldArray[k];

    theCapacity = newCapacity;
    delete [] oldArray;
}

template <typename Object>
int Vector<Object>::Size() const
{
    return theSize;
}

template <typename Object>
int Vector<Object>::Capacity() const
{
    return theCapacity;
}

template <typename Object>
bool Vector<Object>::isEmpty() const
{
    return Size() == 0;
}

template <typename Object>
void Vector<Object>::pushBack(const Object &x)
{
    if(theSize == theCapacity)
        reServe(2 * theCapacity + 1);
    objects[theSize++] = x;
}

template <typename Object>
void Vector<Object>::popBack()
{
    theSize--;
}

template <typename Object>
const Object& Vector<Object>::Back() const
{
    return objects[theSize - 1];
}

template <typename Object>
Object& Vector<Object>::operator[] (int index)
{
    return objects[index];
}

template <typename Object>
const Object& Vector<Object>::operator[] (int index) const
{
    return objects[index];
}

/**���������
template <typename Object>
Iterator Vector<Object>::Begin()
{
    return &objects[0];
}

template <typename Object>
const_Iterator Vector<Object>::Begin() const
{
    return &objects[0];
}

template <typename Object>
Iterator Vector<Object>::End()
{
    return &objects[Size()];
}

template <typename Object>
Vector::const_Iterator Vector<Object>::End() const
{
    return &objects[Size()];
}**/

/**��ȷ������**/
template <typename Object>
typename Vector<Object>::Iterator Vector<Object>::Begin()
{
    return &objects[0];
}

template <typename Object>
typename Vector<Object>::const_Iterator Vector<Object>::Begin() const
{
    return &objects[0];
}

template <typename Object>
typename Vector<Object>::Iterator Vector<Object>::End()
{
    return &objects[Size()];
}

template <typename Object>
typename Vector<Object>::const_Iterator Vector<Object>::End() const
{
    return &objects[Size()];
}

#endif // VECTOR_H
