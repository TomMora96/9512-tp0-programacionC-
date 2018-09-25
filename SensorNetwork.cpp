#include <iostream>
#include <string>
#include <sstream>
#include "Array.h"
#include "SensorNetwork.h"
#include "sensor.h"


SensorNetwork::SensorNetwork(int n):sensors(n)
{
    size=0;
}

SensorNetwork::~SensorNetwork()
{}

void SensorNetwork::SetSize(size_t s)
{
    size=s;
}

Sensor & SensorNetwork::operator[](size_t i)
{    
    if(i>size)
        size=i;
    return sensors[i];
}

Sensor const & SensorNetwork::operator[](size_t i)const
{    return sensors[i];}

void SensorNetwork::Append(Sensor &s)
{
    sensors.Append(s);
    size++;
}

void SensorNetwork::GetFromCsvFile(istream *is,char delimiter)
{
   	string str;
	string aux;
	Sensor s;
	double temp;
	size_t i;
	size_t in;
	size_t fn=0;

	string str2;

	getline(*is,str);
	
	while(fn<str.length())
	{	
		in=fn;
		for(; str[fn]!=delimiter &&fn<str.length(); fn++);
		aux=str.substr(in,fn-in);
		fn++;

		s.SetName(aux);
		this->Append(s);
	}

	while(getline(*is,str))
	{
		i=0;
		stringstream ss(str);
		while(getline(ss,str2,delimiter))
		{			
			if(str2.empty())
				(*this)[i].AppendEmpty();
				
			else
			{
				stringstream str_st(str2);
				if(str_st>>temp)
				{
					(*this)[i].Append(temp);
				}
			}
			i++;
		}

		if(str2.empty())
		{
			(*this)[i].AppendEmpty();
		}
	}

}


// SearchSensorByName: Devuelve por nombre la posición del sensor de nombre (name)
// 		si no se encuentra dicho sensor devuelve 0.
// Ademas devuelve por referencia si se encontro el sensor o no (is_in_network).
size_t SensorNetwork::SearchSensorByName(string name, bool& is_in_network)
{
	size_t i = 0;
	string s;
	s = sensors[i].GetName();

	for(i = 0; i < size; i++)
	{
		s = sensors[i].GetName();
		fflush(stdout);

		if(sensors[i].GetName() == name)
		{
			is_in_network = true;
			return i;				
		}
	}

	is_in_network = false;
	return 0;
}

void SensorNetwork::ExportAsCsv(ostream & os, char delim)
{
    for(size_t i=0; i<size; i++)
    {
        sensors[i].ExportAsCsv(os,delim);
    	os<<endl;
    }
}

ostream & operator<<(ostream & os, SensorNetwork &sn)
{
    for(size_t i=0; i<sn.size; i++)
    {
        os<<sn[i]<<endl;
    }
    return os;
}

