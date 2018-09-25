#ifndef QUERYNETWORK__H
#define QUERYNETWORK__H

#include <iostream>
#include "Query.h"
#include "Array.h"
#include "SensorNetwork.h"

#define DEFAULT_QUERY_NETWORK_LEN 0

class QueryNetwork
{
	Array<Query> Queries;
	size_t size;

public:

	QueryNetwork(int n=DEFAULT_QUERY_NETWORK_LEN);
	~QueryNetwork();

	size_t GetSize();

	void Append(Query &);
	Query & operator[](size_t);
    Query const & operator[](size_t) const;

	friend ostream& operator<<(ostream &, QueryNetwork &);
	friend istream& operator>>(istream &, QueryNetwork &);

	void ProcessQueries(SensorNetwork &);
	void ExportResultsAsCSV(ostream &);
};


#endif