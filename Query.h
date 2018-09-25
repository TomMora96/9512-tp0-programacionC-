#ifndef QUERY__H
#define QUERY__H

#include <iostream>
#include <string>
#include "Array.h"
#include "Result.h"
#include "SensorNetwork.h"
#include "Sensor.h"

using namespace std;

//Delimitador de campo de una linea de entrada de query
#define QUERY_INPUT_DELIMITER ','

//Delimitador para la lista de sensores de una query
#define QUERY_SENSOR_LIST_DELIMITER ';'

//Cantidad de campos que tiene una linea de entrada de un query
#define QUERY_INPUT_AMOUNT_FIELDS 3


class Query
{
	Array<string> SensorArray;
	size_t From;
	size_t To;
	Result Results;

	void ProcessOneSensor(SensorNetwork &);
	void ProcessAllSensorsInNetwork(SensorNetwork &);
	void ProcessMultipleSensors(SensorNetwork &);

	void SetResultsForSensor(Sensor &, size_t&, size_t&);

public:

	Query();
	~Query();

	//Setters
	void SetSensorList(const Array <string> &);
	void SetFrom(const size_t &);
	void SetTo(const size_t &);

	//Getters
	Array <string> GetSensorList();
	size_t GetFrom();
	size_t GetTo();
	Result& GetResults();

	void ProcessQuery(SensorNetwork &);

	friend ostream & operator<<(ostream & os, Query &query);
	friend istream & operator>>(istream & is, Query &query);
};

#endif
