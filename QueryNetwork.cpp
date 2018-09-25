#include <iostream>
#include <string>
#include <sstream> 

#include "QueryNetwork.h"
#include "Query.h"
#include "SensorNetwork.h"
#include "Array.h"


QueryNetwork::QueryNetwork(int n): Queries(n)
{
	size = 0;
}

QueryNetwork::~QueryNetwork(){}

size_t QueryNetwork::GetSize()
{return size;}

void QueryNetwork::Append(Query & query)
{
	Queries.Append(query);
	size++;
}

Query & QueryNetwork::operator[](size_t i)
{    
    if(i>size)
        size=i;
    
    return Queries[i];
}

Query const & QueryNetwork::operator[](size_t i)const
{return Queries[i];}

ostream& operator<<(ostream & os, QueryNetwork & network)
{
	for(size_t i = 0; i < network.size; i++)
		os<<network.Queries[i]<<endl;

	return os;
}

istream& operator>>(istream & is, QueryNetwork & network)
{	
	string line;
	Query * query_ptr;

	while(getline(is, line))
	{
		query_ptr = new Query;
		stringstream stream_line(line);
		stream_line>>(*query_ptr);
		network.Append(*query_ptr);
	}

	return is;
}

void QueryNetwork::ProcessQueries(SensorNetwork &s_network)
{
	for(size_t i = 0; i < size; i++)
		Queries[i].ProcessQuery(s_network);
}

void QueryNetwork::ExportResultsAsCSV(ostream & os)
{
	for(size_t i = 0; i < size; i++)
	{
		os<<Queries[i].GetResults()<<endl;
	}	
}
