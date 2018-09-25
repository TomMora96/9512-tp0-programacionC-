#ifndef SENSOR__H
#define SENSOR__H

#include <iostream>
#include "Array.h"

#define DEFAULT_SENSOR_NAME "sensor0"
#define DEFAULT_SENSOR_LEN 8

class Sensor
{
    Array <double> data;
    Array <bool> valid;

    size_t size;
    string name;

public:

    Sensor(string s=DEFAULT_SENSOR_NAME, size_t n=DEFAULT_SENSOR_LEN)/*:valid(n),data(n),size(0),name("sendor0"){}*/;
    ~Sensor();

    double & operator[](size_t);
    double const & operator[](size_t) const;

    bool operator==(Sensor const &);
    Sensor & operator=(Sensor & s);

    size_t GetSize()const;
    string GetName()const;

    void SetName(string);
    void GetDataFromCsvString(string str, char delimiter);
    
    bool & IsValid(size_t i);
    double & GetData(size_t i);

    //Sensor::GetAverage: Devuelve por nombre el promedio de los valores del sensor en el rango [from, to]
    // Devuelve por referencia la cantidad de valores validos en el rango pedido.
    // amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
    double GetAverage(size_t from, size_t to, size_t& amount_valid_values);

    //Sensor::GetMax: Devuelve por nombre el valor maximo del sensor en el rango [from, to)
    // Devuelve por referencia la cantidad de valores validos en el rango pedido.
    // amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
    double GetMax(size_t from,size_t to, size_t &amount_valid_values);

    //Sensor::GetMin: Devuelve por nombre el valor minimo del sensor en el rango [from, to)
    // Devuelve por referencia la cantidad de valores validos en el rango pedido.
    // amount_valid_values sera 0 si la cantidad es 0 o si el rango pedido excede los limites del sensor.
    double GetMin(size_t from,size_t to, size_t &amount_valid_values);

    void Append(double );
    void AppendEmpty();

    void ExportAsCsv(ostream & os, char delim);
    friend ostream & operator<<(ostream & os, Sensor &s);

};


#endif