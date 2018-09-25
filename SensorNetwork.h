#ifndef SENSORNETWOR__H
#define SENSORNETWOR__H

#include <iostream>
#include <string>
#include <sstream>
#include "Array.h"
#include "sensor.h"

#define DEFAULT_SENSORNETWORK_LEN 0


class SensorNetwork
{
    Array <Sensor> sensors;
    size_t size;

public:

    SensorNetwork(int n=DEFAULT_SENSORNETWORK_LEN);
    ~SensorNetwork();

    Sensor & operator[](size_t);
    Sensor const & operator[](size_t) const;

    size_t GetSize(){return size;}
    void SetSize(size_t);

    // SearchSensorByName: Devuelve por nombre la posición del sensor de nombre (name)
    //      si no se encuentra dicho sensor devuelve 0.
    // Ademas devuelve por referencia si se encontro el sensor o no (is_in_network).
    size_t SearchSensorByName(string name, bool& is_in_network);

    void GetFromCsvFile(istream * ,char );

    void Append(Sensor &s);//ver: por que no funciona sin la referencia
 
    void ExportAsCsv(ostream & , char );
    friend ostream & operator<<(ostream & os, SensorNetwork &sn);

};

#endif