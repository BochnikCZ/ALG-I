#pragma once
#include <iostream>
#include <vector>
#include "Structs.h"

using namespace std;

class Record
{
private:
	Date date;
	Time time;
	Bytes bytes;
	double humidity;
	double temperature;
	double battery;


public:
	Record(string line);

	Date GetDate();
	Time GetTime();
	Bytes GetBytes();
	double GetBattery();
	double GetHumidity();
	double GetTemperature();

};