#ifndef ARRAY__H
#define ARRAY__H
#include <iostream>
#include <cstdio>


#define ARR_DEFAULT_SIZE 2
#define ARR_CHOP_SIZE 5
#define CSV_OUTPUT_DELIMITER ','

using namespace std;


template <class T>

class Array
{
    T * data;
    size_t size;
    size_t alloc_size; //ver

    char output_delimiter;

    void realloc(size_t);

public:

    Array(int n=ARR_DEFAULT_SIZE);
    ~Array();

    size_t GetSize()const;
    size_t GetAllocSize()const;

    void SetSize(size_t);

    Array <T> & operator=(const Array <T> &);

    bool operator==(const Array <T> &)const;
    bool operator!=(const Array <T> &)const;

    T & operator[](int);
    T const & operator[](int) const;


    float GetAverage(size_t const &, size_t const &);
    T GetMax(size_t const &,size_t const &);
    T GetMin(size_t const &,size_t const &);

    void Append(T &element);
    void SetOutputDelimiter(char);

    template <class TT> 
    friend ostream & operator<< (ostream &os, Array<TT> const&arr);
};


template <class T>
void Array<T>::realloc(size_t new_size)
{
    size_t i;
    T *aux;
    aux=new T[new_size];

    for(i=0;i<size; i++)
    {
        aux[i]=data[i];
    }

    if( new_size<size )
    {
		size= new_size;
	}


    delete[]data;
    alloc_size=new_size;
    data=aux;
}

template <class T>
Array<T>::Array(int n)
{
    data=new T[n];
    alloc_size=n;
    size=0;
    output_delimiter = CSV_OUTPUT_DELIMITER;
}

template <class T>
Array <T>::~Array()
{
    if(data!=NULL)
        delete []data;
}

template <class T>
size_t Array<T>::GetSize() const
{
    return size;
}

template <class T>
size_t Array<T>::GetAllocSize()const
{
    return alloc_size;
}

template <class T>
void Array<T>::SetSize(size_t i)
{size=i;}

template <class T>
Array <T> & Array <T>::operator=(const Array <T> & r)
{
    T *aux;

    size_t i;
    if(this==&r)
        return *this;

    if(size!=r.size)
    {
        aux=new T[r.size];
        delete[]data;
        data=aux;
        alloc_size=r.alloc_size;
        size=r.size;
    }
    
    for(i=0; i<size;i++)
        data[i]=r.data[i];
        
    return *this;
}

template <class T>
bool Array<T> :: operator==(const Array & r)const
{
    size_t i;
    if(size!=r.size)
        return false;

    else
        for(i=0; i<size;i++)
            if(data[i]!=r.data[i])
                return false;

    return true;
}

template <class T>
bool Array<T> ::operator!=(const Array <T> &r) const
{
    size_t i;
    if(size!=r.size)
        return true;

    else
        for(i=0; i<size;i++)
            if(data[i]!=r.data[i])
                return true;

    return false;

}

template <class T>
ostream & operator<< (ostream &os, Array<T> const&arr)
{
	size_t i;

	if(arr.size == 0)
		return os;

    // Se asume que existe el operador << para la clase T
    for(i=0; i<arr.GetSize() - 1; i++)
    {
        os<<arr[i]<<arr.output_delimiter;
    }

    os<<arr[i];

    return os;
}

template <class T>
T& Array <T>::operator[](int i)
{
    // ver validacion si i no existe en el arreglo
    return data[i];
}

template <class T>
T const& Array <T>::operator[](int i) const
{
    // ver validacion si i no existe en el arreglo
    return data[i];
}

template <class T>
float Array<T>::GetAverage(size_t const & from, size_t const & to)
{
    size_t i,j;
    float sum=0;

    if(from>size||to>size||from>to)
        return 0;

    for(i=from; i<to; i++)
    {
        if(data[i]!=0)
        {
            sum+=data[i];
            j++;
        }
    }

    return sum/j;
}

template <class T>
T Array<T>::GetMax(size_t const & from,size_t const & to)
{
    size_t i;
    T max=0;

    if(from>size||to>size||from>to)
        return 0;

    for(i=from; i<to;i++)
    {
        if(data[i]>max)
            max=data[i];
    }
    return max;
}

template <class T>
T Array<T>::GetMin(size_t const &from, size_t const &to)
{
    size_t i,j;
    T min;

    if(from>size||to>size||from>to)
        return 0;

    for(i=from; data[i]==0;i++);

    min=data[i];

    for(j=i; j<to;j++)
    {
        if(data[j]<min)
            min=data[j];
    }
    return min;
}


template <class T>
void Array <T> ::SetOutputDelimiter(char c)
{
	output_delimiter = c;
}

template <class T>
void Array <T> ::Append(T &element)
{

    if(size==alloc_size)
        this->realloc(alloc_size+1);

    data[size]=element;
    size++;
}

#endif