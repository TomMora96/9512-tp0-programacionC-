#ifndef RESULT__H
#define RESULT__H

#include <iostream>
using namespace std;

#define MSG_STATUS_OK "OK"
#define MSG_STATUS_NO_DATA "NO DATA"
#define MSG_STATUS_UNKNOW_ID "UNKNOW ID"
#define MSG_STATUS_BAD_QUERY "BAD QUERY"

typedef enum{
	OK,
	NO_DATA,
	UNKNOW_ID,
	BAD_QUERY
} ResultStatus;

class Result
{
	double Average;
	double Min;
	double Max;
	size_t AmountValidValues;
	ResultStatus Status;
	char OutputDelimiter = ',';

public:

	//Setters
	void SetAverage(const double &);
	void SetMin(const double &);
	void SetMax(const double &);
	void SetAmountValidValues(const double &);
	void SetStatus(const ResultStatus &);

	//Getters
	double GetAverage();
	double GetMin();
	double GetMax();
	size_t GetAmountValidValues();
	ResultStatus GetStatus();

	friend ostream & operator<<(ostream & os, Result &result);
};

#endif