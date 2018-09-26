#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Query.h"
#include "Result.h"
#include "sensor.h"
#include "SensorNetwork.h"
#include "Array.h"

using namespace std;


Query::Query():SensorArray()
{
	SensorArray.SetOutputDelimiter(QUERY_SENSOR_LIST_DELIMITER);
	Results.SetStatus(OK);
};

Query::~Query(){};


//Setters
void Query::SetSensorList(const Array <string> & arr)
{
	SensorArray = arr;
}

void Query::SetFrom(const size_t & n)
{
	From = n;
}

void Query::SetTo(const size_t & n)
{
	To = n;
}


//Getters
Array <string> Query::GetSensorList()
{
	return SensorArray;
}

size_t Query::GetFrom()
{
	return From;
}

size_t Query::GetTo()
{
	return To;
}

Result& Query::GetResults()
{
	return Results;
}


//Metodos de Procesamiento
void Query::ProcessQuery(SensorNetwork &network)
{

	if(Results.GetStatus() == BAD_QUERY)
		return;

	switch(SensorArray.GetSize())
	{
		case 1: //Solo un sensor para procesar
			ProcessOneSensor(network);
			break;

		case 0: //Hay que procesar todos los sensores del network
			ProcessAllSensorsInNetwork(network);
			break;

		default: //Hay que procesar los sensores en SensorArray
			ProcessMultipleSensors(network);
	}	
}

void Query::ProcessOneSensor(SensorNetwork &network)
{
	size_t sensor_pos;
	bool sensor_is_in_network;

	sensor_pos = network.SearchSensorByName(SensorArray[0], sensor_is_in_network);
	
	if(sensor_is_in_network)
		SetResultsForSensor(network[sensor_pos], From, To);

	else
		Results.SetStatus(UNKNOW_ID);

}

void Query::ProcessAllSensorsInNetwork(SensorNetwork &network)
{
	size_t i;
	size_t j;
		
	double sensor_val_sum;
	double sensor_val_avg;
	bool valid_sensor_data;
	size_t amount_valid_senors;
	size_t network_size = network.GetSize();

	Sensor aux_sensor;
	size_t aux_from = 0;
	size_t aux_to = To - From;

	for(j = From; j < To; j++) //Para todos las posiciones pedidas
	{
		sensor_val_sum = 0;
		amount_valid_senors = 0;
		valid_sensor_data = false;
		
		for(i = 0; i < network_size; i++) //Calcular promedio de los sensores, si son validos en esta posición.
		{
			if(network[i].IsValid(j))
			{
				valid_sensor_data = true; //Hubo al menos un sensor con dato valido en esta posición.
				sensor_val_sum += network[i][j];
				amount_valid_senors++;
			}
		}

		if(valid_sensor_data)
		{
			sensor_val_avg = sensor_val_sum/amount_valid_senors;
			aux_sensor.Append(sensor_val_avg);
		}
		else
		{
			aux_sensor.AppendEmpty();
		}			
	}

	SetResultsForSensor(aux_sensor, aux_from, aux_to);
}

void Query::ProcessMultipleSensors(SensorNetwork &network)
{
	size_t i;

	size_t sensor_array_size = SensorArray.GetSize();
	size_t sensor_pos;
	bool sensor_is_in_network;

	SensorNetwork aux_network;

	for(i = 0; i < sensor_array_size; i++)
	{
		sensor_pos = network.SearchSensorByName(SensorArray[i], sensor_is_in_network);
		if(sensor_is_in_network)
		{
			aux_network.Append(network[sensor_pos]);
		}

		else
		{
			Results.SetStatus(UNKNOW_ID);
			return;
		}
	}

	ProcessAllSensorsInNetwork(aux_network);
}

void Query::SetResultsForSensor(Sensor &sensor, size_t& from, size_t& to)
{	
	double avg;
	double max;
	double min;
	size_t valid_values;

	avg = sensor.GetAverage(from, to, valid_values);
	max = sensor.GetMax(from, to, valid_values);
	min = sensor.GetMin(from, to, valid_values);
	if(valid_values != 0)
	{
		Results.SetAverage(avg);
		Results.SetMin(min);
		Results.SetMax(max);
		Results.SetAmountValidValues(valid_values);
		
	}

	else
	{
		Results.SetStatus(NO_DATA);
	}
}

ostream & operator<<(ostream & os, Query &query)
{
	if(query.Results.GetStatus() == BAD_QUERY)
		os<<MSG_STATUS_BAD_QUERY<<endl;
	else	 
		os<<query.SensorArray<<QUERY_INPUT_DELIMITER<<query.From<<QUERY_INPUT_DELIMITER<<query.To;
	return os;
}


//Carga una query ingresada en formato CSV.
istream & operator>>(istream & is, Query &query)
{
	string sensor_list;

	string sensor;
	double from;
	double to;
	char c;

	//Lectura de los nombres de los sensores
	getline(is, sensor_list, QUERY_INPUT_DELIMITER);
	
	istringstream stream_sensor_list(sensor_list);
	while(getline(stream_sensor_list, sensor, QUERY_SENSOR_LIST_DELIMITER))
		query.SensorArray.Append(sensor);


	//Lectura del campo 'From'
	if(is>>from)
		query.From = from;

	else
		query.Results.SetStatus(BAD_QUERY);


	while(is>>c && c != QUERY_INPUT_DELIMITER){}

	//Lectura del campo 'To'
	if(is>>to)
		query.To = to;

	else
		query.Results.SetStatus(BAD_QUERY);

	if(from > to)
		query.Results.SetStatus(BAD_QUERY);
	
	return is;		
}