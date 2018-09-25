#include <iostream>
#include <string>
#include <sstream>
#include "sensor.h"
#include "Array.h"

using namespace std;

#define SENSOR_OUTPUT_DELIMITER ","


Sensor:: Sensor(string s, size_t n):valid(n),data(n)
{
    size_t i;
    for(i=0;i<n;i++)
    {
        valid[i]=false;
        data[i]=-1;
    }
    size=0;
    name=s;
}



Sensor:: ~Sensor()
{
    //valid.~Array(); ver: preguntar como funciona la destruccion de memoria dinamica
    //data.~Array();
}

bool Sensor::operator==(Sensor const & s)
{
    if(size==s.size&&name==s.name&&valid==s.valid&&data==s.data)
        return true;

    return false;
}

Sensor & Sensor::operator=(Sensor & s)
{
    if(*this==s)
        return *this;
        
    valid=s.valid;
    data=s.data;

    size=s.size;
    name=s.name;

    return *this;
}

double & Sensor::operator[](size_t i)
{    
    if(i+1>size)
    {
        size=i+1;
        data.SetSize(i+1);
        valid.SetSize(i+1);
    }
    return data[i];
}

double const & Sensor::operator[](size_t i)const
{
    return data[i];
}


bool & Sensor::IsValid(size_t i)
{
    return valid[i];
}

double & Sensor::GetData(size_t i)
{   return data[i];}

size_t Sensor::GetSize()const
{return size;}

string Sensor::GetName()const
{return name;}

void Sensor::SetName(string s)
{    name=s;}


//Sensor::GetAverage: Devuelve por nombre el promedio de los valores del sensor en el rango [from, to]
// Devuelve por referencia la cantidad de valores validos en el rango pedido.
// amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
double Sensor::GetAverage(size_t from, size_t to, size_t &amount_valid_values)
{   size_t i;
    float sum=0;
    amount_valid_values = 0;

    if(from>size||to>size||from>to)
    {
        amount_valid_values = 0;
        return 0;
    }

    for(i=from; i<to; i++)
    {
        if(valid[i]==true)
        {
            sum+=data[i];
            amount_valid_values++;
        }
    }

    return sum/amount_valid_values;

}


//Sensor::GetMax: Devuelve por nombre el valor maximo del sensor en el rango [from, to)
// Devuelve por referencia la cantidad de valores validos en el rango pedido.
// amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
double Sensor:: GetMax(size_t from,size_t to, size_t &amount_valid_values)
{   
    size_t i = 0;
    double max;
    amount_valid_values = 0;

    if(from>size||to>size||from>to)
    {
        amount_valid_values = 0;
        return 0;
    }

    //Si el primer valor es valido, usarlo como max
    if(valid[from] == true)
    {
        max = data[from];
        i = from;
    }

    else //Si no, usar el primer valor valido.
    {
        for(i=from; valid[i] != true && i<=to; i++){}       
        max = data[i];
    }

    for(; i<to;i++)
    {
        if(valid[i] == true)
        {
            amount_valid_values++;
            if(data[i]>max)
                max=data[i];
        }
    }
    
    return max;
}


//Sensor::GetMin: Devuelve por nombre el valor minimo del sensor en el rango [from, to)
// Devuelve por referencia la cantidad de valores validos en el rango pedido.
// amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
double Sensor:: GetMin(size_t from,size_t to, size_t &amount_valid_values)
{   
    size_t i = 0;
    double min;
    amount_valid_values = 0;

    if(from>size||to>size||from>to)
    {
        amount_valid_values = 0;
        return 0;
    }

    //Si el primer valor es valido, usarlo como min
    if(valid[from] == true)
        min = data[from];

    else //Si no, usar el primer valor valido.
    {
        for(i=from; valid[i] != true && i<=to; i++){}       
        min = data[i];
    }

    for(i = from; i<to;i++)
    {
        if(valid[i] == true)
        {
            amount_valid_values++;
            if(data[i]<min)
                min=data[i];
        }
    }
    
    return min;}

void Sensor::Append(double t)
{   
    bool v=true;
    data.Append(t);
    valid.Append(v);
    size++;
}

void Sensor::AppendEmpty()
{   
    bool v=false;
    double d=-1;
    data.Append(d);
    valid.Append(v);
    size++;
}

void Sensor::GetDataFromCsvString(string str, char delimiter)
{
    string aux;
    size_t fn;
    size_t in;
    size_t i;
    double temp;

	fn=0;
    i=0;
	while(fn<str.length())
	{
		in=fn;
		for(; str[fn]!=delimiter&&fn<str.length(); fn++);
		
		aux=str.substr(in,fn-in+1);
		fn++;
		stringstream str_st(aux);
		str_st>>temp;
        data[i]=temp;
        valid[i]=true;
		i++;

		if(str[fn]==delimiter)
		{
			cout<<"nada"<<endl;
            valid[i]=false;
            data[i]=-1;
			fn++;
		}
    size=i;
	}
}

void Sensor::ExportAsCsv(ostream & os, char delim)
{
    if(size==0)
        return;

    os<<name<<delim;

    for(size_t i=0;i<size-1;i++)
    {
        if(valid[i]==true)
        {
            os<<data[i];

            if(i!=size-1)
                os<<delim;
        }
        else
        {
            os<<delim;
        }
    }

    if(valid[size-1]==true)
            os<<data[size-1];

}

ostream & operator<<(ostream & os, Sensor &s)
{
    os<<s.name;
    
    os<<SENSOR_OUTPUT_DELIMITER; 
 
    if(s.size==0)
        return os;

    for(size_t i=0;i<s.size-1;i++)
    {
        if(s.valid[i]==true)
        {
            os<<s[i];

            if(i+1!=s.size-1||s.valid[i+1]==true)//valida si pone la última coma
                os<<SENSOR_OUTPUT_DELIMITER;     //teniendo el último dato vacío
        }
    }
    if(s.valid[s.size-1]==true)
            os<<s[s.size-1];

    return os;
}