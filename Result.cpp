#include <iostream>
#include "Result.h"

using namespace std;

	void Result::SetAverage(const double & av)
	{
		Average = av;
	}

	void Result::SetMin(const double & min)
	{
		Min = min;
	}

	void Result::SetMax(const double & max)
	{
		Max = max;
	}

	void Result::SetAmountValidValues(const double & amount)
	{
		AmountValidValues = amount;
	}

	void Result::SetStatus(const ResultStatus & st)
	{
		Status = st;
	}

	//Getters
	double Result::GetAverage()
	{
		return Average;
	}

	double Result::GetMin()
	{
		return Min;
	}

	double Result::GetMax()
	{
		return Max;
	}
	
	size_t Result::GetAmountValidValues()
	{
		return AmountValidValues;
	}

	ResultStatus Result::GetStatus()
	{
		return Status;
	}

	ostream & operator<<(ostream & os, Result &result)
	{
		switch(result.GetStatus())
		{
			case OK:
				os<<result.Average<<result.OutputDelimiter<<result.Min;
				os<<result.OutputDelimiter<<result.Max;
				os<<result.OutputDelimiter<<result.AmountValidValues;
				break;

			case NO_DATA:
				os<<MSG_STATUS_NO_DATA;
				break;
			
			case UNKNOW_ID:
				os<<MSG_STATUS_UNKNOW_ID;
				break;

			case BAD_QUERY:
				os<<MSG_STATUS_BAD_QUERY;
				break;
		}

		return os;
	}
