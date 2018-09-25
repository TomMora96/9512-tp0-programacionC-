#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

#include "Array.h"
#include "sensor.h"
#include "SensorNetwork.h"
#include "cmdline.h"
#include "Query.h"
#include "QueryNetwork.h"

#include <cstdio>

#define DBG(x) cerr << #x << ":" << (x) << endl

using namespace std;

static void opt_input(string const &arg);
void opt_output(string const &arg);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{0, "o", "output", "-", opt_output, OPT_MANDATORY},
	{0, }
};

static istream *input_stream = 0;
static fstream ifs;
static ostream *output_stream =0;
static fstream ofs;

static void opt_input(string const &arg)
{
		cout<<arg<<endl;

	if(arg == "-") {
		input_stream = &cin;
	}	
	else{
		ifs.open(arg.c_str(), ios::in);
		input_stream = &ifs;
	}

	if(!input_stream-> good()){
		cerr << "Error al abrir archivo " << arg << endl;
		exit(1);
	}

}


void opt_output(string const &arg)
{
	/*if(arg=="-")
		output_stream = &cout;
	
	else
	{
		ofs.open(arg.c_str(), ios::out);
		output_stream=&ofs;
	}

	if(!output_stream-> good()){
		cerr << "Error al abrir archivo " << arg << endl;
		exit(1);
	}
	cout<<"-o"<<endl;*/
}

int main(int argc, char * const argv[])
{
	// Luego de parsear el archivo de entrada, leo líneas, las convierto en
	// streams con la clase stringstream, de las cuales leo e imprimo arreglos
	// hasta no encontrar más. Si en una línea hay un arreglo escrito 
	// de manera incorrecta, no acepto ninguno más

	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	QueryNetwork query_network;
	SensorNetwork sensor_network;

	ifstream query_stream("Consultas_CPU_Temp.csv");
	query_stream>>query_network;

	sensor_network.GetFromCsvFile(input_stream, ',');

	//cout<<"Query Network: "<<endl<<query_network<<endl;

	//cout<<"SensorNetwork:"<<endl;

	//sensor_network.ExportAsCsv(cout, ',');
	query_network.ProcessQueries(sensor_network);
	cout<<"Results: "<<endl;
	query_network.ExportResultsAsCSV(cout);
	




	return 0;
}
