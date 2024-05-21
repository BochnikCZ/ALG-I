#pragma once
#include <iostream>
#include <vector>
#include "Structs.h"

using namespace std;

struct Date
{
	int year;
	int month;
	int day;
};

struct Time {
	int hour;
	int minute;
	int second;
};

struct Bytes
{
	int first_byte;
	int second_byte;
	int third_byte;
	int fourth_byte;
	int fifth_byte;
};